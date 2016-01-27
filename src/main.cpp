
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

using namespace brain;
using namespace std;


using return_int_if_is_float =
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

/// Main function for
/// C++ compiler.
int main()
{

    using foo = meta::iter::advance_ <
                meta::iter::test_advance::begin_t,
                meta::unsigned_<1>>;
    
    std::cout << typeid(meta::iter::item_<foo>).name() << std::endl;
                
    using push = meta::lazy::push_back_<meta::_0_, meta::iter::member::item_<meta::_1_> >;

    std::cout << std::boolalpha;
    std::cout << meta::v_<meta::is_placeholder_expression_<lazy2::item_<meta::_1_>>> << std::endl;

    std::cout << typeid(meta::return_<meta::function_class_<void__>, int>).name() << std::endl;
    std::cout << typeid(meta::return_<return_int_if_is_float, meta::true_, meta::false_, meta::true_, int, short>).name() << std::endl;

    std::cout << typeid(meta::return_<push, meta::pack<>, meta::iter::forward_iterator<meta::unsigned_<0>, int, toto>>).name() << std::endl;

    return 0;
}
