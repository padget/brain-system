#ifndef __META_BRAIN_HPP
#define __META_BRAIN_HPP

#include <type_traits>
namespace brain
{
    /// Inspired by https://github.com/ericniebler/meta
    /// (author https://github.com/ericniebler)
    ///
    /// This library contains tow main principles :
    ///  - list<types_t...>
    ///  - meta function return_<>;
    ///
    /// The public metas functions (with return_)
    /// will present in ft namespace
    /// For all struct / using that returns 'type'
    /// an '_t_' will be added to end of its name.
    /// For all using that encapsulate t_<type_t>
    /// '_t' will be added to its name.
    /// Sale things for metafunction with return_
    /// by adding '_r_'(and '_r')
    namespace meta
    {

        struct nil {};


        /// //////////////////////////////////// ///
        /// Shortcut for access template members ///
        /// //////////////////////////////////// ///


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


        /// Access to value_type member
        /// of type_t
        template<typename type_t>
        using vt_ =
            decltype(v_<type_t>);


        /// Access to size member
        /// of type_t
        template<typename type_t>
        constexpr decltype(t_<type_t>::size) size_ =
            t_<type_t>::size;


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


        /// //////////////////////////// ///
        /// Type instanciation deferring ///
        /// //////////////////////////// ///


        /// Defers the instation of
        /// a template
        template < template<typename ...> typename func_t,
                 typename ... args_t >
        struct defer_t_
        {
            using type = func_t<args_t...>;
        };


        /// t_ shortcut for defer_t_
        template < template<typename ...> typename func_t,
                 typename ... args_t >
        using defer_t =
            t_<t_<defer_t_<func_t, args_t...>>>;


        /// //////////////////////// ///
        /// Meta function conversion ///
        /// //////////////////////// ///


        /// Transforms func_t into
        /// a meta function
        template <template<typename...> typename func_t>
        struct quote_r_
        {
            template<typename ... args_t>
            using return_ =
                t_<defer_t_<func_t, args_t...>>;
        };


        /// r_ shortcut for quote_r_
        template < template<typename ...> typename type_t,
                 typename ... args_t >
        using quote_r =
            r_<quote_r_<type_t>, args_t...>;


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
            defer_t<sizeof_t_, type_t>;


        /// Wrapper for sizeof...
        template<typename ... types_t>
        using sizeof_pack_t_ =
            size_t_<sizeof...(types_t)>;


        /// t_ shortcut for sizeof_pack_t_
        template<typename ... types_t>
        using sizeof_pack_t =
            defer_t<sizeof_pack_t_, types_t...>;


        /// Wrapper for alignof
        template<typename type_t>
        using alignof_t_ =
            size_t_<alignof(type_t)>;


        /// t_ shortcut for alignof_t_
        template<typename type_t>
        using alignof_t =
            defer_t<alignof_t_, type_t>;


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
            defer_t<inc_t_, type_t>;


        /// Wrapper for decrementing
        template<typename type_t>
        using dec_t_ =
            igral_t_ <
            decltype(v_<type_t> - 1),
            v_<type_t> - 1 >;


        /// t_ shortcut for dec_t_
        template<typename type_t>
        using dec_t =
            defer_t<dec_t_, type_t>;


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
            defer_t<plus_t_, type_t, other_t>;


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
            defer_t<minus_t_, type_t, other_t>;


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
            defer_t<multiplies_t_, type_t, other_t>;


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
            defer_t<divides_t_, type_t, other_t>;


        /// Wrapper for negating
        template <typename type_t>
        using negate_t_ =
            igral_t_ <
            decltype(-v_<type_t>),
            -v_<type_t >>;


