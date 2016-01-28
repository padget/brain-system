
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

    using binded = 
        bind_<function_class_<is_same_>, _1_, int>;
        
    std::cout << typeid(binded).name() << std::endl;
    
     using binded2 = 
            bind_<binded, int, _1_>;
            
    using res = return_<binded2, int>;
        
    std::cout << typeid(res).name() << std::endl;
    return 0;
}
