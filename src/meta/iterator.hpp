#ifndef __BRAIN_META_ITERATOR_HPP__
# define __BRAIN_META_ITERATOR_HPP__

#include "math.hpp"
#include "logic.hpp"

namespace brain
{
    namespace meta
    {
        template<typename ... items_t>
        struct pack
        {
            using size =
                sizeof_pack_t<items_t...>;
        };


        template<typename sequence_t>
        using size_ =
            typename sequence_t::size;


        template < typename type_t,
                 typename = void >
        struct has_item_t_:
                std::false_type
        {
        };


        template<typename type_t>
        struct has_item_t_<type_t, void_t<typename type_t::item>> :
                        std::true_type
        {
        };


        template<typename type_t>
        using has_item_t =
            lazy_t<has_item_t_, type_t>;


        template < typename type_t,
                 typename = void >
        struct has_next_t_:
                std::false_type
        {
        };


        template<typename type_t>
        struct has_next_t_<type_t, void_t<typename type_t::next>> :
                        std::true_type
        {
        };


        template<typename type_t>
        using has_next_t =
            lazy_t<has_next_t_, type_t>;


        template < typename type_t,
                 typename = void >
        struct has_prev_t_:
                std::false_type
        {
        };


        template<typename type_t>
        struct has_prev_t_<type_t, void_t<typename type_t::prev>> :
                        std::true_type
        {
        };


        template<typename type_t>
        using has_prev_t =
            lazy_t<has_prev_t_, type_t>;



        template < typename type_t,
                 typename = void >
        struct has_index_t_:
                std::false_type
        {
        };


        template<typename type_t>
        struct has_index_t_<type_t, void_t<typename type_t::index>> :
                        std::true_type
        {
        };


        template<typename type_t>
        using has_index_t =
            lazy_t<has_index_t_, type_t>;



        template<typename type_t>
        using is_forward_iterator_t =
            and_t <
            has_item_t<type_t>,
            has_next_t<type_t>,
            has_index_t<type_t >>;


        template<typename type_t>
        using is_bidirectional_iterator_t =
            and_t <
            is_forward_iterator_t<type_t>,
            has_prev_t<type_t >>;


        template<typename iterator_t>
        using next_ =
            typename iterator_t::next;


        template<typename iterator_t>
        using prev_ =
            typename iterator_t::prev;


        template<typename iterator_t>
        using index_ =
            typename iterator_t::index;


        template<typename iterator_t>
        using item_ =
            typename iterator_t::item;


        struct end_iterator
        {
            using index =
                long_t < -1 >;

            using item =
                nil;

            using next =
                end_iterator;

            using prev =
                end_iterator;
        };


        template < typename sequence_t,
                 typename index_t = long_t<0>,
                 typename prev_t = end_iterator,
                 typename last_index_t = size_<sequence_t >>
        struct iterator;


        template<>
        struct iterator <pack<>, long_t<0>, end_iterator, size_<pack<>>>
        {
            using index =
                long_t < -1 >;
            using item =
                nil;
            using next =
                end_iterator;
            using prev =
                end_iterator;
            using size =
                size_<pack<>>;
        };


        template < typename item_t,
                 typename ... items_t >
        struct iterator <
                pack<item_t, items_t...> ,
                long_t<0>,
                end_iterator,
                size_<pack<item_t, items_t...>> >
        {

            using size =
                size_<pack<item_t, items_t...>>;

            using index =
                long_t<0>;
            using item =
                item_t;
            using prev =
                end_iterator;
            using next =
                iterator <
                pack<items_t...>,
                if_t < equal_to_t<long_t<1>, size>, long_t < -1 > , long_t<1> > ,
                iterator >;
        };


        template < typename item_t,
                 typename ... items_t,
                 typename index_t,
                 typename prev_t,
                 typename last_index_t >
        struct iterator <
                pack<item_t, items_t...> ,
                index_t,
                prev_t,
                last_index_t >
        {
            using index =
                index_t;
            using item =
                item_t;
            using prev =
                prev_t;
            using next =
                iterator <
                pack<items_t...>,
                if_t < equal_to_t <index_t, last_index_t> , long_t < (-1) > , inc_t<index_t >> ,
                iterator ,
                last_index_t >;
            using size =
                last_index_t;
        };


        template < typename prev_t,
                 typename last_index_t >
        struct iterator < pack<>, long_t < -1 > , prev_t, last_index_t >
        {
            using index =
                long_t < -1 > ;
            using item =
                nil;
            using next =
                iterator;
            using prev =
                prev_t;
            using size =
                last_index_t;
        };


        template<typename iterator_t>
        using ended_t =
            std::is_same<nil, item_<iterator_t>>;


        template<typename iterator_t>
        struct last_t_
        {
            using type = last_t_<>
        }

                     template < template<typename ...> typename iterator_t,
                              typename ... args_t >
        struct last_t_<iterator_t<pack<>, args_t...>>
        {

        };
        /*
                template <typename begin_t>
                struct last_t_
                {
                    template < typename iterator_t,
                             typename = std::true_type >
                    struct last_t_impl_
                    {
                        using type =
                            prev_<iterator_t>;
                    };


                    template <typename iterator_t>
                    struct last_t_impl_ <
                            iterator_t,
                            std::false_type >
                    {
                        using type =
                            t_<last_t_impl_<next_<iterator_t>, ended_t<next<iterator_t>>>>;
                    };

                    using type =
                        t_<last_t_impl_<begin_t, ended_t<begin_t>>>;
                };
        */

        template<typename iterator_t>
        using last_t =
            lazy_t<last_t_, iterator_t>;


        template < typename begin_t,
                 typename end_t,
                 typename func_r,
                 typename ... args_t >
        struct from_to_t_
        {
            using begin =
                begin_t;


            using end =
                end_t;


            template < typename iterator_t,
                     typename is_end_t >
            struct from_to_t_impl_;


            template <typename iterator_t>
            struct from_to_t_impl_ <
                    iterator_t,
                    std::false_type >
            {
                using type =
            };


            template <typename iterator_t>
            struct from_to_t_impl_ <
                    iterator_t,
                    std::true_type >
            {

            };


            using type =
                from_to_t_impl_<begin_t, ended_t<begin_t>>;
        };


        template < typename begin_t,
                 typename end_t,
                 typename = is_end_t<end_t >>
        struct distance_t_;


        template < typename begin_t,
                 typename end_t >
        struct distance_t_ <
                begin_t,
                end_t,
                std::false_type >
        {
            using type =
                minus_t <
                index_<end_t>,
                index_<begin_t >>;
        };


        template < typename begin_t,
                 typename end_t >
        struct distance_t_ <
                begin_t,
                end_t,
                std::true_type >
        {
            using type =
                minus_t <
                index_<begin_t>,
                index_<prev_<end_t> >>;
        };


        template < typename begin_t,
                 typename end_t >
        using distance_t =
            lazy_t<distance_t_, begin_t, end_t>;
    }
}

#endif
