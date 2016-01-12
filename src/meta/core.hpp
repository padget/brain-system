#ifndef __BRAIN_META_CORE_HPP__
# define __BRAIN_META_CORE_HPP__

#include <type_traits>

namespace brain
{
    namespace meta
    {
        struct nil {};


        /// //////////////////// ///
        /// Most common shortcut ///
        /// //////////////////// ///


        /// Access to type member
        /// of type_t
        template<typename type_t>
        using t_ =
            typename type_t::type;


        /// Access to value member
        /// of type_t
        template<typename type_t>
        constexpr decltype(t_<type_t>::value) v_ =
            t_<type_t>::value;


        /// Wrapper for void
        template<typename ...>
        using void_t =
            void;


        /// ////////////////////////// ///
        /// Lazy instanciation of type ///
        /// ////////////////////////// ///


        /// Defers the instation of
        /// a template
        template < template<typename ...> typename func_t,
                 typename ... args_t >
        struct lazy_t_
        {
            using type =
                func_t<args_t...>;
        };


        /// t_ shortcut for defer_t_
        template < template<typename ...> typename func_t,
                 typename ... args_t >
        using lazy_t =
            t_<t_<lazy_t_<func_t, args_t...>>>;


        /// /////////////////// ///
        /// Has Type Definition ///
        /// /////////////////// ///


        /// Determines if a
        /// type_t has the
        /// 'type' member
        template < typename ,
                 typename = void >
        struct has_type_t_:
                std::false_type
        {
        };


        /// Specialisation for
        /// has_type_ if type_t
        /// has 'type' member
        template<typename type_t>
        struct has_type_t_ < type_t,
                void_t<typename type_t::type> > :
                std::true_type
        {
        };


        /// Evaluates the result
        /// of t_<has_type_<type_t>>
        template<typename type_t>
        using has_type_t =
            lazy_t<has_type_t_, type_t>;


        /// ///////////// ///
        /// Meta function ///
        /// ///////////// ///


        /// Access to return_ member
        /// of type_t
        template < typename type_r,
                 typename ... args_t >
        using return_ =
            typename type_r::
            template return_<args_t...>;


        /// Shortcut for return_
        template < typename type_r,
                 typename ... args_t >
        using r_ =
            return_<type_r, args_t...>;


        /// Transforms func_t into
        /// a meta function
        template <template<typename...> typename func_t>
        struct as_r_
        {
            template<typename ... args_t>
            using return_ =
                t_<lazy_t_<func_t, args_t...>>;
        };


        /// r_ shortcut for
        /// as_r_<type_t>, args_t...
        template < template<typename ...> typename type_t,
                 typename ... args_t >
        using as_r =
            r_<as_r_<type_t>, args_t...>;


        /// A meta function that
        /// returns the composition
        /// of other several meta
        /// functions funcs_t
        template<typename ... funcs_t>
        struct compose_r_;


        /// Specialisation for
        /// compose that takes
        /// a single meta function
        template<typename func_t>
        struct compose_r_<func_t>
        {
            template<typename ... args_t>
            using return_ =
                r_<func_t, args_t...>;
        };


        /// Specialisation for
        /// compose that take
        /// more one meta functions
        template < typename func_t,
                 typename ... funcs_t >
        struct compose_r_<func_t, funcs_t...>
        {
            template<typename ... args_t>
            using return_ =
                r_ < func_t,
                r_ < compose_r_<funcs_t...>,
                args_t... > >;
        };


        /// Evaluates the result of
        /// private_::compose<funcs_t...>
        template<typename ... funcs_t>
        using compose_r =
            compose_r_<funcs_t...>;


        /// Determines if a
        /// type has a return_
        /// member
        template < typename,
                 typename = void >
        struct has_return_t_
        {
            using type =
                std::false_type;
        };


        /// Specialisation for
        /// has_return_ if
        /// type_t has return_
        template <typename type_t>
        struct has_return_t_ < type_t,
                void_t < typename
                type_t::template return_<> > >
        {
            using type =
                std::true_type;
        };


