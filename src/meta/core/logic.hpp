#ifndef __BRAIN_META_CORE_LOGIC_HPP__
# define  __BRAIN_META_CORE_LOGIC_HPP__

#include "base.hpp"
#include "math.hpp"

namespace meta
{
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
        /// Returns true_
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

        /// Specialisation for
        /// and_ that returns
        /// true_ if
        /// all of bools_t is
        /// true_
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
        /// Returns true_
        /// if one or more bools_t
        /// is true
        template <typename... bools_t>
        struct or_;


        /// Specialisation for
        /// or_ that returns
        /// false_ for default case
        template <>
        struct or_<> :
                false_
        {
        };


        /// Specialisation for
        /// or_ that returns
        /// true_ if
        /// one of bools_t is
        /// true_
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
        /// Lazy signature
        /// of equal_to_
        template < typename type_t,
                 typename other_t >
        struct equal_to_ :
                meta::function_<meta::equal_to_, type_t, other_t> {};


        /// Lazy signature
        /// of equal_to_
        template < typename type_t,
                 typename other_t >
        struct not_equal_to_ :
                meta::function_<meta::not_equal_to_, type_t, other_t> {};


        /// Lazy signature
        /// of equal_to_
        template < typename type_t,
                 typename other_t >
        struct greater_ :
                meta::function_<meta::greater_, type_t, other_t> {};


        /// Lazy signature
        /// of equal_to_
        template < typename type_t,
                 typename other_t >
        struct less_ :
                meta::function_<meta::less_, type_t, other_t> {};


        /// Lazy signature
        /// of equal_to_
        template < typename type_t,
                 typename other_t >
        struct greater_equal_:
                meta::function_<meta::greater_equal_, type_t, other_t> {};


        /// Lazy signature
        /// of equal_to_
        template < typename type_t,
                 typename other_t >
        struct less_equal_:
                meta::function_<meta::less_equal_, type_t, other_t> {};


        /// Lazy signature
        /// of equal_to_
        template < typename type_t,
                 typename other_t >
        struct bit_and_ :
                meta::function_<meta::bit_and_, type_t, other_t> {};


        /// Lazy signature
        /// of equal_to_
        template < typename type_t,
                 typename other_t >
        struct bit_or_:
                meta::function_<meta::bit_or_, type_t, other_t> {};


        /// Lazy signature
        /// of equal_to_
        template < typename type_t,
                 typename other_t >
        struct bit_xor_ :
                meta::function_<meta::bit_xor_, type_t, other_t> {};


        /// Lazy signature
        /// of equal_to_
        template < typename type_t,
                 typename other_t >
        struct bit_not_ :
                meta::function_<meta::bit_not_, type_t, other_t> {};

        /// Lazy signature
        /// of equal_to_
        template<typename ... bools_t>
        struct and_:
                meta::function_<meta::and_, bools_t...> {};


        /// Lazy signature
        /// of equal_to_
        template<typename ... bools_t>
        struct or_:
                meta::function_<meta::or_, bools_t...> {};


        /// Lazy signature
        /// of equal_to_
        template<typename bool_t>
        struct not_ :
                meta::function_<meta::not_, bool_t> {};
    }
}

#endif
