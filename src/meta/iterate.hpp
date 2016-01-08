#ifndef __BRAIN_META_ITERATE_HPP__
# define  __BRAIN_META_ITERATE_HPP__

#include "list.hpp"

namespace brain
{
    namespace meta
    {
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
        /// an empty list as first
        /// parameter. It returns
        /// res_t itself. So this
        /// has no effect on the
        /// result.
        template < typename res_t,
                 typename func_t >
        struct accumulate_t_<list<>, res_t, func_t>
        {
            using type =
                res_t;
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
            lazy_t < accumulate_t_ ,
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
            lazy_t<iterate_t_, list_t, func_t>;

    }
}

#endif
