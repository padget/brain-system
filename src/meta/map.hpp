#ifndef __BRAIN_META_MAP_HPP__
# define  __BRAIN_META_MAP_HPP__

#include "list.hpp"
#include "algorithm.hpp"

namespace brain
{
    namespace meta
    {
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
            using type =
                list<pair<keys_t, values_t>...>;
        };


        /// t_ shortcut for to_map_t_
        template < typename keys_t,
                 typename values_t >
        using to_map_t =
            lazy_t<to_map_t_, keys_t, values_t>;


        /// Returns the value
        /// of mapped key_t
        /// from map_t
        template < typename map_t,
                 typename key_t >
        struct value_of_t_
        {
            template<typename type_t>
            using predicate_ =
                std::is_same<key_t, first_t<type_t>>;

            using type =
                second_t<find_one_if_t<map_t, as_r_<predicate_>>>;
        };


        /// t_ shortcut for value_of_t_
        template < typename map_t,
                 typename key_t >
        using value_of_t =
            lazy_t<value_of_t_, map_t, key_t>;


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
            lazy_t<map_replace_t_, list_t, map_t>;

    }
}

#endif