        /// Evaluates the result
        /// of t_<has_return_<type_t>>
        template<typename type_t>
        using has_return_t =
            lazy_t<has_return_t_, type_t>;


        /// Determines if type_t
        /// is a meta function
        /// or not.
        template<typename type_t>
        using is_meta_function_t =
            has_return_t<type_t>;


        /// Meta function that
        /// binds the front_args_t...
        /// at the beginning of
        /// the parameters of the
        /// meta function func_t
        template < typename func_t,
                 typename... front_args_t >
        struct bind_front_r_
        {
            template<typename ... args_t>
            using return_ =
                r_ < func_t,
                front_args_t...,
                args_t... >;
        };


        /// Metafunction that
        /// binds the back_args_t...
        /// at the ending of
        /// the parameters of the
        /// meta function func_t
        template < typename func_t,
                 typename ... back_args_t >
        struct bind_back_r_
        {
            template<typename ... args_t>
            using return_ =
                r_ < func_t,
                args_t...,
                back_args_t... >;
        };


        /// Meta function that
        /// expands the list
        /// into func_t meta
        /// function parameters packs
        template < typename func_t,
                 typename list_t >
        struct expand_t_;


        /// Specialisation for
        /// expand that unpacks
        /// list_t into args_t...
        template < typename func_t,
                 template<typename ...> typename list_t,
                 typename ... args_t >
        struct expand_t_ < func_t,
                list_t <args_t... >>
        {
            using type =
                r_<func_t, args_t...>;
        };


        /// Evaluates the result of
        /// t_<private_::expand<func_t, list_t>>
        template < typename func_t,
                 typename list_t >
        using expand_t =
            lazy_t <expand_t_, func_t, list_t>;


        /// ///////////////////////// ///
        /// Wrapper for literal types ///
        /// ///////////////////////// ///


        /// Shortcut for
        /// std::integral_constant
        template < typename literal_t,
                 literal_t _l >
        using igral_t_ =
            std::integral_constant<literal_t, _l>;


        /// t_ shortcut for igral_t_
        template < typename literal_t,
                 literal_t _l >
        using igral_t =
            t_<igral_t_<literal_t, _l>>;


        /// Wrapper for bool
        template<bool _b>
        using bool_t_ =
            igral_t_<bool, _b>;


        /// t_ shortcut
        /// for bool_t_
        template<bool _b>
        using bool_t =
            t_<bool_t_<_b>>;


        /// Wrapper for short
        template<short _s>
        using short_t_ =
            igral_t_<short, _s>;


        /// t_ shortcut
        /// for short_t_
        template<short _s>
        using short_t =
            t_<short_t_<_s>>;


        /// Wrapper for unsigned short
        template<unsigned short _us>
        using ushort_t_ =
            igral_t_<unsigned short, _us>;


        /// t_ shortcut
        /// for ushort_t_
        template<unsigned short _us>
        using ushort_t =
            t_<ushort_t_<_us>>;


        /// Wrapper for char
        template<char _c>
        using char_t_ =
            igral_t_<char, _c>;


        /// t_ shortcut
        /// for char_t_
        template<char _c>
        using char_t =
            t_<char_t_<_c>>;


        /// Wrapper for int
        template<int _i>
        using int_t_ =
            igral_t_<int, _i>;


        /// t_ shortcut
        /// for int_t_
        template<int _i>
        using int_t =
            t_<int_t_<_i>>;


        /// Wrapper for long
        template<long _l>
        using long_t_ =
            igral_t_<long, _l>;


        /// t_ shortcut
        /// for long_t_
        template<long _l>
        using long_t =
            t_<long_t_<_l>>;


        /// Wrapper for long long
        template<long long _ll>
        using longlong_t_ =
            igral_t_<long long, _ll>;


        /// t_ shortcut
        /// for longlong_t_
        template<long long _ll>
        using longlong_t =
            t_<longlong_t_<_ll>>;


        /// Wrapper for unsigned
        template<unsigned _u>
        using unsigned_t_ =
            igral_t_<unsigned, _u>;


        /// t_ shortcut
        /// for unsigned_t_
        template<unsigned _u>
        using unsigned_t =
            t_<unsigned_t_<_u>>;


