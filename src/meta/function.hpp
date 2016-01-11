#ifndef __BRAIN_META_FUNCTION_HPP__
# define  __BRAIN_META_FUNCTION_HPP__

#include "fundamental.hpp"
#include <type_traits>

namespace brain
{
    namespace meta
    {
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
    }
}

#endif
