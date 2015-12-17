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
    std::cout << sizeof(std::function<void()>);

    launch < test::test_suite < meta::test::member_test,
           meta::test::literal_test,
           meta::test::constkw_test,
           meta::test::pack_test,
           meta::test::function_test,
           meta::test::math_test,
           meta::test::conditional_test,
           test::property_value_test,
           test::property_cvalue_test,
           test::property_pointer_test,
           test::object_test,
           test::marshalling_test/*,
          test::reference_test,
          test::system_test,
          test::smart_ptr_test,
          test::scanner_test,
          test::parser_test,

   test::tree_maker_test*/ >> ();

    return 0;
}