        /// Wrapper for unsigned long
        template<unsigned long _ul>
        using unsignedl_t_ =
            igral_t_<unsigned long, _ul>;


        /// t_ shortcut
        /// for unsignedl_t_
        template<unsigned long _ul>
        using unsignedl_t =
            t_<unsignedl_t_<_ul>>;


        /// Wrapper for unsigned long long
        template<unsigned long long _ull>
        using unsignedll_t_ =
            igral_t_<unsigned long long, _ull>;


        /// t_ shortcut
        /// for unsignedll_t_
        template<unsigned long long _ull>
        using unsignedll_t =
            t_<unsignedll_t_<_ull>>;


        /// Wrapper for size_t
        template<std::size_t _s>
        using size_t_ =
            igral_t_<std::size_t, _s>;


        /// /////////////////////// ///
        /// Logical wrapper feature ///
        /// /////////////////////// ///


        /// Wrapper for equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using equal_to_t_ =
            bool_t_ < v_<type_t>
            == v_<other_t >>;


        /// t_ shortcut for equal_to_t_
        template < typename type_t,
                 typename other_t >
        using equal_to_t =
            lazy_t<equal_to_t_, type_t, other_t>;


        /// Wrapper for not equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using not_equal_to_t_ =
            bool_t_ < v_<type_t>
            != v_<other_t >>;


        /// t_ shortcut for not_equal_to_t_
        template < typename type_t,
                 typename other_t >
        using not_equal_to_t =
            lazy_t<not_equal_to_t_, type_t, other_t>;


        /// Wrapper for greater
        /// operator
        template < typename type_t,
                 typename other_t >
        using greater_t_ =
            bool_t_ < (v_<type_t>
                       > v_<other_t>) >;


        /// t_ shortcut for greater_t_
        template < typename type_t,
                 typename other_t >
        using greater_t =
            lazy_t<greater_t_, type_t, other_t>;


        /// Wrapper for less
        /// operator
        template < typename type_t,
                 typename other_t >
        using less_t_ =
            bool_t_ < (v_<type_t>
                       < v_<other_t>) >;


        /// t_ shortcut for less_t_
        template < typename type_t,
                 typename other_t >
        using less_t =
            lazy_t<less_t_, type_t, other_t>;


        /// Wrapper for greater equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using greater_equal_t_ =
            bool_t_ < (v_<type_t>
                       >= v_<other_t>) >;


        /// t_ shortcut for greater_equal_t_
        template < typename type_t,
                 typename other_t >
        using greater_equal_t =
            lazy_t<greater_equal_t_, type_t, other_t>;


        /// Wrapper for less equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using less_equal_t_ =
            bool_t_ < (v_<type_t>
                       <= v_<other_t>) >;


        /// t_ shortcut for less_equal_t_
        template < typename type_t,
                 typename other_t >
        using less_equal_t =
            lazy_t<less_equal_t_, type_t, other_t>;


        /// Wrapper for bit and
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_and_t_ =
            bool_t_ < v_<type_t>
            & v_<other_t >>;


        /// t_ shortcut for bit_and_t_
        template < typename type_t,
                 typename other_t >
        using bit_and_t =
            lazy_t<bit_and_t_, type_t, other_t>;


        /// Wrapper for bit or
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_or_t_ =
            bool_t_ < v_<type_t>
            | v_<other_t >>;


        /// t_ shortcut for bit_or_t_
        template < typename type_t,
                 typename other_t >
        using bit_or_t =
            lazy_t<bit_or_t_, type_t, other_t>;


        /// Wrapper for bit xor
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_xor_t_ =
            bool_t_ < v_<type_t>
            ^ v_<other_t >>;


        /// t_ shortcut for bit_xor_t_
        template < typename type_t,
                 typename other_t >
        using bit_xor_t =
            lazy_t<bit_xor_t_, type_t, other_t>;


        /// Wrapper for bit not
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_not_t_ =
            bool_t_ < ~v_<type_t >>;


