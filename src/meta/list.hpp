#ifndef __BRAIN_META_LIST_HPP__
# define __BRAIN_META_LIST_HPP__

#include "keywords.hpp"
#include "math.hpp"
#include "logic.hpp"
#include "select.hpp"
#include "function.hpp"

namespace brain
{
    namespace meta
    {
        /// //////////////////////////////////////// ///
        /// Wrapper for parameters pack manipulation ///
        /// //////////////////////////////////////// ///


        /// Access to size member
        /// of type_t
        template<typename type_t>
        constexpr decltype(t_<type_t>::size) size_ =
            t_<type_t>::size;


        /// Wrapper for a
        /// parameters pack.
        template<typename ... types_t>
        struct list
        {
            using type =
                list;

            static constexpr auto size =
                v_<sizeof_pack_t_<types_t...>>;
        };


        /// Returns an empty
        /// list. Its a convenient
        /// shortcut for many
        /// list algorithm
        struct empty_list_t_
        {
            using type =
                list<>;
        };


        /// t_ shortcut for
        /// empty_list_t_
        using empty_list_t =
            t_<empty_list_t_>;


        /// Returns bool_<true>
        /// if list_t is empty_
        template<typename list_t>
        using empty_t_ =
            bool_t_<size_<list_t>>;


        /// t_ shortcut for empty_
        template<typename list_t>
        using empty_t =
            lazy_t<empty_t_, list_t>;


        /// Returns the type
        /// at the target_t
        /// position if current_t
        /// and target_t represents
        /// the same position in
        /// pack list_t
        template < typename target_t,
                 typename current_t,
                 typename list_t >
        struct at_t_;


        /// Specialisation for
        /// at_t that takes an
        /// empty list and returns
        /// nil type
        template < typename target_t,
                 typename current_t >
        struct at_t_<target_t, current_t, list<>>
        {
            using type =
                nil;

            static_assert(v_<std::is_same<type, nil>>,
                          "nil detected !!!");
        };


        /// Specialisation for
        /// at_t_ that distings
        /// the first type_t off
        /// the others types_t
        /// from the list.
        template < typename target_t,
                 typename current_t,
                 typename type_t,
                 typename ... types_t >
        struct at_t_ < target_t,
                current_t,
                list<type_t, types_t... >>
        {
            using type =
                if_t <
                equal_to_t < target_t,
                current_t > ,
                type_t,
                t_ < at_t_ < target_t,
                inc_t<current_t>,
                list<types_t... >> >>;

        };


        /// t_ shortcut for at_t_
        template < typename target_t,
                 typename list_t >
        using at_t =
            lazy_t<at_t_, target_t, unsigned_t<0>, list_t>;



        /// Shortcut for at_t that
        /// takes directly an unsigned
        template < unsigned _target,
                 typename list_t >
        using at_c =
            at_t<unsigned_t<_target>, list_t>;


        /// Returns first type
        /// of list_t
        template<typename list_t>
        struct front_t_;


        /// Specialisation of
        /// front_ that identifies
        /// the head_t of list_t
        template < typename head_t,
                 typename ... types_t >
        struct front_t_<list<head_t, types_t...>>
        {
            using type =
                head_t;
        };


        /// Evaluates t_<front_<list_t>>
        template<typename list_t>
        using front_t =
            lazy_t<front_t_, list_t>;


        /// Private private_ementation
        /// of back_ template
        template<typename types_t>
        struct back_t_;


        template<typename type_t>
        struct back_t_<list<type_t>>
        {
            using type =
                type_t;
        };


        template < typename type_t,
                 typename ... types_t >
        struct back_t_<list<type_t, types_t...>>
        {
            using type =
                t_<back_t_<list<types_t...>>>;
        };


        /// Evaluates the result of
        /// t_<private_::back_<list_t>>
        template<typename list_t>
        using back_t =
            lazy_t<back_t_, list_t>;


        /// Inserts type_t at
        /// list_t[index_t]
        template < typename list_t,
                 typename index_t,
                 typename type_t >
        struct insert_at_t_;


        /// Push a type_t at
        /// back of list_t
        template < typename type_t,
                 typename list_t >
        struct push_back_t_ ;


        /// Specialisation for
        /// push_back_ to expand
        /// types_t pack parameters
        template < typename type_t,
                 typename ... types_t >
        struct push_back_t_<type_t, list<types_t...>>
        {
            using type =
                list<types_t..., type_t>;
        };


        /// Evaluates the result
        /// of t_<push_back_<type_t, list_t>>
        template < typename type_t,
                 typename list_t >
        using push_back_t =
            lazy_t<push_back_t_, type_t, list_t>;


        /// Pushs a type_t at
        /// front_ of list_t
        template < typename type_t,
                 typename list_t >
        struct push_front_t_;


        /// Specialisation for
        /// push_front_ to expand
        /// types_t pack parameters
        template < typename type_t,
                 typename ... types_t >
        struct push_front_t_<type_t, list<types_t...>>
        {
            using type = list<type_t, types_t...>;
        };


        /// Evaluates the result
        /// of t_<push_front_<type_t, list_t>>
        template < typename type_t,
                 typename list_t >
        using push_front_t =
            lazy_t<push_front_t_, type_t, list_t>;


