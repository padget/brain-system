#ifndef __BRAIN_META_CORE_FUNCTIONCLASS_HPP__
# define  __BRAIN_META_CORE_FUNCTIONCLASS_HPP__

# include "base.hpp"
# include "math.hpp"
# include "select.hpp"
 
namespace brain
{
    namespace meta
    {
        namespace core
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
                    type_<function_<func_t, args_t...>>;
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
            template<typename index_t>
            struct placeholder;


            /// Predefined placeholders
            /// from 1 to 15
            using _0_ = placeholder<long_<0>>;
            using _1_ = placeholder<long_<1>>;
            using _2_ = placeholder<long_<2>>;
            using _3_ = placeholder<long_<3>>;
            using _4_ = placeholder<long_<4>>;
            using _5_ = placeholder<long_<5>>;
            using _6_ = placeholder<long_<6>>;
            using _7_ = placeholder<long_<7>>;
            using _8_ = placeholder<long_<8>>;
            using _9_ = placeholder<long_<9>>;
            using _10_ = placeholder<long_<10>>;
            using _11_ = placeholder<long_<11>>;
            using _12_ = placeholder<long_<12>>;
            using _13_ = placeholder<long_<13>>;
            using _14_ = placeholder<long_<14>>;
            using _15_ = placeholder<long_<15>>;


            namespace impl
            {
                template<typename type_t>
                struct is_placeholder_expression_
                {
                    using type =
                        false_;
                };

                template < template<typename ...> typename type_t,
                         typename ... args_t >
                struct is_placeholder_expression_<type_t<args_t...>>
                {
                    using type =
                        type_<or_<type_<is_placeholder_expression_<args_t>>...>>;
                };

                template < template<typename> typename holder_t,
                         typename  _rank >
                struct is_placeholder_expression_<holder_t<_rank>>
                {
                    using type =
                        is_same_<placeholder<_rank>, holder_t<_rank>>;
                };
            }


            template<typename type_t>
            using is_placeholder_expression_ =
                type_<impl::is_placeholder_expression_<type_t>>;


            namespace impl
            {
                template<typename lfunc_t>
                struct lambda;


                template < typename func_r,
                         typename ... holders_t >
                struct bind_;


                template < typename func_r,
                         typename is_placed_t,
                         typename ... args_t >
                struct return_;


                template < typename func_r,
                         typename ... args_t >
                struct return_<func_r, false_, args_t...>
                {
                    using type =
                        typename func_r::template return_<args_t...>;
                };


                template < template<typename ...> typename func_t,
                         typename ... holders_t,
                         typename ... args_t >
                struct  return_<func_t<holders_t...>, false_, args_t...>
                {
                    using type =
                        typename func_t<holders_t...>::template return_<args_t...>;
                };


                template < typename func_t,
                         typename ... args_t >
                struct return_<lambda<func_t>, true_, args_t...>
                {
                    using type =
                        type_<type_<return_<type_<lambda<func_t>>, true_, args_t...>>>;
                };


                template < typename index_t,
                         typename ... args_t >
                struct  return_<placeholder<index_t>, true_, args_t...>
                {
                    using type =
                        typename placeholder<index_t>::template return_<args_t...>;
                };


                template < template<typename ...> typename func_t,
                         typename ... holders_t,
                         typename ... args_t >
                struct  return_<func_t<holders_t...>, true_, args_t...>
                {
                    using bind =
                        bind_<function_class_<func_t>, holders_t...>;
                    using type =
                        type_<type_<return_<type_<bind>, false_, args_t...>>>;
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
                         typename ... holders_t >
                struct bind_
                {

                    using type =
                        bind_;

                    template<typename ... reals_t>
                    using return_  =
                        return_ <
                        func_r,
                        core::is_placeholder_expression_<func_r>,
                        core::eval_if_ <
                        core::is_placeholder_expression_<holders_t>,
                        return_<holders_t, core::is_placeholder_expression_<holders_t>, reals_t...>,
                        core::function_<idem_, holders_t>
                        > ...
                        >;
                };


                template <typename lfunc_t>
                struct lambda;


                template < template<typename...> typename lfunc_t,
                         typename ... holders_t >
                struct lambda<lfunc_t<holders_t...>>
                {
                    using type =
                        bind_<function_class_<lfunc_t>, holders_t...> ;

                    template<typename ... args_t>
                    using return_ =
                        type_<type_<core::return_<type, core::is_placeholder_expression_<type>, args_t...>>>;
                };
            }


            template < typename func_r,
                     typename ... holders_t >
            using bind_ =
                type_<impl::bind_<func_r, holders_t...>>;


            template<typename lfunc_t>
            using lambda =
                impl::lambda<lfunc_t>;


            namespace impl
            {
                template<typename lambda_t>
                struct is_lambda_;

                template < template<typename> typename lambda_t,
                         typename lfunc_t >
                struct is_lambda_<lambda_t<lfunc_t>>
                {
                    using type =
                        core::is_same_<core::lambda<lfunc_t>, lambda_t<lfunc_t>>;
                };
            }

            template<typename lambda_t>
            using is_lambda_ =
                type_<impl::is_lambda_<lambda_t>>;


            namespace test_is_lambda
            {
                static_assert(v_<is_lambda_<lambda<_0_>>>, "");
            }




            /// Unitary Test
            /// of function_class_
            namespace test_function_class
            {
                template<typename type_t>
                using is_int =
                    is_same_<type_t, int>;

                using is_int_function =
                    function_class_<is_int>;

                static_assert(v_<return_<is_int_function, int>>, "");
            }


            /// //////////////////////////// ///
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
            }


            /// ///////////////////////// ///
            /// Basic bind front and back ///
            /// ///////////////////////// ///


            /// Meta function that
            /// binds the front_args_t...
            /// at the beginning of
            /// the parameters of the
            /// meta function func_t
            template < typename func_t,
                     typename... front_args_t >
            struct bind_front_
            {
                template<typename ... args_t>
                using return_ =
                    return_<func_t, front_args_t..., args_t...>;
            };


            /// Metafunction that
            /// binds the back_args_t...
            /// at the ending of
            /// the parameters of the
            /// meta function func_t
            template < typename func_t,
                     typename ... back_args_t >
            struct bind_back_
            {
                template<typename ... args_t>
                using return_ =
                    return_<func_t, args_t..., back_args_t...>;
            };
            

            namespace test_bind_front_back
            {
                using is_float_front = bind_front_<function_class_<is_same_>, float>;
                using is_float_back = bind_back_<function_class_<is_same_>, float>;

                static_assert(v_<return_<is_float_front, float>>, "");
                static_assert(v_<return_<is_float_back, float>>, "");
                static_assert(!v_<return_<is_float_front, int>>, "");
                static_assert(!v_<return_<is_float_back, int>>, "");
            }

        }
    }
}

#endif
