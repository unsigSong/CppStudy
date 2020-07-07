#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;

void worker_thread()
{
    //메인에서 데이터를 보내땔 까지 기다린다.
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, []{return ready;});

    //기다린 후 lock을 얻음
    std::cout << "worker 스레드는 데이터를 처리하고 있다.\n";
    data += " after processing";

    //데이터를 다시 메인으로 보낸다.
    processed = true;
    std::cout << "worker 스레드가 데이터 처리가 완료되었다고 신호를 보낸다\n";

    //notifying 하기 전에 수동으로 unlocking한다.
    //기다리는 스레드가 다시 블럭되지 않도록
    lk.unlock();
    cv.notify_one();
}

int main()
{
    std::thread worker(worker_thread);

    data = "Example data";

    //데이터를 worker thread에 전송
    {
        std::lock_guard<std::mutex> lk(m);
        ready = true;
        std::cout << "main()은 데이터가 준비 되었다는 신호를 보낸다.\n";
    }
    cv.notify_one();

    //wokrer를 기다린다.
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{return processed;});
    }
    std::cout << "main()으로 오다, data = " << data << '\n';

    worker.join();
}