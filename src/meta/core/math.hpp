#ifndef __BRAIN_META_CORE_MATH_HPP__
# define  __BRAIN_META_CORE_MATH_HPP__

#include "base.hpp"

namespace meta
{

    /// ///////////////////////// ///
    /// Wrapper for literal types ///
    /// ///////////////////////// ///


    /// Shortcut for
    /// std::integral_constant
    template < typename literal_t,
             literal_t _l >
    using igral_ =
        std::integral_constant<literal_t, _l>;


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
        /// Lazy signature
        /// of inc_
        template<typename type_t>
        struct inc_:
                meta::function_<meta::inc_, type_t> {};


        /// Lazy signature
        /// of dec_
        template<typename type_t>
        struct dec_:
                meta::function_<meta::dec_, type_t> {};


        /// Lazy signature
        /// of plus_
        template < typename type_t,
                 typename other_t >
        struct plus_ :
                meta::function_<meta::plus_, type_t, other_t> {};


        /// Lazy signature
        /// of minus_
        template < typename type_t,
                 typename other_t >
        struct minus_:
                meta::function_<meta::minus_, type_t, other_t> {};


        /// Lazy signature
        /// of multiplies_
        template < typename type_t,
                 typename other_t >
        struct multiplies_:
                meta::function_<meta::multiplies_, type_t, other_t> {};


        /// Lazy signature
        /// of divides_
        template < typename type_t,
                 typename other_t >
        struct divides_:
                meta::function_<meta::divides_, type_t, other_t> {};


        /// Lazy signature
        /// of negate_
        template <typename type_t>
        struct negate_ :
                meta::function_<meta::negate_, type_t> {};


        /// Lazy signature
        /// of modulus_
        template < typename type_t,
                 typename other_t >
        struct modulus_ :
                meta::function_<meta::modulus_, type_t, other_t> {};
    }
}
#endif