        /// t_ shortcut for negate_t_
        template<typename type_t>
        using negate_t =
            defer_t<negate_t_, type_t>;


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
            defer_t<modulus_t_, type_t, other_t>;

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
            defer_t<equal_to_t_, type_t, other_t>;


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
            defer_t<not_equal_to_t_, type_t, other_t>;


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
            defer_t<greater_t_, type_t, other_t>;


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
            defer_t<less_t_, type_t, other_t>;


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
            defer_t<greater_equal_t_, type_t, other_t>;


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
            defer_t<less_equal_t_, type_t, other_t>;


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
            defer_t<bit_and_t_, type_t, other_t>;


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
            defer_t<bit_or_t_, type_t, other_t>;


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
            defer_t<bit_xor_t_, type_t, other_t>;


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
            defer_t<bit_not_t_, type_t, other_t>;


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
            defer_t<if_t_, args_t...>;


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


        /// Specialisation for
        /// and_ that returns
        /// std::false_type if
        /// one of bools_t is
        /// false
        template < typename bool_t,
                 typename... bools_t >
        struct and_t_<bool_t, bools_t...>:
                if_c < !v_<bool_t>, std::false_type, and_t_<bools_t... >>
        {
        };


        /// Evaluates the result
        /// of t_<_and_<bools_t...>>
        template<typename ... bools_t>
        using and_t =
            defer_t<and_t_, bools_t...>;


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
                if_c < v_<bool_t>,
                std::true_type,
                or_t_<bools_t... >>
        {
        };


        /// Evaluates the result
        /// of t_<_or_<bools_t...>>
        template<typename ... bools_t>
        using or_t =
            defer_t<or_t_, bools_t...>;


        /// Negates the bool_t
        template<typename bool_t>
        using not_t_ =
            bool_t_ < !v_<bool_t >>;


        /// t_ shortcut for not_t_
        template<typename bool_t>
        using not_t =
            defer_t<not_t_, bool_t>;


        /// //////////////////////////////////////// ///
        /// Wrapper for parameters pack manipulation ///
        /// //////////////////////////////////////// ///

        /// Wrapper for a
        /// parameters pack.
        template<typename ... types_t>
        struct list
        {
            using type = list;
            static constexpr auto size =
                v_<sizeof_pack_t_<types_t...>>;
        };


        /// Returns an empty
        /// list. Its a convenient
        /// shortcut for many
        /// list algorithm
        struct empty_list_t_
        {
            using type = list<>;
        };


        /// t_ shortcut for
        /// empty_list_t_
        using empty_list_t =
            t_<empty_list_t_>;


        /// Returns bool_<true>
        /// if list_t is empty_
        template<typename list_t>
        using empty_t_ =
            bool_t_<size_<list_t>>;


        /// t_ shortcut for empty_
        template<typename list_t>
        using empty_t =
            defer_t<empty_t_, list_t>;


        /// Returns the type
        /// at the target_t
        /// position if current_t
        /// and target_t represents
        /// the same position in
        /// pack list_t
        template < typename target_t,
                 typename current_t,
                 typename list_t >
        struct at_t_;


        /// Specialisation for
        /// at_t that takes an
        /// empty list and returns
        /// nil type
        template < typename target_t,
                 typename current_t >
        struct at_t_<target_t, current_t, list<>>
        {
            using type = nil;
        };


        /// Specialisation for
        /// at_t_ that distings
        /// the first type_t off
        /// the others types_t
        /// from the list.
        template < typename target_t,
                 typename current_t,
                 typename type_t,
                 typename ... types_t >
        struct at_t_ < target_t,
                current_t,
                list<type_t, types_t... >>
        {
            using type =
                if_t <
                equal_to_t<target_t, current_t>,
                type_t,
                t_<at_t_<target_t, inc_t<current_t>, list<types_t...>> >>;

        };


        /// t_ shortcut for at_t_
        template < typename target_t,
                 typename list_t >
        using at_t =
            defer_t<at_t_, target_t, unsigned_t<0>, list_t>;



        /// Shortcut for at_t that
        /// takes directly an unsigned
        template < unsigned _target,
                 typename list_t >
        using at_c =
            at_t<unsigned_t<_target>, list_t>;


        /// Returns first type
        /// of list_t
        template<typename list_t>
        struct front_t_;


