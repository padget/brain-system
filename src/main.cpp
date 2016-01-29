
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

using namespace std;


/*using return_int_if_is_float =
    meta::lazy::if_ <
    meta::lazy::if_ <
    meta::lazy::if_ <
    meta::_0_,
    meta::_1_,
    meta::_2_ > ,
    meta::_2_,
    meta::_1_ > ,
    meta::_3_,
    meta::lazy::push_back_<meta::pack<>, meta::_4_> >;

template<typename type_t>
struct main_item_
{
    using type = typename type_t::item;
};

namespace lazy2
{
    template<typename type_t>
    struct item_ :
            meta::function_<main_item_, type_t> {};
}

struct toto
{
    using type = toto;
};




template<typename foo>
struct void__
{
    using type = void;
};
                  */
using namespace meta;

/// Main function for
/// C++ compiler.
int main()
{                       
   
//   using res = return_<bind_<function_class_<lazy::greater_> , _1_, _0_>, int_<1>, int_<2>>;
    using res = return_<bind_<function_class_<lazy::plus_>, _0_, ___>, int_<1>, int_<2> >;


     //std::cout << typeid(res).name() << std::endl;
    std::cout << std::boolalpha << v_<res> << std::endl;
    return 0;
}
