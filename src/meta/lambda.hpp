#ifndef __BRAIN_META_LAMBDA_HPP__
# define __BRAIN_META_LAMBDA_HPP__

/// #include "map.hpp"
///#include "core.hpp"

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


        template<typename ... expressions_t>
        struct is_placeholder_expression
        {
            using type = 
                or_<type_<is_placeholder_expression<expressions_t>>...>;
        };


        template < template<typename ...> typename caller_t,
                 typename ... expressions_t >
        struct is_placeholder_expression<caller_t<expressions_t...>>
        {
            using type = or_<type_<is_placeholder_expression<expressions_t>>...>;
        };


        template < template<unsigned> typename placeholder_t,
                 unsigned _rank >
        struct is_placeholder_expression<placeholder_t<_rank>>
        {
            using type =
                is_same_ <
                placeholder_t<_rank>,
                placeholder<_rank> >;
        };


        template<typename type_t>
        struct is_placeholder_expression<type_t>
        {
            using type = false_;
        };


        namespace test_is_placeholder_expression
        {
            // using expression_t = if_t<_0_, _1_, _3_>;
            static_assert(v_<type_<is_placeholder_expression<_0_>>>, "");
        }

    }
}

#endif
