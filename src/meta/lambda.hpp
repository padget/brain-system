#ifndef __BRAIN_META_LAMBDA_HPP__
# define __BRAIN_META_LAMBDA_HPP__


//#include "core.hpp"

namespace brain
{
    namespace meta
    {
        //// placeholders

        template<unsigned _u>
        struct placeholder {};

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

            template < template<unsigned> typename holder_t,
                     unsigned _rank >
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
            template<typename lfunc_t>
            struct lambda;


            template < template<typename... > typename lfunc_t,
                     typename ... args_t >
            struct lambda<lfunc_t<args_t...>>
            {
                using type = lfunc_t<args_t...>;
            };
        }


        template<typename lfunc_t>
        using lambda =
            type_<impl::lambda<lfunc_t>>;

        namespace lazy
        {
            template<typename lfunc_t>
            struct lambda :
                function_<meta::lambda, lfunc_t>{}; 
        }

        namespace test_lambda
        {
            static_assert(v_<is_placeholder_expression_<lambda<lazy::if_<lazy::if_<_1_, _1_, _1_>, _0_>>>>, "");
        }
    }
}

#endif
