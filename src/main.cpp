/*
 * main.cpp
 *
 *  Created on: 27 oct. 2013
 *      Author: bmathieu
 */

#include "test/utest/utest.hpp"
#include "core/meta.hpp"
#include "core/core.hpp"
#include "core/serialize.hpp"
#include "core/filtering.hpp"
#include <iostream>

using namespace brain;
using namespace std;


struct base {virtual void foo() {std::cout << "base" << std::endl;}};
struct derived: public base {virtual void foo() {std::cout << "derived" << std::endl;}};

/// Main function for
/// C++ compiler.
int main()
{


    /* launch < test::test_suite < meta::test::member_test,
            meta::test::literal_test,
            meta::test::constkw_test,
            meta::test::pack_test,
            meta::test::function_test,
            meta::test::math_test,
            meta::test::conditional_test,
            test::object_test,
            test::component_test,
            test::monomorphe_test,
            test::shared_component_test/*,
          test::reference_test,
          test::system_test,
          test::smart_ptr_test,
          test::scanner_test,
          test::parser_test,
           *
     //     test::tree_maker_test>> ();
     */

    std::stack<std::string> st;
    st.push("Coucou");
    std::cout << st.top() << std::endl;


    serializerstream<char> ss;
    using attr =
        typename serializerstream<char>::attribute;

    object o;
    
    ss << o;

    auto && res =  xml_format<char>()(ss) ;

    std::cout << res << std::endl;
    std::cout << res << std::endl;

    return 0;
}
