
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


using return_int_if_is_float =
    lazy::if_<lazy::if_<lazy::if_<_0_, _1_, _2_>, _2_, _1_>, _3_, _4_>;

template<typename foo>
struct void_r_
{
    using type = void;
};

/// Main function for
/// C++ compiler.
int main()
{



    std::cout << typeid(return_<void_r_<int>>).name() << std::endl;
    std::cout << typeid(return_<return_int_if_is_float, true_, false_, true_, int, short>).name() << std::endl;

    return 0;
}
