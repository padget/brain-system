#ifndef __BRAIN_META_ALGORITHM_HPP__
# define __BRAIN_META_ALGORITHM_HPP__

#include "function.hpp"
#include "select.hpp"
#include "math.hpp"
#include "list.hpp"

namespace brain
{
    namespace meta
    {
        /// Incremente res_t
        /// if ref_t is same
        /// as type_t
        template < typename res_t ,
                 typename type_t,
                 typename ref_t >
        using inc_if_t =
            if_t < std::is_same<ref_t, type_t>,
            inc_t<res_t>, res_t >;


        /// Count the number
        /// of occurences of
        /// ref_t into list_t
        template < typename list_t,
                 typename ref_t >
        using count_t =
            accumulate_t < list_t,
            unsigned_t<0>,
            bind_back_r_<as_r_<inc_if_t>, ref_t >>;


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
            using type =
                at_t <
                unsigned_t<0>,
                concat_t < if_t
                < r_ < predicate_t,
                types_t > ,
                list<types_t>, list< >> ... >>;

            static_assert(!v_<std::is_same<nil, type>>,
                          "the type is equals to nil !! ");
        };


        /// t_ shortcut for
        /// find_one_if_t_
        template < typename list_t,
                 typename predicate_t >
        using find_one_if_t =
            lazy_t<find_one_if_t_, list_t, predicate_t>;


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
            lazy_t<replace_t_, list_t, old_t, new_t>;

    }
}

#endif
