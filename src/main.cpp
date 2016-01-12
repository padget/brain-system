
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

using namespace brain;
using namespace std;


/// Main function for
/// C++ compiler.
int main()
{
    using a_list = meta::list<double, int, short, std::string>;
    using a_second_list = meta::pop_front_t<a_list>;
    
    static_assert(meta::v_<std::is_same<meta::list<int, short, std::string>, a_second_list>>, "");
    /*launch < test::test_suite < meta::test::member_test,
           meta::test::literal_test,
           meta::test::constkw_test,
           meta::test::pack_test,
           meta::test::function_test,
           meta::test::math_test,
           meta::test::conditional_test,
           meta::test::runtime_test,
           test::property_value_test,
           test::property_cvalue_test,
           test::property_pointer_test,
           test::object_test,
           test::marshalling_test,
           test::any_test,
           test::system_test,
           test::scanner_test,
           test::parser_test,
           test::system_test,
           test::scanner_test,
           test::parser_test >> ();

    */


    return 0;
}