        /// t_ shortcut for bit_not_t_
        template < typename type_t,
                 typename other_t >
        using bit_not_t =
            lazy_t<bit_not_t_, type_t, other_t>;


        /// Returns std::true_type
        /// if all bools_t are true
        template <typename... bools_t>
        struct and_t_;


        /// Specialisation for
        /// _and_ that returns
        /// std::true_type for
        /// default case.
        template <>
        struct and_t_<> :
                std::true_type
        {
        };


        template < typename test_t,
                 typename ... other_t >
        struct and_t_<test_t, other_t...> :
                bool_t_<v_<test_t> and v_<t_<and_t_<other_t...>>>>
        {
        };


        /// Evaluates the result
        /// of t_<_and_<bools_t...>>
        template<typename ... bools_t>
        using and_t =
            lazy_t<and_t_, bools_t...>;


        /// Returns std::true_type
        /// if one or more bools_t
        /// is true
        template <typename... bools_t>
        struct or_t_;


        /// Specialisation for
        /// _or_ that returns
        /// std::false_type
        /// for default case
        template <>
        struct or_t_<> :
                std::false_type
        {
        };


        /// Specialisation for
        /// _and_ that returns
        /// std::false_type if
        /// all of bools_t is
        /// false
        template < typename bool_t,
                 typename... bools_t >
        struct or_t_<bool_t, bools_t...> :
                bool_t_<v_<bool_t> or v_<t_<or_t_<bools_t...>>>>

        {
        };


        /// Evaluates the result
        /// of t_<_or_<bools_t...>>
        template<typename ... bools_t>
        using or_t =
            lazy_t<or_t_, bools_t...>;


        /// Negates the bool_t
        template<typename bool_t>
        using not_t_ =
            bool_t_ < !v_<bool_t >>;


        /// t_ shortcut for not_t_
        template<typename bool_t>
        using not_t =
            lazy_t<not_t_, bool_t>;


        /// /////////// ///
        /// Range logic ///
        /// /////////// ///


        /// Returns true_type
        /// if current_t is
        /// between begin_t
        /// and end_t
        template < typename begin_t,
                 typename end_t,
                 typename current_t >
        using in_range_t =
            and_t < greater_equal_t<current_t, begin_t>,
            less_equal_t<current_t, end_t >>;


        /// Returns true_type
        /// if current_t is
        /// between begin_t
        /// and end_t
        template < typename begin_t,
                 typename end_t,
                 typename current_t >
        using out_range_t =
            not_t < in_range_t < begin_t,
            end_t, current_t >>;


        /// ////////////////////////////// ///
        /// Wrapper for constness keywords ///
        /// ////////////////////////////// ///


        /// Wrapper for sizeof
        template<typename type_t>
        using sizeof_t_ =
            size_t_<sizeof(type_t)>;


        /// t_ shortcut for sizeof_t_
        template<typename type_t>
        using sizeof_t =
            lazy_t<sizeof_t_, type_t>;


        /// Wrapper for sizeof...
        template<typename ... types_t>
        using sizeof_pack_t_ =
            size_t_<sizeof...(types_t)>;


        /// t_ shortcut for sizeof_pack_t_
        template<typename ... types_t>
        using sizeof_pack_t =
            lazy_t<sizeof_pack_t_, types_t...>;


        /// Wrapper for alignof
        template<typename type_t>
        using alignof_t_ =
            size_t_<alignof(type_t)>;


        /// t_ shortcut for alignof_t_
        template<typename type_t>
        using alignof_t =
            lazy_t<alignof_t_, type_t>;


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
        using inc_t_ =
            igral_t_ <
            decltype(v_<type_t> + 1),
            v_<type_t> + 1 >;


        /// t_ shortcut for inc_t_
        template<typename type_t>
        using inc_t =
            lazy_t<inc_t_, type_t>;


        /// Wrapper for decrementing
        template<typename type_t>
        using dec_t_ =
            igral_t_ <
            decltype(v_<type_t> - 1),
            v_<type_t> - 1 >;


        /// t_ shortcut for dec_t_
        template<typename type_t>
        using dec_t =
            lazy_t<dec_t_, type_t>;


