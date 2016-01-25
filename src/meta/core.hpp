#ifndef __BRAIN_META_CORE_HPP__
# define __BRAIN_META_CORE_HPP__

#include <type_traits>
#include "core/base.hpp"
#include "core/math.hpp"
#include "core/logic.hpp"
#include "core/select.hpp"
#include "core/functionclass.hpp"
#include "core/pack.hpp"

namespace brain
{
    namespace meta
    {
        /// ////////// ///
        /// Base alias ///
        /// ////////// ///

        using nil =
            core::nil;

        using true_ =
            core::true_;

        using false_ =
            core::false_;

        template<typename ... types_t>
        using void_ =
            core::void_<types_t...>;

        template<typename type_t>
        using type_ =
            core::type_<type_t>;

        template<typename type_t>
        constexpr decltype(core::v_<type_t>) v_ =
            core::v_<type_t>;

        template<typename type_t>
        using idem_ =
            core::idem_<type_t>;

        template < typename type_t,
                 typename other_t >
        using is_same_ =
            core::is_same_<type_t, other_t>;

        template < template<typename ...> typename func_t,
                 typename ... args_t >
        using function_ =
            core::function_<func_t, args_t...>;

        /// ////////// ///
        /// Math alias ///
        /// ////////// ///

        template < typename literal_t,
                 literal_t _l >
        using igral_ =
            core::igral_<literal_t, _l>;

        template<bool _b>
        using bool_ =
            core::bool_<_b>;

        template<short _s>
        using short_ =
            core::short_<_s>;

        template<short _us>
        using ushort_ =
            core::ushort_<_us>;

        template<char _c>
        using char_ =
            core::char_<_c>;

        template<int _i>
        using int_ =
            core::int_<_i>;

        template<long _l>
        using long_ =
            core::long_<_l>;

        template<long long _ll>
        using longlong_ =
            core::longlong_<_ll>;

        template<unsigned _u>
        using unsigned_ =
            core::unsigned_<_u>;

        template<unsigned long _ul>
        using unsignedl_ =
            core::unsignedl_<_ul>;

        template<unsigned long long _ull>
        using unsignedll_ =
            core::unsignedll_<_ull>;

        template<std::size_t _s>
        using size_t_ =
            core::size_t_<_s>;

        template<typename type_t>
        using inc_ =
            core::inc_<type_t>;

        template<typename type_t>
        using dec_ =
            core::dec_<type_t>;

        template < typename type_t,
                 typename other_t >
        using plus_ =
            core::plus_<type_t, other_t>;

        template < typename type_t,
                 typename other_t >
        using minus_ =
            core::minus_<type_t, other_t>;

        template < typename type_t,
                 typename other_t >
        using multiplies_ =
            core::multiplies_<type_t, other_t>;

        template < typename type_t,
                 typename other_t >
        using divides_ =
            core::divides_<type_t, other_t>;

        template <typename type_t>
        using negate_ =
            core::negate_<type_t>;

        template < typename type_t,
                 typename other_t >
        using modulus_ =
            core::modulus_<type_t, other_t>;


        /// /////////// ///
        /// Logic alias ///
        /// /////////// ///

        template < typename type_t,
                 typename other_t >
        using equal_to_ =
            core::equal_to_<type_t, other_t>;

        template < typename type_t,
                 typename other_t >
        using not_equal_to_ =
            core::not_equal_to_<type_t, other_t>;

        template < typename type_t,
                 typename other_t >
        using greater_ =
            core::greater_<type_t, other_t>;

        template < typename type_t,
                 typename other_t >
        using less_ =
            core::less_<type_t, other_t>;

        template < typename type_t,
                 typename other_t >
        using greater_equal_ =
            core::greater_equal_<type_t, other_t>;

        template < typename type_t,
                 typename other_t >
        using less_equal_ =
            core::less_equal_<type_t, other_t>;

        template < typename type_t,
                 typename other_t >
        using bit_and_ =
            core::bit_and_<type_t, other_t>;

        template < typename type_t,
                 typename other_t >
        using bit_or_ =
            core::bit_or_<type_t, other_t>;

        template < typename type_t,
                 typename other_t >
        using bit_xor_ =
            core::bit_xor_<type_t, other_t>;

        template < typename type_t,
                 typename other_t >
        using bit_not_ =
            core::bit_not_<type_t, other_t>;

        template<typename ... bools_t>
        using and_ =
            core::and_<bools_t...>;

        template<typename ... bools_t>
        using or_ =
            core::or_<bools_t...>;

        template<typename bool_t>
        using not_ =
            core::not_<bool_t>;

        /// /////////////// ///
        /// Selection alias ///
        /// /////////////// ///

        template < typename test_t,
                 typename then_t,
                 typename else_t >
        using if_ =
            core::if_<test_t, then_t, else_t>;

        template < typename test_t,
                 typename lthen_t,
                 typename lelse_t >
        using eval_if_ =
            core::eval_if_<test_t, lthen_t, lelse_t>;

        /// //////////////////// ///
        /// Function class alias ///
        /// //////////////////// ///

        template<template<typename ...> typename func_t>
        using function_class_ =
            core::function_class_<func_t>;

        template<typename index_t>
        using placeholder =
            core::placeholder;

        using _0_ = core::_0_;
        using _1_ = core::_1_;
        using _2_ = core::_2_;
        using _3_ = core::_3_;
        using _4_ = core::_4_;
        using _5_ = core::_5_;
        using _6_ = core::_6_;
        using _7_ = core::_7_;
        using _8_ = core::_8_;
        using _9_ = core::_9_;
        using _10_ = core::_10_;
        using _11_ = core::_11_;
        using _12_ = core::_12_;
        using _13_ = core::_13_;
        using _14_ = core::_14_;
        using _15_ = core::_15_;

        template<typename type_t>
        using is_placeholder_expression_ =
            core::is_placeholder_expression_<type_t>;

        template < typename type_r,
                 typename ... args_t >
        using return_ =
            core::return_<type_r, args_t...>;

        template < typename func_r,
                 typename ... holders_t >
        using bind_ =
            core::bind_<func_r, holders_t...>;

        template<typename lfunc_t>
        using lambda =
            core::lambda<lfunc_t>;

        template < typename func_t,
                 typename ... funcs_t >
        using compose_ =
            core::compose_<func_t, funcs_t...>;

        template < typename func_t,
                 typename... front_args_t >
        using bind_front_ =
            core::bind_front_<func_t, front_args_t...>;

        template < typename func_t,
                 typename... back_args_t >
        using bind_back_ =
            core::bind_back_<func_t, back_args_t...>;

        /// ////////// ///
        /// Pack alias ///
        /// ////////// ///

        template<typename ... types_t>
        using pack =
            core::pack<types_t...>;

        template<typename pack_t>
        using size_ =
            core::size_<pack_t>;

        template<typename ... packs_t>
        using concat_ =
            core::concat_<packs_t...>;

        template < typename pack_t,
                 typename type_t >
        using push_back_ =
            core::push_back_<pack_t, type_t>;

        template < typename pack_t,
                 typename type_t >
        using push_front_ =
            core::push_front_<pack_t, type_t>;

        template<typename pack_t>
        using clear_ =
            core::clear_<pack_t>;
    }
}

#endif
