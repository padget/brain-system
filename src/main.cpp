
//#include "meta/core.hpp"
//#include "meta/fundamental.hpp"
//#include "meta/keywords.hpp"
//#include "meta/math.hpp"
//#include "configuration/properties.hpp"
//#include <iostream>

#include "meta/meta.hpp"
#include <iostream>
#include <typeinfo>
//#include "test/utest/utest.hpp"

using namespace brain::meta;
using namespace std;

namespace test_is_placeholder_expression
{
    // using expression_t = if_t<_0_, _1_, _3_>;
    /// static_assert(v_<is_placeholder_expression<if_t_<if_t_<_0_>>>>, "");
    //static_assert(false, "";)
}



/// Main function for
/// C++ compiler.
int main()
{
    using begin_t = forward_iterator_builder_<pack<int, double, short>>;

    using next1_t = next_<begin_t>; /// double
    using next2_t = next_<next1_t>; /// short
    using end_t = next_<next2_t>; /// nil

    std::cout << typeid(advance_<begin_t, long_<0>>).name() << std::endl;
//
//    static_assert(v_<is_same_<begin_t, advance_<begin_t, long_<0>>>>, "");
//    static_assert(v_<is_same_<next1_t, advance_<next1_t, long_<0>>>>, "");
//    static_assert(v_<is_same_<next2_t, advance_<next2_t, long_<0>>>>, "");
//    static_assert(v_<is_same_<end_t, advance_<end_t, long_<0>>>>, "");
//
//    static_assert(v_<is_same_<next1_t, advance_<begin_t, long_<1>>>>, "");
//    static_assert(v_<is_same_<next2_t, advance_<begin_t, long_<2>>>>, "");
//    static_assert(v_<is_same_<end_t, advance_<begin_t, long_<3>>>>, "");
//
//    static_assert(v_<is_same_<end_t, advance_<next1_t, long_<2>>>>, "");

    return 0;
}
