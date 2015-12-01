/*
 * main.cpp
 *
 *  Created on: 27 oct. 2013
 *      Author: bmathieu
 */

#include "test/utest/utest.hpp"
#include "core/meta.hpp"
#include "core/core.hpp"
#include <iostream>

using namespace brain;
using namespace std;


/// Main function for
/// C++ compiler.
int main()
{ 
    
    std::cout << "Coucou" << std::endl;
    test::test_suite < meta::test::member_test,
         meta::test::literal_test,
         meta::test::constkw_test,
         meta::test::pack_test,
         meta::test::function_test,
         meta::test::math_test,
         meta::test::conditional_test,
         test::property_test,
         test::object_test, 
         test::reference_test/*,
         test::system_test,
         test::smart_ptr_test,
         test::scanner_test,
         test::parser_test,
          *
         test::tree_maker_test*/ > ()();

    return 0;
}
