#ifndef __BRAIN_META_MATH_HPP__
# define __BRAIN_META_MATH_HPP__

#include "fundamental.hpp"

namespace brain
{
    namespace meta
    {
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
    }
}

#endif
