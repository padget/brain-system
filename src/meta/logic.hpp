#ifndef __BRAIN_META_LOGIC_HPP__
# define __BRAIN_META_LOGIC_HPP__

#include "fundamental.hpp"

namespace brain
{
    namespace meta
    {
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
    }
}

#endif