        /// Specialisation of
        /// front_ that identifies
        /// the head_t of list_t
        template < typename head_t,
                 typename ... types_t >
        struct front_t_<list<head_t, types_t...>>
        {
            using type = head_t;
        };


        /// Evaluates t_<front_<list_t>>
        template<typename list_t>
        using front_t =
            defer_t<front_t_, list_t>;


        /// Private private_ementation
        /// of back_ template
        template<typename ... types_t>
        struct back_t_;


        /// Private private_ementation
        /// of back_
        template<typename type_t>
        struct back_t_<type_t>
        {
            using type = type_t;
        };


        /// Private private_ementation
        /// of back_ template
        template < typename type_t,
                 typename ... types_t >
        struct back_t_<type_t, types_t...>
        {
            using type = t_<back_t_<types_t...>>;
        };


        /// private_ementation for
        /// back_ in case of list
        template<typename ... types_t>
        struct back_t_<list<types_t...>>
        {
            using type = t_<back_t_<types_t...>>;
        };


        /// Evaluates the result of
        /// t_<private_::back_<list_t>>
        template<typename list_t>
        using back_t =
            defer_t<back_t_, list_t>;


        /// Push a type_t at
        /// back of list_t
        template < typename type_t,
                 typename list_t >
        struct push_back_t_ ;


        /// Specialisation for
        /// push_back_ to expand
        /// types_t pack parameters
        template < typename type_t,
                 typename ... types_t >
        struct push_back_t_<type_t, list<types_t...>>
        {
            using type = list<types_t..., type_t>;
        };


        /// Evaluates the result
        /// of t_<push_back_<type_t, list_t>>
        template < typename type_t,
                 typename list_t >
        using push_back_t =
            defer_t<push_back_t_, type_t, list_t>;


        /// Pushs a type_t at
        /// front_ of list_t
        template < typename type_t,
                 typename list_t >
        struct push_front_t_;


        /// Specialisation for
        /// push_front_ to expand
        /// types_t pack parameters
        template < typename type_t,
                 typename ... types_t >
        struct push_front_t_<type_t, list<types_t...>>
        {
            using type = list<type_t, types_t...>;
        };


        /// Evaluates the result
        /// of t_<push_front_<type_t, list_t>>
        template < typename type_t,
                 typename list_t >
        using push_front_t =
            defer_t<push_front_t_, type_t, list_t>;


        /// Removes the first
        /// type of list_t
        template<typename list_t>
        struct pop_front_t_;


        /// Specialisation for
        /// pop_front_ that identifies
        /// and removes the first
        /// type
        template < typename first_t,
                 typename ... types_t >
        struct pop_front_t_<list<first_t, types_t...>>
        {
            using type = list<types_t...>;
        };


        /// Evaluates the result
        /// of t_<pop_front_<list_t>>
        template<typename list_t>
        using pop_front_t =
            defer_t<pop_front_t_, list_t>;


        /// Concatenates all lists_t
        /// into a single list
        template <typename... lists_t>
        struct concat_t_;


        /// Specialisation for
        /// concat_ that takes no
        /// list and return an
        /// empty_ list.
        template <>
        struct concat_t_<>
        {
            using type = list<>;
        };


        /// Specialisation for
        /// concat_ that takes
        /// only one list and
        /// returns the same list
        template <typename... types_t>
        struct concat_t_<list<types_t...>>
        {
            using type = list<types_t...>;
        };


        /// Specialisation for
        /// concat_ that takes
        /// two lists and returns
        /// the concatenated list
        template < typename... types1_t,
                 typename... types2_t >
        struct concat_t_ <
                list<types1_t...>,
                list<types2_t...> >
        {
            using type =
                list<types1_t..., types2_t...>;
        };


        /// Specialisation for
        /// concat_ that represents
        /// the general case.
        template < typename... types1_t,
                 typename... types2_t,
                 typename... others_t >
        struct concat_t_ <
                list<types1_t...>,
                list<types2_t...>,
                others_t... >

