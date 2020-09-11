#include <iostream>
#include <tuple>
#include <utility>

int add(int first, int second) { return first + second;}

template<typename T>
T add_generic( T first, T second){ return first + second;}

auto add_lamda = [](auto first, auto second){ return first + second;};

template<typename... Ts>
std::ostream& operator<<(std::ostream& os, std::tuple<Ts...> const& theTuple)
{
    std::apply
    (
        [&os](Ts const&... tupleArgs)
        {
            os << '[';
            std::size_t n{0};
            ((os<<tupleArgs<<(++n != sizeof...(Ts) ? ", " : "")),...);
            os<< ']';
        }, theTuple
    );
    return os;
}

int main()
{
    //OK
    std::cout << std::apply(add, std::pair(1,2)) <<std::endl;

    //OK
    std::cout << std::apply(add_generic<float>, std::make_pair(2.0f, 3.0f)) << "\n";

    //Error
    //std::cout << std::apply(add_generic, std::make_pair(2.0f, 3.0f)) << "\n";
    
    //OK
    std::cout << std::apply(add_lamda, std::pair(2.0f, 3.0f)) << std::endl;

    //advanced example
    std::tuple myTuple(25, "Hello", 9.31f, 'c');
    std::cout << myTuple << "\n";
    
    return 0;
}

//command : g++ apply.cpp -std=c++17