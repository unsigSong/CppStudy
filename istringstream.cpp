#include <iostream>
#include <sstream>
#include <iterator>
#include <numeric>
#include <algorithm>

int main()
{
    std::istringstream str("0.1 0.2 0.3 0.4");
    std::partial_sum(std::istream_iterator<double>(str),
                     std::istream_iterator<double>(),
                     std::ostream_iterator<double>(std::cout, " ")  );

    std::cout << "\n first even number is = "<< std::endl;
    std::istringstream str2("1 3 5 7 9 10");
    std::cout << *std::find_if(std::istream_iterator<int>(str2),
                     std::istream_iterator<int>(),
                     [](int i){return i%2 == 0; } ) << std::endl;

}