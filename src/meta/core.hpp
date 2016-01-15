#ifndef __BRAIN_META_CORE_HPP__
# define __BRAIN_META_CORE_HPP__

#include <type_traits>
#include "macro.hpp"

namespace brain
{
    /// TODO Lazy of all metafunctions

    namespace meta
    {
        /// Type that
        /// represents
        /// nothing
        struct nil {};


        /// Alias for
        /// std::true_type
        using true_ =
            std::true_type;


        /// Alias for
        /// std::false_type
        using false_ =
            std::false_type;


        /// Wrapper for void
        template<typename ...>
        using void_ =
            void;


        /// Definition
        /// of pack
        template<typename ...>
        struct pack;


        /// //////////////////// ///
        /// Most common shortcut ///
        /// //////////////////// ///


        /// Access to type member
        /// of type_t. Evaluates
        /// the result of the meta
        /// function type_t
        has_(type)
        access_(type)


        /// Access to value
        /// member of type_t
        template<typename type_t>
        constexpr decltype(type_<type_t>::value) v_ =
            type_<type_t>::value;


        /// Access to type_t
        /// itself
        template<typename type_t>
        using idem_ = type_t;


        /// identity that
        /// returns the
        /// type_t itself
        template<typename type_t>
        struct identity_
        {
            using type =
                type_t;
        };


        /// type_ shortcut
        /// for std::is_same
        template < typename type_t,
                 typename other_t >
        using is_same_ =
            type_<std::is_same<type_t, other_t>>;



        /// ////////////////////////////// ///
        /// function_ : lazy instantiation ///
        /// ////////////////////////////// ///


        namespace impl
        {
            /// A function is
            /// the declaration
            /// of a signature of
            /// a meta function.
            template < template<typename ...> typename func_t,
                     typename args_t,
                     typename = void >
            struct function_;


            /// Specialization that
            /// expands the args_t
            /// for the future
            /// function evaluation
            template < template<typename ...> typename func_t,
                     typename ... args_t >
            struct function_ <
                    func_t,
                    pack<args_t...>,
                    void_<func_t<args_t...>> >
            {
                /// Only the call to
                /// type member compute
                /// its evaluation.
                using type =
                    func_t<args_t...>;
            };
        }

        /// Public exposition
        /// of the impl::function_
        template < template<typename ...> typename func_t,
                 typename ... args_t >
        using function_ =
            impl::function_ <
            func_t,
            pack<args_t... >>;

        /// Lazy declaration
        /// of type_ and
        /// has_type_member
        lazy_(type)


        /// Unitary Test
        /// of function_
        namespace test_function
        {
            template<typename type_t>
            using identity_function =
                function_<identity_, type_t>;

            template<typename type_t>
            using lazy_type =
                lazy::type_<type_t>;

            static_assert(v_<std::is_same<type_<type_<identity_function<int>>>, int>>, "");
            /// Example of lazy use :
            /// if this expression will be evaluated,
            /// the compilation will fail because of
            /// int has no member type ! So the type
            /// member of function_ demanding of the
            /// evaluation of the type member of int
            /// is not evaluated while the type of
            /// function_ is not used in code !
            static_assert(!v_<is_same_<lazy_type<int>, int>>, "");
            static_assert(v_<is_same_<type_<lazy::type_<function_<idem_, int>>>, int>>, "");
        }

        /// //////////////////////////////////////// ///
        /// function_class_ : lazy functor computing ///
        /// //////////////////////////////////////// ///


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


