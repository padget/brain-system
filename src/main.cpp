/*
 * main.cpp
 *
 *  Created on: 27 oct. 2013
 *      Author: bmathieu
 */

#include "test/utest/utest.hpp"

using namespace brain;
using namespace std;



int main()
{
    test::test_suite < test::system_test,
         test::smart_ptr_test,
         test::scanner_test,
         test::parser_test, 
         test::tree_maker_test> ()();

    return (int) exitcode::WELL;
}
