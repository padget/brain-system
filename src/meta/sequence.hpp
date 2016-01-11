#ifndef __BRAIN_META_SEQUENCE_HPP__
# define __BRAIN_META_SEQUENCE_HPP__

#include "iterator.hpp"

namespace brain
{
    namespace meta
    {
        template < template<typename...> typename iterator_t,
                 typename ... items_t >
        struct sequence
        {
            using begin =
                iterator_t<pack<items_t...>>;

            using end =
                next_<last_t<begin>>;

            using size =
                sizeof_pack_t<items_t...>;


            template<typename ... args_t>
            using iterator =
                iterator_t<args_t...>;
        };


        template<typename ... items_t>
        using vector =
            sequence<iterator, items_t...>;


        template<typename ... items_t>
        using list =
            sequence<iterator, items_t...>;


        template<typename sequence_t>
        using begin_ =
            typename sequence_t::begin;


        template<typename sequence_t>
        using end_ =
            typename sequence_t::end;


        template < typename sequence_t,
                 typename ... args_t >
        using iterator_ =
            typename sequence_t::template iterator<args_t...>;


        template<typename sequence_t>
        using empty_t =
            equal_to_t <
            size_<sequence_t>,
            unsigned_t<0> >;


        template<typename sequence_t>
        struct clear_t_;


        template < template<template<typename ...>typename, typename...> typename sequence_t,
                 template<typename...> typename iterator_t,
                 typename ... items_t >
        struct clear_t_<sequence_t<iterator_t, items_t...>>
        {
            using type =
                sequence_t<iterator_t>;
        };


        template<typename sequence_t>
        using clear_t =
            lazy_t<clear_t_, sequence_t>;


        template<typename sequence_t>
        using front_t =
            item_<begin_<sequence_t>>;


        template<typename sequence_t>
        using back_t =
            item_<prev_<end_<sequence_t>>>;


        template < typename sequence_t,
                 typename type_t >
        struct push_back_t_;


        template < template<template<typename...> typename, typename...> typename sequence_t,
                 template<typename...> typename iterator_t,
                 typename ... items_t,
                 typename type_t >
        struct push_back_t_ <
                sequence_t<iterator_t, items_t...>,
                type_t >
        {
            using type =
                sequence_t<iterator_t, items_t..., type_t>;
        };

        template < typename sequence_t,
                 typename type_t >
        using push_back_t =
            lazy_t<push_back_t_, sequence_t, type_t>;


        template < typename sequence_t,
                 typename type_t >
        struct push_front_t_;


        template < template<template<typename...> typename, typename...> typename sequence_t,
                 template<typename...> typename iterator_t,
                 typename ... items_t,
                 typename type_t >
        struct push_front_t_ <
                sequence_t<iterator_t, items_t...>,
                type_t >
        {
            using type =
                sequence_t<iterator_t, type_t, items_t...>;
        };

        template < typename sequence_t,
                 typename type_t >
        using push_front_t =
            lazy_t<push_front_t_, sequence_t, type_t>;


        template<typename sequence_t>
        struct pop_back_t_;


        template < template<template<typename...> typename, typename...> typename sequence_t,
                 template<typename...> typename iterator_t,
                 typename ... items_t >
        struct pop_back_t_<sequence_t<iterator_t, items_t...>>
        {
            template < typename current_t,
                     typename temp_sequence_t >
            struct pop_back_t_impl_
            {
                using type =
                    push_front_t<t_<pop_back_t_impl_<temp_sequence_t, next_<current_t>>>, item_<current_t>>;
            };


            template<typename tmp_sequence_t>
            struct pop_back_t_impl_ <
                    tmp_sequence_t,
                    prev_<end_<sequence_t<iterator_t, items_t...>>> >
            {
                using type =
                    tmp_sequence_t;
            };

            using type = t_<pop_back_t_impl_<begin_<sequence_t<iterator_t, items_t...>>, sequence_t<iterator_t>>>;

        };


        template < typename sequence_t>
        using pop_back_t =
            lazy_t<pop_back_t_, sequence_t>;


        template<typename sequence_t>
        struct pop_front_t_;


        template < template<template<typename...> typename, typename...> typename sequence_t,
                 template<typename...> typename iterator_t,
                 typename ... items_t,
                 typename type_t >
        struct pop_front_t_ <
                sequence_t<iterator_t,  type_t, items_t...> >
        {
            using type =
                sequence_t<iterator_t, items_t...>;
        };


        template < typename sequence_t>
        using pop_front_t =
            lazy_t<pop_front_t_, sequence_t>;




        using a_list = vector<double, int>;
        using a_second_list = pop_back_t<a_list>;
        static_assert(v_<std::is_same<back_t<a_second_list>, double>>, "");
    }
}

#endif
