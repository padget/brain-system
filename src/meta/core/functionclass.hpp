#ifndef __BRAIN_META_CORE_FUNCTIONCLASS_HPP__
# define  __BRAIN_META_CORE_FUNCTIONCLASS_HPP__

# include "base.hpp"
# include "math.hpp"
# include "select.hpp"
# include "pack.hpp"
# include <utility>

namespace meta
{

    /// function_class_ is
    /// a metafunction which
    /// the evaluation is in
    /// two times :
    ///  - Configuration with
    ///    parameters of the type func_t
    ///    (not lazy instantiation)
    ///  - Call of the member
    ///    return_ that represents
    ///    the results of the call.
    /// So it can be considered
    /// as a configurable metafunction
    template<template<typename ...> typename func_t>
    struct function_class_
    {
        /// Returns the result
        /// of func_t
        template<typename ... args_t>
        using return_ =
            eval_if_ <
            has_type_member<type_<function_<func_t, args_t...>>>,
            function_<type_, type_<function_<func_t, args_t...>>>,
            type_<function_<func_t, args_t...>>
            >;
    };


    /// ////////////////////// ///
    /// Placeholder expression ///
    /// ////////////////////// ///


    /// Placeholder used
    /// for lambda and
    /// placeholding
    /// expression in
    /// declaration and
    /// call instantiation
    template<int index_t>
    struct placeholder:
            int_<index_t>
    {
        template<typename ... args_t>
        using return_ =
            at_<pack<args_t...>, int_<index_t>>;
    };


    /// Predefined placeholders
    /// from 1 to 15
    using ___ = placeholder < -1 >; 
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
    using _15_ = placeholder<15>;


    namespace impl
    {
        template<typename type_t>
        struct is_placeholder_expression_
        {
            using type =
                meta::false_;
        };


        template < template<typename ...> typename type_t,
                 typename ... args_t >
        struct is_placeholder_expression_<type_t<args_t...>>
        {
            using type =
                meta::or_<meta::type_<is_placeholder_expression_<args_t>>...>;
        };


        template < template<int> typename holder_t,
                 int  _rank >
        struct is_placeholder_expression_<holder_t<_rank>>
        {
            using type =
                meta::is_same_<meta::placeholder<_rank>, holder_t<_rank>>;
        };
    }


    template<typename type_t>
    using is_placeholder_expression_ =
        type_<impl::is_placeholder_expression_<type_t>>;


    template<typename type_t>
    using is_neutral_placeholder_ =
        is_same_<___, type_t>;


    namespace impl
    {
        template<typename lfunc_t>
        struct lambda;


        template < typename func_r,
                 typename holders_t,
                 typename indexes_t >
        struct bind_;


        template < typename func_r,
                 typename is_placed_t,
                 typename ... args_t >
        struct return_;


        /// Specialization for
        /// metafunction class
        /// that not be made of
        /// placeholders
        template < typename func_r,
                 typename ... args_t >
        struct return_<func_r, meta::false_, args_t...>
        {
            using type =
                typename func_r::template return_<args_t...>;
        };



        template < template<typename ...> typename func_t,
                 typename ... holders_t,
                 typename ... args_t >
        struct  return_<func_t<holders_t...>, true_, args_t...>
        {
            using bind =
                bind_<function_class_<func_t>, pack<holders_t...>, std::make_index_sequence<sizeof...(holders_t)>>;
            using type =
                meta::type_<return_<bind, meta::true_, args_t...>>;
        };


        template < int index_t,
                 typename ... args_t >
        struct  return_<meta::placeholder<index_t>, meta::true_, args_t...>
        {
            using type =
                typename meta::placeholder<index_t>::template return_<args_t...>;
        };


        template < typename func_r,
                 typename ... bind_args_t,
                 std::size_t... indexes_t,
                 typename ... args_t >
        struct return_<bind_<func_r, pack<bind_args_t...>, std::index_sequence<indexes_t...>>, true_, args_t...>
        {
            using type =
                typename bind_<func_r, pack<bind_args_t...>, std::index_sequence<indexes_t...>>::template return_<args_t...>;
        };
    }

    /// Access to return_
    /// member of type_t
    template < typename type_r,
             typename ... args_t >
    using return_ =
        type_<impl::return_<type_r, is_placeholder_expression_<type_r>, args_t...>>;


    namespace impl
    {
        template < typename func_r,
                 typename ... holders_t,
                 std::size_t ... indexes_t >
        struct bind_ <
                func_r,
                pack<holders_t...>,
                std::index_sequence<indexes_t... >>
        {
            using type =
                bind_;

            template<typename ... reals_t>
            using return_  =
                typename func_r::
                template return_ <
                meta::eval_if_ <
                    meta::is_placeholder_expression_<holders_t> ,
                    lazy::eval_if_<
                        meta::is_neutral_placeholder_<holders_t>, 
                        return_<placeholder<indexes_t>, true_, reals_t...>,
                        return_<holders_t, meta::is_placeholder_expression_<holders_t>, reals_t...>>,
                    meta::function_<idem_, holders_t >> ... >;
        };
    }


    template < typename func_r,
             typename ... holders_t >
    using bind_ =
        type_<impl::bind_<func_r, pack<holders_t...>, std::make_index_sequence<sizeof...(holders_t)>>>;


    namespace impl
    {
        template<typename func_t>
        struct lambda;

        template < template<typename ...> typename func_t,
                 typename ... holders_t >
        struct lambda <func_t<holders_t...>>
        {
            using type = bind_<function_class_<func_t>, pack<holders_t...>, std::make_index_sequence<sizeof...(holders_t)>>;

            template<typename ... reals_t>
            using return_ =
                typename type::
                template return_<reals_t...>;
        };
    }

    template<typename lfunc_t>
    using lambda =
        type_<impl::lambda<lfunc_t>>;


    namespace lazy
    {
        template<typename lfunc_t>
        struct lambda:
                meta::function_<meta::lambda, lfunc_t> {};
    }



    /*   /// //////////////////////////// ///
       /// Composition of metafunctions ///
       /// //////////////////////////// ///


       namespace impl
       {
           /// A meta function that
           /// returns the composition
           /// of other several meta
           /// functions funcs_t
           template < typename func_t,
                    typename ... funcs_t >
           struct compose_;


           /// Specialisation for
           /// compose that takes
           /// a single meta function
           template<typename func_t>
           struct compose_<func_t>
           {
               template<typename ... args_t>
               using return_ =
                   core::return_<func_t, args_t...>;
           };


           /// Specialisation for
           /// compose that take
           /// more one meta functions
           template < typename func_t,
                    typename next_t,
                    typename ... funcs_t >
           struct compose_<func_t, next_t, funcs_t...>
           {
               template<typename ... args_t>
               using return_ =
                   core::return_<func_t, core::return_<compose_<next_t, funcs_t...>, args_t...>>;
           };
       }


       /// Evaluates the result of
       /// impl::compose<funcs_t...>
       template < typename func_t,
                typename ... funcs_t >
       using compose_ =
           impl::compose_<func_t, funcs_t...>;

       /// Unitary Test
       /// of compose_
       namespace test_compose
       {
           template<typename type_t>
           using is_int = is_same_<type_t, int>;
           using is_int_comp = compose_<function_class_<is_int>>;

           static_assert(v_<core::return_<is_int_comp, int>>, "");

           template<typename type_t>
           using is_true = is_same_<type_t, true_>;
           using is_int_true_compo = compose_<function_class_<is_true>, is_int_comp>;

           static_assert(v_<core::return_<is_int_true_compo, int>> , "");
       } */

}

#endif
