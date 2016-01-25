#ifndef __BRAIN_META_LAMBDA_HPP__
# define __BRAIN_META_LAMBDA_HPP__

#include "sequence.hpp"

namespace brain
{
    namespace meta
    {
        /// //////////// ///
        /// placeholders ///
        /// //////////// ///



        template<typename  index_t>
        struct placeholder
        {
            template<typename ... args_t>
            using return_ =
                item_<at_<forward_list<args_t...>, index_t>>;
        };



        namespace test_placeholder
        {
            static_assert(v_<is_same_<int, return_<_0_, int, double, char>>>, "");
            static_assert(v_<is_same_<double, return_<_1_, int, double, char>>>, "");
            static_assert(v_<is_same_<char, return_<_2_, int, double, char>>>, "");
            static_assert(v_<is_same_<nil, return_<_3_, int, double, char>>>, "");
        }


        namespace test_lambda
        {
        }


    }
}

#endif
