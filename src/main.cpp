
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

//using namespace std;
using namespace meta;

/// Main function for
/// C++ compiler.
int main()
{
    std::cout << typeid(pow_<fraction<int_<32>, int_<2>>, int_<2>>).name() << std::endl;
    return 0;
}
