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

        template<typename index_t>
        using arg =
            placeholder<index_t>;


        using _0_ = arg<long_<0>>;
        using _1_ = arg<long_<1>>;
        using _2_ = arg<long_<2>>;
        using _3_ = arg<long_<3>>;
        using _4_ = arg<long_<4>>;
        using _5_ = arg<long_<5>>;
        using _6_ = arg<long_<6>>;
        using _7_ = arg<long_<7>>;
        using _8_ = arg<long_<8>>;
        using _9_ = arg<long_<9>>;
        using _10_ = arg<long_<10>>;
        using _11_ = arg<long_<11>>;
        using _12_ = arg<long_<12>>;
        using _13_ = arg<long_<13>>;
        using _14_ = arg<long_<14>>;
        using _15_ = arg<long_<15>>;


        namespace test_placeholder
        {
            static_assert(v_<is_same_<int, return_<_0_, int, double, char>>>, "");
            static_assert(v_<is_same_<double, return_<_1_, int, double, char>>>, "");
            static_assert(v_<is_same_<char, return_<_2_, int, double, char>>>, "");
            static_assert(v_<is_same_<nil, return_<_3_, int, double, char>>>, "");
        }







        namespace impl
        {
            template<typename type_t>
            struct is_placeholder_expression_
            {
                using type = false_;
            };

            template < template<typename ...> typename type_t,
                     typename ... args_t >
            struct is_placeholder_expression_<type_t<args_t...>>
            {
                using type =
                    or_<type_<is_placeholder_expression_<args_t>>...>;
            };

            template < template<typename > typename holder_t,
                     typename  _rank >
            struct is_placeholder_expression_<holder_t<_rank>>
            {
                using type =
                    meta::is_same_<meta::placeholder<_rank>, holder_t<_rank>>;
            };
        }


        template<typename type_t>
        using is_placeholder_expression_ =
            type_<impl::is_placeholder_expression_<type_t>>;


        namespace lazy
        {
            template<typename type_t>
            struct is_placeholder_expression_ :
                    function_<is_placeholder_expression_, type_t> {};
        }


        namespace test_is_placeholder
        {
            static_assert(v_<is_placeholder_expression_<_0_>>, "");
            static_assert(v_<is_placeholder_expression_<lazy::if_<lazy::if_<_1_, _1_, _1_>, int, int>>>, "");
        }




        namespace impl
        {
            template < typename placehold_expr_t,
                     typename ... args_t >
            struct bind;

            template < template<typename...> typename lfunc_t,
                     typename ... holders_t ,
                     typename ... args_t >
            struct bind<lfunc_t<holders_t...>, args_t...>
            {

                using type =
                    lfunc_t <
                    type_ <
                    eval_if_ <
                    meta::is_placeholder_expression_<holders_t>,
                    lazy::return_<holders_t, args_t...>,
                    lazy::idem_<holders_t> >> ... >;
            };


            template < typename lfunc_t>
            struct lambda;


            template < template<typename...> typename lfunc_t,
                     typename ... holders_t >
            struct lambda<lfunc_t<holders_t...>>
            {
                using type = lambda;/// Sur une piste... 
                
                template<typename ... args_t>
                using return_ =
                    type_<bind<lfunc_t<holders_t...>, args_t... >>;
            };
        }


        template<typename lfunc_t>
        using lambda =
            impl::lambda<lfunc_t>;


        namespace test_lambda
        {
            using is_int = lambda<lazy::is_same_<_0_, _2_>>;
            using res = return_<type_<is_int>, int, float, int>;
            static_assert(v_<res>, "");
        }







        namespace impl
        {
            template<typename lambda_t>
            struct is_lambda_;

            template < template<typename> typename lambda_t,
                     typename lfunc_t >
            struct is_lambda_<lambda_t<lfunc_t>>
            {
                using type =
                    meta::is_same_<meta::lambda<lfunc_t>, lambda_t<lfunc_t>>;
            };
        }

        template<typename lambda_t>
        using is_lambda_ =
            type_<impl::is_lambda_<lambda_t>>;


        namespace lazy
        {
            template<typename lambda_t>
            struct is_lambda_ :
                    function_<is_lambda_, lambda_t> {};
        }


        namespace test_is_lambda
        {
            static_assert(v_<is_lambda_<lambda<_0_>>>, "");
        }
    }
}

#endif