        {
            using type = t_<concat_t_<list<types1_t..., types2_t...>, others_t...>>;
        };


        /// Evaluates the result
        /// of t_<concat_<lists_t...>>
        template <typename... lists_t>
        using concat_t =
            defer_t<concat_t_, lists_t...>;


        /// Removes the last
        /// type of list_t
        template<typename list_t>
        struct pop_back_t_;


        /// Specialisation for
        /// pop_back_t_ used
        /// for list with one
        /// element inside
        template<typename type_t>
        struct pop_back_t_<list<type_t>>
        {
            using type = list<>;
        };


        /// Specialisation for
        /// pop_back_t_ used
        /// for list with no
        /// element inside
        template < typename type_t,
                 typename ... types_t >
        struct pop_back_t_<list<type_t, types_t...>>
        {
            using type = concat_t < list<type_t>,
                  t_<pop_back_t_<list<types_t...>> >>;
        };


        /// Evaluates the result
        /// of t_<pop_back_<list_t>>
        template<typename list_t>
        using pop_back_t =
            defer_t<pop_back_t_, list_t>;


        /// Convert any pack
        /// representation into
        /// a list
        template<typename pack_t>
        struct to_list_t_;


        /// Specialisation of
        /// to_list_t_ that
        /// distings the types_t
        template < template<typename ...> typename pack_t,
                 typename ... types_t >
        struct to_list_t_<pack_t<types_t...>>
        {
            using type = list<types_t...>;
        };


        /// t_ shortcut for to_list_t_
        template<typename pack_t>
        using to_list_t =
            defer_t<to_list_t_, pack_t>;


        /// Finds the first type
        /// that respects the
        /// predicate_t. If there
        /// is no element, it
        /// won't compile.
        template < typename list_t,
                 typename predicate_t >
        struct find_one_if_t_;


        /// Specialisation for
        /// find_one_if_t_ that
        /// distings each type
        /// of list_t
        template < typename ... types_t,
                 typename predicate_t >
        struct find_one_if_t_<list<types_t...>, predicate_t>
        {
            using type = at_t <
                         unsigned_t<0>,
                         concat_t<if_t <r_<predicate_t, types_t>, list<types_t>, list<>>...>
                         >;
        };


        /// t_ shortcut for
        /// find_one_if_t_
        template < typename list_t,
                 typename predicate_t >
        using find_one_if_t =
            defer_t<find_one_if_t_, list_t, predicate_t>;


        /// //////////////////////////// ///
        /// Wrapper for map manipulation ///
        /// //////////////////////////// ///


        /// Wrapper for pair
        /// key-value
        template < typename key_t,
                 typename value_t >
        using pair =
            list<key_t, value_t>;


        /// Returns the first
        /// type of a pair
        template<typename pair_t>
        using first_t =
            at_t<unsigned_t<0>, pair_t>;


        /// Returns the second
        /// type of a pair
        template<typename pair_t>
        using second_t =
            at_t<unsigned_t<1>, pair_t>;


        /// Build a map from
        /// list of keys and
        /// list of values
        template < typename keys_t,
                 typename values_t >
        struct to_map_t_;


        /// Specialisation for
        /// to_map_t_ that distings
        /// elements of keys_t
        /// and values_t
        template < typename ... keys_t,
                 typename ... values_t >
        struct to_map_t_ <
                list<keys_t...>,
                list<values_t... >>
        {
            using type = list<pair<keys_t, values_t>...>;
        };


        /// t_ shortcut for to_map_t_
        template < typename keys_t,
                 typename values_t >
        using to_map_t =
            defer_t<to_map_t_, keys_t, values_t>;


        /// Returns the value
        /// of mapped key_t
        /// from map_t
        template < typename map_t,
                 typename key_t >
        struct value_of_t_
        {
            template<typename type_t>
            using predicate_ = std::is_same<key_t, first_t<type_t>>;

            using type =
                second_t<find_one_if_t<map_t, quote_r_<predicate_>>>;
        };


