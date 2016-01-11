#ifndef __BRAIN_META_FUNDAMENTAL_HPP__
# define __BRAIN_META_FUNDAMENTAL_HPP__

#include "core.hpp"


namespace brain
{
    namespace meta
    {
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


        /// Wrapper for void
        template<typename ...>
        using void_t =
            void;
    }
}

#endif
