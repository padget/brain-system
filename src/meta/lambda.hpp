#ifndef __BRAIN_META_LAMBDA_HPP__
# define __BRAIN_META_LAMBDA_HPP__

#include "map.hpp"

namespace brain
{
    namespace meta
    {
        /// placeholders
        template<unsigned _u>
        struct placeholder;

        using _0_ = placeholder<0>;
        using _1_ = placeholder<1>;
        using _2_ = placeholder<2>;
        using _3_ = placeholder<3>;
        using _4_ = placeholder<4>;
        using _5_ = placeholder<5>;
        using _6_ = placeholder<6>;
        using _7_ = placeholder<7>;
        using _8_ = placeholder<8>;
        using _9_ = placeholder<9>;
        using _10_ = placeholder<10>;
        using _11_ = placeholder<11>;
        using _12_ = placeholder<12>;
        using _13_ = placeholder<13>;
        using _14_ = placeholder<14>;


        /// A lambda is a anonymous
        /// meta function that can
        /// support placeholding
        /// feature between lambda
        /// arguments and meta function
        /// func_t arguments
        template < typename lambda_args_t,
                 typename func_t ,
                 typename func_args_t >
        struct lambda;


        /// Specialisation for
        /// lambda that distings
        /// each type of lambda_args_t
        /// and of func_args_t
        template < typename ... lambda_args_t,
                 typename func_t,
                 typename ... func_args_t >
        struct lambda < list<lambda_args_t...>,
                func_t, list<func_args_t... >>
        {
            using lambda_args_ =
                list<lambda_args_t...>;
            using func_args_ =
                list<func_args_t...>;

            template<typename ... args_t>
            using return_ =
                expand_t<func_t, map_replace_t<func_args_, to_map_t<lambda_args_, list<args_t...>>>>;
        };


    }
}

#endif
