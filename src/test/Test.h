/*
 * Test.h
 *
 *  Created on: 10 avr. 2015
 *      Author: bmathieu
 */

#ifndef TEST_TEST_H_
#define TEST_TEST_H_

#include "../core.h"

namespace brain
{
	namespace test
	{
		template <typename test>
		class Assert
		{
			public:
				template <typename str, typename = brain::enable_if_stringable_t<str>>
				static void assert(const std::string& test_name, bool exp, str&& errmess)
				{
					if (!exp)
						Logger<Assert<test>>::error(
								test_name + " ... KO \t [reason] : " + (string) errmess);
					else
						Logger<Assert<test>>::info(test_name + " ... OK");
				}

				template <typename str, typename = brain::enable_if_stringable_t<str>>
				static void manual(const std::string& test_name, str&& mess)
				{
					Logger<Assert<test>>::warn(
							test_name + "... OK/KO ? \t [message] : " + (string) mess);
				}
		};
	}
}

#endif /* TEST_TEST_H_ */