        /// Removes the first
        /// type of list_t
        template<typename list_t>
        struct pop_front_t_;


        /// Specialisation for
        /// pop_front_ that identifies
        /// and removes the first
        /// type
        template < typename first_t,
                 typename ... types_t >
        struct pop_front_t_<list<first_t, types_t...>>
        {
            using type =
                list<types_t...>;
        };


        /// Evaluates the result
        /// of t_<pop_front_<list_t>>
        template<typename list_t>
        using pop_front_t =
            lazy_t<pop_front_t_, list_t>;


        /// Concatenates all lists_t
        /// into a single list
        template <typename... lists_t>
        struct concat_t_;


        /// Specialisation for
        /// concat_ that takes no
        /// list and return an
        /// empty_ list.
        template <>
        struct concat_t_<>
        {
            using type =
                list<>;
        };


        /// Specialisation for
        /// concat_ that takes
        /// only one list and
        /// returns the same list
        template <typename... types_t>
        struct concat_t_<list<types_t...>>
        {
            using type =
                list<types_t...>;
        };


        /// Specialisation for
        /// concat_ that takes
        /// two lists and returns
        /// the concatenated list
        template < typename... types1_t,
                 typename... types2_t >
        struct concat_t_ <
                list<types1_t...>,
                list<types2_t...> >
        {
            using type =
                list<types1_t..., types2_t...>;
        };


        /// Specialisation for
        /// concat_ that represents
        /// the general case.
        template < typename... types1_t,
                 typename... types2_t,
                 typename... others_t >
        struct concat_t_ <
                list<types1_t...>,
                list<types2_t...>,
                others_t... >
        {
            using type =
                t_ < concat_t_ < list < types1_t...,
                types2_t... > , others_t... >>;
        };


        /// Evaluates the result
        /// of t_<concat_<lists_t...>>
        template <typename... lists_t>
        using concat_t =
            lazy_t<concat_t_, lists_t...>;


        /// Removes the last
        /// type of list_t
        template<typename list_t>
        struct pop_back_t_;


        template<typename type_t>
        struct pop_back_t_<list<type_t>>
        {
            using type =
                empty_list_t;
        };


        /// Specialisation for
        /// pop_back_t_ used
        /// for list with one
        /// element inside
        template < typename type_t,
                 typename ... types_t >
        struct pop_back_t_<list<type_t, types_t...>>
        {
            using type =
                concat_t < list<type_t>,
                t_<pop_back_t_<list<types_t ...>> >>;
        };


        /// Evaluates the result
        /// of t_<pop_back_<list_t>>
        template<typename list_t>
        using pop_back_t =
            lazy_t<pop_back_t_, list_t>;


        /// Convert any pack
        /// representation into
        /// a list
        template<typename pack_t>
        struct to_list_t_;


        /// Specialisation of
        /// to_list_t_ that
        /// distings the types_t
        template < template<typename ...> typename pack_t,
                 typename ... types_t >
        struct to_list_t_<pack_t<types_t...>>
        {
            /// Deports the elements
            /// from pack_t to list
            using type =
                list<types_t...>;
        };


        /// t_ shortcut for to_list_t_
        template<typename pack_t>
        using to_list_t =
            lazy_t<to_list_t_, pack_t>;



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


        /// Meta function that
        /// add type_t to list_t
        /// if r_<predicate_t, type_t>
        /// returns true. Else it
        /// returns list_t itself
        template<typename predicate_t>
        struct filter_r_
        {
            template < typename list_t,
                     typename type_t >
            using return_ =
                select_t <
                r_<predicate_t, type_t>,
                push_back_t<type_t, list_t>,
                list_t >;
        };


        /// Evaluates the result
        /// of accumulate < list_t, list<>,
        /// private_::filter<predicate_t >>;
        template < typename list_t,
                 typename predicate_t >
        using filter_t =
            lazy_t < accumulate_t , list_t, list<>,
            filter_r_<predicate_t >>;






//        template < unsigned _nb,
//                 typename type_t >
//        struct repeat_t_
//        {
//            using type =
//                concat_t <
//                t_ < repeat_t_ < _nb / 2, type_t >> ,
//                t_ < repeat_t_ < _nb / 2, type_t >> ,
//                t_ < repeat_t_ < _nb % 2, type_t >>>;
//        };
//
//
//        /// TODO Sort + Doc
//        template <typename type_t>
//        struct repeat_t_<0u, type_t>
//        {
//            using type =
//                list<>;
//        };
//
//
//        /// TODO Sort + Doc
//        template <typename type_t>
//        struct repeat_t_<1u, type_t>
//        {
//            using type =
//                list<type_t>;
//        };
//
//
//        /// TODO Sort + Doc
//        template < typename nb_t,
//                 typename type_t >
//        using repeat_t =
//            t_<repeat_t_<v_<nb_t>, type_t>>;
//
//
//        /// TODO Sort + Doc
//        template < unsigned _nb,
//                 typename type_t >
//        using repeat_c =
//            lazy_t<repeat_t, unsigned_t<_nb>, type_t>;

    }
}


#endif