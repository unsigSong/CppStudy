#include <functional>
#include <iostream>
#include <map>

int main()
{

    std::map<std::string, std::function<void(int)>> fun_map;

    fun_map.insert(std::make_pair( "print", [](int i){std::cout<< i << std::endl; })) ;

    fun_map["print"](9);

    return 0;
}