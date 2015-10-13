///*
// * TestLQL.hpp
// *
// *  Created on: 16 avr. 2015
// *      Author: bmathieu
// */
//
//#ifndef TEST_UTEST_TESTLQL_HPP_
//#define TEST_UTEST_TESTLQL_HPP_
//
//#include "../../data.h"
//
//namespace brain
//{
//	namespace test
//	{
//		namespace lql
//		{
//			class TestLQL
//			{
//			};
//
//			template <typename asserter>
//			static void testLQL_Lambda_Plus()
//			{
//				data::lql::bti_Expression_sptr d1 { new data::lql::bti_Double(0.1) };
//				data::lql::bti_Expression_sptr d2 { new data::lql::bti_Double(0.2) };
//
//				data::lql::bti_Expression_sptr i1 { new data::lql::bti_Integer(1) };
//				data::lql::bti_Expression_sptr i2 { new data::lql::bti_Integer(2) };
//
//				data::lql::bti_Expression_sptr s1 { new data::lql::bti_String("Str 1") };
//				data::lql::bti_Expression_sptr s2 { new data::lql::bti_String("Str 2") };
//
//				data::lql::bti_Expression_sptr da1 { new data::lql::bti_Date(date(2015, 12, 25)) };
//				data::lql::bti_Expression_sptr da2 { new data::lql::bti_Date(date(2015, 12, 26)) };
//
//				data::lql::bti_Expression_sptr l1 { new data::lql::bti_List( { d1, d2 }) };
//				data::lql::bti_Expression_sptr l2 { new data::lql::bti_List( { i1, i2 }) };
//				data::lql::bti_Expression_sptr l3 { new data::lql::bti_List( { s1, s2 }) };
//				data::lql::bti_Expression_sptr l4 { new data::lql::bti_List( { da1, da2 }) };
//
//				data::lql::bti_Expression_sptr l5 { new data::lql::bti_List( { l1, l2, l3, l4 }) };
//
//				data::lql::bti_List_sptr ls1 = brain::shared_conv<brain::data::lql::bti_List>(l1);
//				data::lql::bti_List_sptr ls2 = brain::shared_conv<brain::data::lql::bti_List>(l2);
//				data::lql::bti_List_sptr ls3 = brain::shared_conv<brain::data::lql::bti_List>(l3);
//				data::lql::bti_List_sptr ls4 = brain::shared_conv<brain::data::lql::bti_List>(l4);
//				data::lql::bti_List_sptr ls5 = brain::shared_conv<brain::data::lql::bti_List>(l5);
//
//				data::lql::bti_Expression_sptr plus { new data::lql::bti_Plus(ls1) };
//
//				asserter::assert("test 1 Lambda PLUS", brain::type<brain::data::lql::bti_Double>::equals(plus->eval().get()),
//						"Le type du résultat doit être double");
//
//				data::lql::bti_Expression_sptr plus2 { new data::lql::bti_Plus(ls2) };
//				asserter::assert("test 2 Lambda PLUS", brain::type<brain::data::lql::bti_Integer>::equals(plus2->eval().get()),
//						"Le type du résultat doit être integer");
//
//				data::lql::bti_Expression_sptr plus3 { new data::lql::bti_Plus(ls3) };
//				asserter::assert("test 3 Lambda PLUS", brain::type<brain::data::lql::bti_String>::equals(plus3->eval().get()),
//						"Le type du résultat doit être string");
//
//				data::lql::bti_Expression_sptr plus4 { new data::lql::bti_Plus(ls5) };
//				asserter::assert("test 4 Lambda PLUS", brain::type<brain::data::lql::bti_List>::equals(plus4->eval().get()),
//						"Le type du résultat doit être list");
//			}
//		}
//	}
//}
//
//#endif /* TEST_UTEST_TESTLQL_HPP_ */
