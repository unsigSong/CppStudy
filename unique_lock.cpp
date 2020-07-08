#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

struct Box {
    explicit Box(int num) : num_things{num} {}
    int num_things;
    std::mutex m;
};


void transfer(Box &from, Box &to, int num){
    //실제 lock이 되지 않았다.
    std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
    std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);

    //deadlock 없이 unique_locks 둘다 lock
    std::lock(lock1, lock2 );

    from.num_things -= num;
    to.num_things += num;
    //'unique_lock' 소멸자에서 from.m, to.m 뮤텍스가 unluck된다.
}

int main()
{
    Box acc1(100);
    Box acc2(50);

    std::thread t1(transfer, std::ref(acc1), std::ref(acc2), 10);
    std::thread t2(transfer, std::ref(acc2), std::ref(acc1), 5);

    t1.join();
    t2.join();

    std::cout << acc1.num_things << std::endl;
    std::cout << acc2.num_things << std::endl;
}


