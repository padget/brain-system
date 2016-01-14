#ifndef __BRAIN_META_LAMBDA_HPP__
# define __BRAIN_META_LAMBDA_HPP__

/// #include "map.hpp"
#include "core.hpp"

namespace brain
{
    namespace meta
    {
        //// placeholders
        template<unsigned _u>
        struct placeholder;

        template<unsigned _u>
        using arg = placeholder<_u>;

        using _0_ = arg<0>;
        using _1_ = arg<1>;
        using _2_ = arg<2>;
        using _3_ = arg<3>;
        using _4_ = arg<4>;
        using _5_ = arg<5>;
        using _6_ = arg<6>;
        using _7_ = arg<7>;
        using _8_ = arg<8>;
        using _9_ = arg<9>;
        using _10_ = arg<10>;
        using _11_ = arg<11>;
        using _12_ = arg<12>;
        using _13_ = arg<13>;
        using _14_ = arg<14>;
        using _15_ = arg<15>;


        template<typename ... expressions_t>
        struct is_placeholder_expression:
                or_t<is_placeholder_expression<expressions_t>...>
        {
        };
        
        
        template<template<typename ...> typename caller_t, 
        typename ... expressions_t>
        struct is_placeholder_expression<caller_t<expressions_t...>>:
                or_t<is_placeholder_expression<expressions_t>...>
        {
        };


        template < template<unsigned> typename placeholder_t,
                 unsigned _rank >
        struct is_placeholder_expression<placeholder_t<_rank>>:
                        std::is_same <
                        placeholder_t<_rank>,
                        placeholder<_rank> >
        {
        };


        template<typename type_t>
        struct is_placeholder_expression<type_t>:
                std::false_type
        {
        };


        /*namespace test_is_placeholder_expression
        {
              // using expression_t = if_t<_0_, _1_, _3_>;
               static_assert(!v_<is_placeholder_expression<if_t<_0_, _0_, _0_>>>, "");
               static_assert(false, "";)
        }*/


        /* /// A lambda is a anonymous
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
        */

    }
}

#endif