        /// t_ shortcut for value_of_t_
        template < typename map_t,
                 typename key_t >
        using value_of_t =
            defer_t<value_of_t_, map_t, key_t>;


        /// ////////////////////////// ///
        /// Meta function manipulation ///
        /// ////////////////////////// ///

        /// A meta function is
        /// a template that
        /// contains the return_
        /// member. This member
        /// is an alias type
        /// that represents the
        /// transformation that
        /// the input types
        /// delt with


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


        /// A meta function
        /// that always returns
        /// the type_t itself
        template<typename type_t>
        struct always_r_
        {
            template<typename ... args_t>
            using return_ = type_t;
        };


        /// r_ shortcut always_r_
        template < typename type_t,
                 typename ... args_t >
        using always_r =
            r_<always_r_<type_t>, args_t...>;


        /// Evaluates the args_t
        /// and returns always
        /// the type void
        template<typename ... args_t>
        using void_r =
            always_r<void, args_t...>;


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
                void_r<typename type_t::type> > :
                std::true_type
        {
        };


        /// Evaluates the result
        /// of t_<has_type_<type_t>>
        template<typename type_t>
        using has_type_t =
            defer_t<has_type_t_, type_t>;


        /// Determines if a
        /// type has a return_
        /// member
        template < typename,
                 typename = void >
        struct has_return_t_
        {
            using type = std::false_type;
        };


        /// Specialisation for
        /// has_return_ if
        /// type_t has return_
        template <typename type_t>
        struct has_return_t_ < type_t,
                void_r < typename
                type_t::template return_<> > >
        {
            using type = std::true_type;
        };


        /// Evaluates the result
        /// of t_<has_return_<type_t>>
        template<typename type_t>
        using has_return_t =
            defer_t<has_return_t_, type_t>;


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
            defer_t <expand_t_, func_t, list_t>;


        /// ////////////////// ///
        /// Iteration features ///
        /// ////////////////// ///


        /// Accumulates res_t over list_t
        /// the meta function func_t
        /// that must take two
        /// parameters res_t and
        /// current type_t of list_t
        /// and finally returns the
        /// result res_t
        template < typename list_t,
                 typename res_t,
                 typename func_t >
        struct accumulate_t_;


        /// Specialisation for
        /// accumulate that takes
        /// an empty_ list as first
        /// parameter. It returns
        /// res_t itself. So this
        /// has no effect on the
        /// result.
        template < typename res_t,
                 typename func_t >
        struct accumulate_t_<list<>, res_t, func_t>
        {
            using type = res_t;
        };


        /// Specialisation for
        /// accumulate that takes
        /// a list with one or more
        /// types and inherits from
        /// the next step of the
        /// accumulation on res_t
        template < typename type_t,
                 typename ... types_t,
                 typename res_t,
                 typename func_t >
        struct accumulate_t_ <list<type_t, types_t...>, res_t, func_t> :
                accumulate_t_ <list<types_t...>, r_<func_t, res_t, type_t>, func_t>
        {
        };


        /// Evaluates the result
        /// of t_<accumulate<list_t, res_t, func_t>>
        template < typename list_t,
                 typename res_t,
                 typename func_t >
        using accumulate_t =
            defer_t < accumulate_t_ ,
            list_t, res_t, func_t >;


        /// Iterates a meta
        /// function over each
        /// element of a list
        /// and return the new list
        template < typename list_t,
                 typename func_t >
        struct iterate_t_;


        /// Specialisation for
        /// iterate_t_ that
        /// distings elements
        /// of list_t
        template < typename ... types_t,
                 typename func_t >
        struct iterate_t_<list<types_t...>, func_t>
        {
            using type =
                list<r_<func_t, types_t>...>;
        };


        /// t_ shortcut
        /// for iterate_t_
        template < typename list_t,
                 typename func_t >
        using iterate_t =
            defer_t<iterate_t_, list_t, func_t>;


        /// ///////////////////////////////// ///
        /// Lambda with placeholding features ///
        /// ///////////////////////////////// ///


