
//#include "meta/core.hpp"
//#include "meta/fundamental.hpp"
//#include "meta/keywords.hpp"
//#include "meta/math.hpp"
//#include "configuration/properties.hpp"
//#include <iostream>

#include <vector>
#include "meta/meta.hpp"
#include <typeinfo>
#include <iostream>
//#include "test/utest/utest.hpp"

using namespace brain::meta;
using namespace std;


/// Main function for
/// C++ compiler.
int main()
{
   
    std::cout << typeid(is_placeholder_expression_<_0_>).name() << std::endl;
    std::cout << typeid(return_<_0_, std::string, double, char>).name() << std::endl;

    return 0;
}