        /// Access to return_
        /// member of type_t
        template < typename type_r,
                 typename ... args_t >
        using return_ =
            typename type_r::
            template return_<args_t...>;


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
                    return_<func_t, args_t...>;
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
                    return_<func_t, return_<compose_<next_t, funcs_t...>, args_t...>>;
            };
        }


        /// Evaluates the result of
        /// impl::compose<funcs_t...>
        template < typename func_t,
                 typename ... funcs_t >
        using compose_ =
            impl::compose_<func_t, funcs_t...>;


        namespace lazy
        {
            /// Returns the signature
            /// of the composition that
            /// will be evaluated as
            /// later as possible
            template < typename func_t,
                     typename ... funcs_t >
            using compose_ =
                function_<compose_, func_t, funcs_t...>;
        }


        /// Unitary Test
        /// of compose_
        namespace test_compose
        {
            template<typename type_t>
            using is_int = is_same_<type_t, int>;
            using is_int_comp = compose_<function_class_<is_int>>;

            static_assert(v_<return_<is_int_comp, int>>, "");

            template<typename type_t>
            using is_true = is_same_<type_t, true_>;
            using is_int_true_compo = compose_<function_class_<is_true>, is_int_comp>;

            static_assert(v_<return_<is_int_true_compo, int>> , "");
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


        namespace lazy
        {
            /// Returns the signature
            /// of the front bind that
            /// will be evaluated as
            /// later as possible
            template < typename func_t,
                     typename ... front_args_t >
            using bind_front_ =
                function_<bind_front_, func_t, front_args_t...>;


            /// Returns the signature
            /// of the back binding that
            /// will be evaluated as
            /// later as possible
            template < typename func_t,
                     typename ... back_args_t >
            using bind_back_ =
                function_<bind_back_, func_t, back_args_t...>;
        }


        namespace test_bind_front_back
        {
            using is_float_front = bind_front_<function_class_<is_same_>, float>;
            using is_float_back = bind_back_<function_class_<is_same_>, float>;

            static_assert(v_<return_<is_float_front, float>>, "");
            static_assert(v_<return_<is_float_back, float>>, "");
            static_assert(!v_<return_<is_float_front, int>>, "");
            static_assert(!v_<return_<is_float_back, int>>, "");
        }



        /// ///////////////////////// ///
        /// Wrapper for literal types ///
        /// ///////////////////////// ///


        /// Shortcut for
        /// std::integral_constant
        template < typename literal_t,
                 literal_t _l >
        using igral_ =
            type_<std::integral_constant<literal_t, _l>>;


        /// Wrapper for bool
        template<bool _b>
        using bool_ =
            igral_<bool, _b>;



        /// Wrapper for short
        template<short _s>
        using short_ =
            igral_<short, _s>;


        /// Wrapper for unsigned short
        template<unsigned short _us>
        using ushort_ =
            igral_<unsigned short, _us>;


        /// Wrapper for char
        template<char _c>
        using char_ =
            igral_<char, _c>;


        /// Wrapper for int
        template<int _i>
        using int_ =
            igral_<int, _i>;


        /// Wrapper for long
        template<long _l>
        using long_ =
            igral_<long, _l>;


        /// Wrapper for long long
        template<long long _ll>
        using longlong_ =
            igral_<long long, _ll>;


        /// Wrapper for unsigned
        template<unsigned _u>
        using unsigned_ =
            igral_<unsigned, _u>;


        /// Wrapper for unsigned long
        template<unsigned long _ul>
        using unsignedl_ =
            igral_<unsigned long, _ul>;


        /// Wrapper for unsigned long long
        template<unsigned long long _ull>
        using unsignedll_ =
            igral_<unsigned long long, _ull>;


        /// Wrapper for size_t
        template<std::size_t _s>
        using size_t_ =
            igral_<std::size_t, _s>;


        /// /////////////////////// ///
        /// Logical wrapper feature ///
        /// /////////////////////// ///


        /// Wrapper for equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using equal_to_ =
            bool_ < v_<type_t>
            == v_<other_t >>;


        /// Wrapper for not equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using not_equal_to_ =
            bool_ < v_<type_t>
            != v_<other_t >>;


        /// Wrapper for greater
        /// operator
        template < typename type_t,
                 typename other_t >
        using greater_ =
            bool_ < (v_<type_t>
                     > v_<other_t>) >;


        /// Wrapper for less
        /// operator
        template < typename type_t,
                 typename other_t >
        using less_ =
            bool_ < (v_<type_t>
                     < v_<other_t>) >;


        /// Wrapper for greater equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using greater_equal_ =
            bool_ < (v_<type_t>
                     >= v_<other_t>) >;


        /// Wrapper for less equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using less_equal_ =
            bool_ < (v_<type_t>
                     <= v_<other_t>) >;


        /// Wrapper for bit and
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_and_ =
            bool_ < v_<type_t>
            & v_<other_t >>;


        /// Wrapper for bit or
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_or_ =
            bool_ < v_<type_t>
            | v_<other_t >>;


        /// Wrapper for bit xor
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_xor_ =
            bool_ < v_<type_t>
            ^ v_<other_t >>;


        /// Wrapper for bit not
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_not_ =
            bool_ < ~v_<type_t >>;


        namespace impl
        {
            /// Returns std::true_type
            /// if all bools_t are true
            template <typename... bools_t>
            struct and_;


            /// Specialisation for
            /// _and_ that returns
            /// std::true_type for
            /// default case.
            template <>
            struct and_<> :
                    true_
            {
            };


            template < typename test_t,
                     typename ... other_t >
            struct and_<test_t, other_t...> :
                    bool_<v_<test_t> and v_<type_<and_<other_t...>>>>
            {
            };

        }

        /// Evaluates the result
        /// of type_<_and_<bools_t...>>
        template<typename ... bools_t>
        using and_ =
            type_<impl::and_<bools_t...>>;


        namespace impl
        {
            /// Returns std::true_type
            /// if one or more bools_t
            /// is true
            template <typename... bools_t>
            struct or_;


            /// Specialisation for
            /// _or_ that returns
            /// std::false_type
            /// for default case
            template <>
            struct or_<> :
                    true_
            {
            };


            /// Specialisation for
            /// _and_ that returns
            /// std::false_type if
            /// all of bools_t is
            /// false
            template < typename bool_t,
                     typename... bools_t >
            struct or_<bool_t, bools_t...> :
                    bool_<v_<bool_t> or v_<type_<or_<bools_t...>>>>

            {
            };
        }

        /// Evaluates the result
        /// of type_<_or_<bools_t...>>
        template<typename ... bools_t>
        using or_ =
            type_<impl::or_<bools_t...>>;


        /// Negates the bool_t
        template<typename bool_t>
        using not_ =
            bool_ < !v_<bool_t >>;


        namespace lazy
        {
            /// Evaluates the result
            /// of type_<and_<bools_t...>>
            template<typename ... bools_t>
            using and_ =
                function_<and_, bools_t...>;


            template<typename ... bools_t>
            using or_ =
                function_<or_, bools_t...>;


            template<typename bool_t>
            using not_ =
                function_<not_, bool_t>;
        }


        /// ////////////////////////////// ///
        /// Wrapper for constness keywords ///
        /// ////////////////////////////// ///


        /// Wrapper for sizeof
        template<typename type_t>
        using sizeof_ =
            size_t_<sizeof(type_t)>;


        /// Wrapper for sizeof...
        template<typename ... types_t>
        using sizeof_pack_ =
            size_t_<sizeof...(types_t)>;


        /// Wrapper for alignof
        template<typename type_t>
        using alignof_ =
            size_t_<alignof(type_t)>;


        namespace lazy
        {
            template<typename type_t>
            using sizeof_ =
                function_<sizeof_, type_t>;


            template<typename ... types_t>
            using sizeof_pack_ =
                function_<sizeof_pack_, types_t...>;


            template<typename type_t>
            using alignof_ =
                function_<alignof_, type_t>;
        }


        /// /////////////////////// ///
        /// Keyword Feature Remover ///
        /// /////////////////////// ///


        ///
        template<typename type_t>
        using remove_const_t =
            std::remove_const_t<type_t>;


        ///
        template<typename type_t>
        using remove_volatile_t =
            std::remove_volatile_t<type_t>;


        ///
        template<typename type_t>
        using remove_reference_t =
            std::remove_reference_t<type_t>;


        ///
        template<typename type_t>
        using remove_pointer_t =
            std::remove_pointer_t<type_t>;


        ///
        template<typename type_t>
        using extract_basic_type_t =
            remove_const_t <
            remove_pointer_t <
            remove_reference_t<type_t> > >;


        /// ///////////////////////////// ///
        /// Mathematical wrapper features ///
        /// ///////////////////////////// ///


        /// Wrapper for incrementing
        template<typename type_t>
        using inc_ =
            igral_ <
            decltype(v_<type_t> + 1),
            v_<type_t> + 1 >;


        /// Wrapper for decrementing
        template<typename type_t>
        using dec_ =
            igral_ <
            decltype(v_<type_t> - 1),
            v_<type_t> - 1 >;


        /// Wrapper for additing
        template < typename type_t,
                 typename other_t >
        using plus_ =
            igral_ <
            decltype(v_<type_t> + v_<other_t>),
            v_<type_t> + v_<other_t >>;


        /// Wrapper for substracting
        template < typename type_t,
                 typename other_t >
        using minus_ =
            igral_ <
            decltype(v_<type_t> - v_<other_t>),
            v_<type_t> - v_<other_t >>;


        /// Wrapper for multiplying
        template < typename type_t,
                 typename other_t >
        using multiplies_ =
            igral_ <
            decltype(v_<type_t> * v_<other_t>),
            v_<type_t> * v_<other_t >>;


        /// Wrapper for dividing
        template < typename type_t,
                 typename other_t >
        using divides_ =
            igral_ <
            decltype(v_<type_t> / v_<other_t>),
            v_<type_t> / v_<other_t >>;


        /// Wrapper for negating
        template <typename type_t>
        using negate_ =
            igral_ <
            decltype(-v_<type_t>),
            -v_<type_t >>;


        /// Wrapper for moduling
        template < typename type_t,
                 typename other_t >
        using modulus_ =
            igral_ <
            decltype(v_<type_t> % v_<other_t>),
            v_<type_t> % v_<other_t >>;


        namespace lazy
        {
            /// Wrapper for incrementing
            template<typename type_t>
            using inc_ =
                function_<inc_, type_t>;


            /// Wrapper for decrementing
            template<typename type_t>
            using dec_ =
                function_<dec_, type_t>;


            /// Wrapper for additing
            template < typename type_t,
                     typename other_t >
            using plus_ =
                function_<plus_, type_t, other_t>;


            /// Wrapper for substracting
            template < typename type_t,
                     typename other_t >
            using minus_ =
                function_<minus_, type_t, other_t>;


            /// Wrapper for multiplying
            template < typename type_t,
                     typename other_t >
            using multiplies_ =
                function_<multiplies_, type_t, other_t>;


            /// Wrapper for dividing
            template < typename type_t,
                     typename other_t >
            using divides_ =
                function_<divides_, type_t, other_t>;


            /// Wrapper for negating
            template <typename type_t>
            using negate_ =
                function_<negate_, type_t>;


            /// Wrapper for moduling
            template < typename type_t,
                     typename other_t >
            using modulus_ =
                function_<modulus_, type_t, other_t>;
        }


        /// ////////////// ///
        /// Type selection ///
        /// ////////////// ///

        /// TODO Test unitaire pour selection

        namespace impl
        {
            /// Type selector
            template<typename ...>
            struct if_;


            /// Type selector
            /// specialisation that
            /// returns void
            /// if_t is true
            template<typename test_t>
            struct if_<test_t> :
                    std::enable_if<v_<test_t>>
            {
            };


            /// Type selector
            /// specialisation that
            /// returns then_t
            /// if_t is true
            template < typename test_t,
                     typename then_t >
            struct if_<test_t, then_t>:
                    std::enable_if<v_<test_t>, then_t>
            {
            };


            /// Type selector
            /// specialisation that
            /// returns then_t
            /// if_t is true
            /// else else_t
            template < typename test_t,
                     typename then_t,
                     typename else_t >
            struct if_<test_t, then_t, else_t>:
                    std::conditional<v_<test_t>, then_t, else_t>
            {
            };

        }


        /// Evaluates the result
        /// of type_<_if_<args_t...>>
        template<typename ... args_t>
        using if_ =
            type_<impl::if_<args_t...>>;


        /// Evaluates the result
        /// of if_<bool_<_b>, args_t... >
        template < bool _b,
                 typename... args_t >
        using if_c =
            if_<bool_<_b>, args_t...>;


        /// Evaluates the result
        /// of if_<if_t, then_t, else_t>
        template < typename test_t,
                 typename then_t,
                 typename else_t >
        using select_ =
            if_<test_t, then_t, else_t> ;


        /// Evaluates the result
        /// of if_c<_b, then_t, else_t>
        template < bool _b,
                 typename then_t,
                 typename else_t >
        using select_c =
            if_c<_b, then_t, else_t> ;


        namespace lazy
        {
            /// Evaluates the result
            /// of type_<_if_<args_t...>>
            template<typename ... args_t>
            using if_ =
                function_<if_, args_t...>;


            /// Evaluates the result
            /// of if_<if_t, then_t, else_t>
            template < typename test_t,
                     typename then_t,
                     typename else_t >
            using select_ =
                if_<test_t, then_t, else_t> ;
        }


        /// ///////////// ///
        /// Pack Features ///
        /// ///////////// ///


        /// Main support of the
        /// parameters pack
        template<typename ... items_t>
        struct pack
        {
            using size =
                sizeof_pack_<items_t...>;
        };


        /// size member
        /// accessor
        template<typename sequence_t>
        using size_ =
            typename sequence_t::size;


        namespace impl
        {
            /// Definition of
            /// push_back_t_
            template < typename sequence_t,
                     typename type_t >
            struct push_back_;


            /// Pushes type_t at
            /// the end of
            /// sequence_t
            template < template<typename...> typename sequence_t,
                     typename ... items_t,
                     typename type_t >
            struct push_back_ <
                    sequence_t<items_t...>,
                    type_t >
            {
                using type =
                    sequence_t<items_t..., type_t>;
            };
        }

        /// type_ shortcut for
        /// push_back_t_
        template < typename sequence_t,
                 typename type_t >
        using push_back_ =
            type_<impl::push_back_<sequence_t, type_t>>;


        namespace lazy
        {
            template < typename sequence_t,
                     typename type_t >
            using push_back_ =
                function_<push_back_, sequence_t, type_t>;
        }

        namespace test_push_back
        {
            using seq_t = pack<int, short>;

            static_assert(v_<std::is_same<pack<int, short, double>, push_back_<seq_t, double>>>, "");
        }


        namespace impl
        {
            /// Definition of
            /// push_front_
            template < typename sequence_t,
                     typename type_t >
            struct push_front_;


            /// Pushes type_t at
            /// the front of
            /// sequence_t
            template < template<typename...> typename sequence_t,
                     typename ... items_t,
                     typename type_t >
            struct push_front_ <
                    sequence_t<items_t...>,
                    type_t >
            {
                using type =
                    sequence_t<type_t, items_t...>;
            };
        }

        /// type_ shortcut for
        /// push_front_
        template < typename sequence_t,
                 typename type_t >
        using push_front_ =
            type_<impl::push_front_<sequence_t, type_t>>;


        namespace lazy
        {
            template < typename sequence_t,
                     typename type_t >
            using push_front_ =
                function_<push_front_, sequence_t, type_t>;
        }


        namespace test_push_front
        {
            using seq_t = pack<int, short>;

            static_assert(v_<is_same_<pack<double, int, short>, push_front_<seq_t, double>>>, "");
        }


        template<typename pack_t>
        struct unpack_t_;
    }
}

#endif