        /// Wrapper for additing
        template < typename type_t,
                 typename other_t >
        using plus_t_ =
            igral_t_ <
            decltype(v_<type_t> + v_<other_t>),
            v_<type_t> + v_<other_t >>;


        /// t_ shortcut for plus_t_
        template < typename type_t,
                 typename other_t >
        using plus_t =
            lazy_t<plus_t_, type_t, other_t>;


        /// Wrapper for substracting
        template < typename type_t,
                 typename other_t >
        using minus_t_ =
            igral_t_ <
            decltype(v_<type_t> - v_<other_t>),
            v_<type_t> - v_<other_t >>;


        /// t_ shortcut for minus_t_
        template < typename type_t,
                 typename other_t >
        using minus_t =
            lazy_t<minus_t_, type_t, other_t>;


        /// Wrapper for multiplying
        template < typename type_t,
                 typename other_t >
        using multiplies_t_ =
            igral_t_ <
            decltype(v_<type_t> * v_<other_t>),
            v_<type_t> * v_<other_t >>;


        /// t_ shortcut for multiplies_t_
        template < typename type_t,
                 typename other_t >
        using multiplies_t =
            lazy_t<multiplies_t_, type_t, other_t>;


        /// Wrapper for dividing
        template < typename type_t,
                 typename other_t >
        using divides_t_ =
            igral_t_ <
            decltype(v_<type_t> / v_<other_t>),
            v_<type_t> / v_<other_t >>;


        /// t_ shortcut for divides_t_
        template < typename type_t,
                 typename other_t >
        using divides_t =
            lazy_t<divides_t_, type_t, other_t>;


        /// Wrapper for negating
        template <typename type_t>
        using negate_t_ =
            igral_t_ <
            decltype(-v_<type_t>),
            -v_<type_t >>;


        /// t_ shortcut for negate_t_
        template<typename type_t>
        using negate_t =
            lazy_t<negate_t_, type_t>;


        /// Wrapper for moduling
        template < typename type_t,
                 typename other_t >
        using modulus_t_ =
            igral_t_ <
            decltype(v_<type_t> % v_<other_t>),
            v_<type_t> % v_<other_t >>;


        /// t_ shortcut for modulus_t_
        template < typename type_t,
                 typename other_t >
        using modulus_t =
            lazy_t<modulus_t_, type_t, other_t>;


        /// ////////////// ///
        /// Type selection ///
        /// ////////////// ///


        /// Type selector
        template<typename ...>
        struct if_t_;


        /// Type selector
        /// specialisation that
        /// returns void
        /// if_t is true
        template<typename if_t>
        struct if_t_<if_t> :
                std::enable_if<v_<if_t>>
        {
        };


        /// Type selector
        /// specialisation that
        /// returns then_t
        /// if_t is true
        template < typename if_t,
                 typename then_t >
        struct if_t_<if_t, then_t>:
                std::enable_if<v_<if_t>, then_t>
        {
        };


        /// Type selector
        /// specialisation that
        /// returns then_t
        /// if_t is true
        /// else else_t
        template < typename if_t,
                 typename then_t,
                 typename else_t >
        struct if_t_<if_t, then_t, else_t>:
                std::conditional<v_<if_t>, then_t, else_t>
        {
        };


        /// Evaluates the result
        /// of t_<_if_<args_t...>>
        template<typename ... args_t>
        using if_t =
            lazy_t<if_t_, args_t...>;


        /// Evaluates the result
        /// of if_<bool_<_b>, args_t... >
        template < bool _b,
                 typename... args_t >
        using if_c =
            if_t<bool_t_<_b>, args_t...>;


        /// Evaluates the result
        /// of if_<if_t, then_t, else_t>
        template < typename test_t,
                 typename then_t,
                 typename else_t >
        using select_t =
            if_t<test_t, then_t, else_t> ;


        /// Evaluates the result
        /// of if_c<_b, then_t, else_t>
        template < bool _b,
                 typename then_t,
                 typename else_t >
        using select_c =
            if_c<_b, then_t, else_t> ;

    }
}

#endif
