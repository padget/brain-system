#ifndef __BRAIN_META_SEQUENCE_MAP_HPP__
# define __BRAIN_META_SEQUENCE_MAP_HPP__

namespace meta
{
    /// Defines a pair
    /// of key-value
    /// pattern
    template < typename key_t,
             typename value_t >
    struct pair:
            list<key_t, value_t>
    {
        /// Key of the pair
        using key =
            key_t;


        /// Value of the pair
        using value =
            value_t;
    };


    /// Accessor to
    /// key member
    template<typename pair_t>
    using key_ =
        typename pair_t::key;


    /// Accessor to
    /// value member
    template<typename pair_t>
    using value_ =
        typename pair_t::value;


    /// Defines a map
    /// as a list of
    /// pair
    template <typename ... pairs_t>
    struct map:
            list<pairs_t...>
    {
    };


    /// Returns true_ if
    /// key_t is already
    /// present in map_t
    template < typename map_t,
             typename key_t >
    using defined_ =
        meta::equal_to_ <
        meta::seq::count_if_ < map_t,
        meta::lambda < lazy::is_same_ <
        lazy::front_<lazy::item_<___>>,
        key_t >>> , meta::unsigned_<1> >;


    template < typename map_t,
             typename key_t >
    using value_of_ =
        meta::back_ <
        meta::item_ <
        meta::seq::find_if_ <
        map_t,
        meta::lambda <
        lazy::is_same_ <
        lazy::front_<lazy::item_<_0_>>,
        key_t >>> >>;


    namespace impl
    {
        template < typename examined_t,
                 typename pred_r,
                 typename cases_t >
        struct switch_;


        template < typename examined_t,
                 typename pred_r,
                 typename ... states_t,
                 typename ... funcs_r >
        struct switch_ <
                examined_t,
                pred_r,
                map<pair<states_t, funcs_r>... >>
        {
            using type =
                meta::return_ <
                value_of_ <
                map<pair<states_t, funcs_r>...>,
                meta::return_<pred_r, examined_t >> ,
                examined_t > ;
        };
    }


    template < typename examined_t,
             typename pred_r,
             typename ... cases_t >
    using switch_ =
        meta::type_<impl::switch_<examined_t, pred_r, map<cases_t...>>>;



    namespace lazy
    {
        /// Lazy signature
        /// of key_
        template<typename pair_t>
        struct key_ :
                meta::function_<meta::key_, pair_t> {};


        /// Lazy signature
        /// of key_
        template<typename pair_t>
        struct value_ :
                meta::function_<meta::value_, pair_t> {};


        /// Lazy signature
        /// of key_
        template < typename map_t,
                 typename key_t >
        struct defined_ :
                meta::function_<meta::defined_, map_t, key_t> {};


        /// Lazy signature
        /// of value_of_
        template < typename map_t,
                 typename key_t >
        struct value_of_ :
                meta::function_<meta::value_of_, map_t, key_t> {};
    }
}

#endif