        /// Replaces types from
        /// list_t that represents
        /// a key in map_t
        template < typename list_t,
                 typename map_t >
        struct map_replace_t_;


        /// Specialisation for
        /// map_replace_t_ that
        /// distings each type
        /// of list_t
        template < typename ... types_t,
                 typename map_t >
        struct map_replace_t_<list<types_t...>, map_t>
        {
            using type =
                list<value_of_t<map_t, types_t>...>;
        };


        /// t_ shortcut for
        /// map_replace_t
        template < typename list_t,
                 typename map_t >
        using map_replace_t =
            defer_t<map_replace_t_, list_t, map_t>;


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
            using lambda_args_ = list<lambda_args_t...>;
            using func_args_ = list<func_args_t...>;

            template<typename ... args_t>
            using return_ =
                expand_t<func_t, map_replace_t<func_args_, to_map_t<lambda_args_, list<args_t...>>>>;
        };


        /// //////// ///
        /// Unsorted ///
        /// //////// ///

        /// TODO Sort + DOC all unsorted


        /// Meta function that
        /// add type_t to list_t
        /// if r_<predicate_t, type_t>
        /// returns true. Else it
        /// returns list_t itself
        template<typename predicate_t>
        struct filter_r_
        {
            template < typename list_t,
                     typename type_t >
            using return_ =
                select_t <
                r_<predicate_t, type_t>,
                push_back_t<type_t, list_t>,
                list_t >;
        };


        /// Evaluates the result
        /// of accumulate < list_t, list<>,
        /// private_::filter<predicate_t >>;
        template < typename list_t,
                 typename predicate_t >
        using filter_t =
            defer_t < accumulate_t ,  list_t, list<>,
            filter_r_<predicate_t >>;


        /// TODO Sort + Doc
        template < unsigned _nb,
                 typename type_t >
        struct repeat_t_
        {
            using type = concat_t <
                         t_ < repeat_t_ < _nb / 2, type_t >> ,
                         t_ < repeat_t_ < _nb / 2, type_t >> ,
                         t_ < repeat_t_ < _nb % 2, type_t >>>;
        };


        /// TODO Sort + Doc
        template <typename type_t>
        struct repeat_t_<0u, type_t>
        {
            using type = list<>;
        };


        /// TODO Sort + Doc
        template <typename type_t>
        struct repeat_t_<1u, type_t>
        {
            using type = list<type_t>;
        };


        /// TODO Sort + Doc
        template < typename nb_t,
                 typename type_t >
        using repeat_t =
            t_<repeat_t_<v_<nb_t>, type_t>>;


        /// TODO Sort + Doc
        template < unsigned _nb,
                 typename type_t >
        using repeat_c =
            defer_t<repeat_t, unsigned_t<_nb>, type_t>;


        /// TODO Sort + Doc
        template < typename res_t ,
                 typename type_t,
                 typename ref_t >
        using inc_if_t = if_t<std::is_same<ref_t, type_t>, inc_t<res_t>, res_t>;


        /// TODO Sort + Doc
        template < typename list_t,
                 typename ref_t >
        using count_t = accumulate_t<list_t, unsigned_t<0>, bind_back_r_<quote_r_<inc_if_t>, ref_t>>;


        /// TODO Sort + Doc
        template < typename list_t,
                 typename old_t,
                 typename new_t >
        struct replace_t_;


        /// TODO Sort + Doc
        template < typename ... types_t,
                 typename old_t,
                 typename new_t >
        struct replace_t_<list<types_t...>, old_t, new_t>
        {
            using type = /// TODO Faire du replace_if et donc transformer is_same en prédicat.
                list<if_t<std::is_same<types_t, old_t>, new_t, types_t>...>;
        };


        /// TODO Sort + Doc
        template < typename list_t,
                 typename old_t,
                 typename new_t >
        using replace_t =
            defer_t<replace_t_, list_t, old_t, new_t>;


        template<typename ... types_t>
        struct inherit:
            public types_t ...
        {};
    }
}


#endif
