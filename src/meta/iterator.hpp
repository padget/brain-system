#ifndef __BRAIN_META_ITERATOR_HPP__
# define __BRAIN_META_ITERATOR_HPP__

#include "core.hpp"

namespace brain
{
    namespace meta
    {
        /// Main support of the
        /// parameters pack
        template<typename ... items_t>
        struct pack
        {
            using size =
                sizeof_pack_t<items_t...>;
        };


        /// size member
        /// accessor
        template<typename sequence_t>
        using size_ =
            typename sequence_t::size;


        /// Determines if
        /// type_t has item
        /// member or not
        template < typename type_t,
                 typename = void >
        struct has_item_t_:
                std::false_type
        {
        };


        /// Specialization for
        /// has_item_t_ that
        /// returns true_type
        /// because of presence
        /// of item member
        template<typename type_t>
        struct has_item_t_<type_t, void_t<typename type_t::item>> :
                        std::true_type
        {
        };


        /// t_ shortcut for
        /// has_item_t_
        template<typename type_t>
        using has_item_t =
            lazy_t<has_item_t_, type_t>;


        /// Determines if
        /// type_t has next
        /// member or not
        template < typename type_t,
                 typename = void >
        struct has_next_t_:
                std::false_type
        {
        };


        /// Specialization for
        /// has_item_t_ that
        /// returns true_type
        /// because of presence
        /// of next member
        template<typename type_t>
        struct has_next_t_<type_t, void_t<typename type_t::next>> :
                        std::true_type
        {
        };


        /// t_ shortcut for
        /// has_next_t_
        template<typename type_t>
        using has_next_t =
            lazy_t<has_next_t_, type_t>;


        /// Determines if
        /// type_t has prev
        /// member or not
        template < typename type_t,
                 typename = void >
        struct has_prev_t_:
                std::false_type
        {
        };


        /// Specialization for
        /// has_item_t_ that
        /// returns true_type
        /// because of presence
        /// of prev member
        template<typename type_t>
        struct has_prev_t_<type_t, void_t<typename type_t::prev>> :
                        std::true_type
        {
        };


        /// t_ shortcut for
        /// has_prev_t_
        template<typename type_t>
        using has_prev_t =
            lazy_t<has_prev_t_, type_t>;


        /// Determines if
        /// type_t has index
        /// member or not
        template < typename type_t,
                 typename = void >
        struct has_index_t_:
                std::false_type
        {
        };


        /// Specialization for
        /// has_item_t_ that
        /// returns true_type
        /// because of presence
        /// of index member
        template<typename type_t>
        struct has_index_t_ <
                type_t,
                void_t<typename type_t::index> > :
                std::true_type
        {
        };


        /// t_ shortcut for
        /// has_index_t_
        template<typename type_t>
        using has_index_t =
            lazy_t<has_index_t_, type_t>;


        /// Determines if type_t
        /// is a forward iterator
        template<typename type_t>
        using is_forward_iterator_t =
            and_t <
            has_item_t<type_t>,
            has_next_t<type_t>,
            has_index_t<type_t >>;


        /// Determines if type_t
        /// is a backward iterator
        template<typename type_t>
        using is_backward_iterator_t =
            and_t <
            has_item_t<type_t>,
            has_prev_t<type_t>,
            has_index_t<type_t >>;


        /// Determines if type_t
        /// is a bidirectionnal
        /// iterator
        template<typename type_t>
        using is_bidirectional_iterator_t =
            and_t <
            is_forward_iterator_t<type_t>,
            is_backward_iterator_t<type_t >>;


        /// Accessor for
        /// next member
        template<typename iterator_t>
        using next_ =
            typename iterator_t::next;


        /// Accessor for
        /// prev member
        template<typename iterator_t>
        using prev_ =
            typename iterator_t::prev;


        /// Accessor for
        /// index member
        template<typename iterator_t>
        using index_ =
            typename iterator_t::index;


        /// Accessor for
        /// item member
        template<typename iterator_t>
        using item_ =
            typename iterator_t::item;


        /// Generic end
        /// iterator used
        /// in all meta
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


        /// Definition of
        /// bidirectionnal
        /// iterator
        template < typename sequence_t,
                 typename index_t = long_t<0>,
                 typename prev_t = end_iterator,
                 typename last_index_t = size_<sequence_t >>
        struct iterator;


        /// If the pack is
        /// empty and the
        /// index is 0, so
        /// the first iterator
        /// is also the end
        /// iterator
        template<>
        struct iterator <
                pack<>,
                long_t<0>,
                end_iterator,
                size_<pack<>> >
        {
            using size =
                size_<pack<>>;

            using index =
                long_t < -1 >;
            using item =
                nil;
            using next =
                end_iterator;
            using prev =
                end_iterator;
        };


        /// In the case of the
        /// index 0 the current
        /// is built with item_t
        /// and the next is built
        /// with items_t
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


        /// General case that
        /// build current and
        /// demande for the next
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


        /// Last case that build
        /// the end iterator with
        /// an index -1
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


        /// Determines if the
        /// iterator_t is the
        /// end iterator of its
        /// sequence
        template<typename iterator_t>
        struct ended_t_:
                std::false_type
        {
        };


        /// Specialization that
        /// returns true_type
        /// due to the empty
        /// paramater pack
        template < template<typename ...> typename iterator_t,
                 typename ... args_t >
        struct ended_t_ <
                iterator_t < pack<>,
                args_t... > > :
                std::true_type
        {
        };


        /// t_ shortcut for
        /// ended_t_
        template<typename iterator_t>
        using ended_t =
            lazy_t<ended_t_, iterator_t>;


        /// Returns the last
        /// item before the end
        /// iterator
        template<typename iterator_t>
        struct last_valid_t_
        {
            using type =
                t_<last_valid_t_<next_<iterator_t>>>;
        };


        /// Specialization for
        /// that returns the prev
        /// iterator of the end
        /// iterator
        template < template<typename ...> typename iterator_t,
                 typename ... args_t >
        struct last_valid_t_ <
                iterator_t < pack<>,
                args_t... >>
        {
            using type =
                prev_<iterator_t<pack<>, args_t...>>;
        };


        /// t_ shortcut for
        /// last_valid_t_
        template<typename iterator_t>
        using last_t =
            lazy_t<last_valid_t_, iterator_t>;


        /// Computes the
        /// distance between
        /// two iterators
        template < typename begin_t,
                 typename end_t >
        struct distance_t_
        {
            using type =
                inc_t < minus_t <
                index_<end_t>,
                index_<begin_t> >>;
        };


        /// Specialization for
        /// end iterator that
        /// returns the distance
        /// between the begin_t
        /// and prev_<end_t>
        template < typename begin_t,
                 template<typename ...> typename end_t ,
                 typename ... args_t >
        struct distance_t_<begin_t, end_t<pack<>, args_t...>>
        {
            using type =
                inc_t < minus_t <
                index_<prev_<end_t<pack<>, args_t...>>> ,
                index_<begin_t> >>;
        };


        /// t_ shortcut for
        /// distance_t_
        template < typename begin_t,
                 typename end_t >
        using distance_t =
            lazy_t<distance_t_, begin_t, end_t>;


        /// Navigates between
        /// begin_t and end_t
        /// thanks to direction_t
        /// to accumulate the
        /// results of each call
        /// of func_r on each
        /// item_<iterator>
        template < typename begin_t,
                 typename end_t,
                 template<typename> typename direction_,
                 template<typename> typename accessor_,
                 typename init_t,
                 typename func_r ,
                 typename ... params_t >
        struct navigate_t_
        {
            template < typename current_t,
                     typename tmp_t >
            struct navigate_t_impl_
            {
                using type =
                    lazy_t < navigate_t_impl_,
                    direction_<current_t>,
                    r_<func_r, tmp_t, accessor_<current_t>>, params_t... >;
            };


            template <typename tmp_t>
            struct navigate_t_impl_<end_t, tmp_t>
            {
                using type =
                    tmp_t;
            };


            using type =
                lazy_t<navigate_t_impl_, begin_t, init_t, params_t...>;
        };


        /// t_ shortcut for
        /// navigate_t_
        template < typename begin_t,
                 typename end_t,
                 template<typename>  typename direction_,
                 template<typename>  typename accessor_,
                 typename init_t,
                 typename func_r,
                 typename ... params_t >
        using navigate_t =
            t_<navigate_t_<begin_t, end_t, direction_, accessor_, init_t, func_r, params_t...>>;


        /// Specialization of
        /// navigate_t for the
        /// next_ direction
        template < typename begin_t,
                 typename end_t,
                 typename init_t,
                 typename func_r,
                 typename ... params_t >
        using forward_item_t =
            navigate_t<begin_t, end_t, next_, item_, init_t, func_r, params_t...>;


        /// Specialization of
        /// navigate_t for the
        /// prev_ direction
        template < typename begin_t,
                 typename end_t,
                 typename init_t,
                 typename func_r ,
                 typename ... params_t >
        using backward_item_t =
            navigate_t<begin_t, end_t, prev_, item_, init_t, func_r, params_t...>;


        /// Specialization of
        /// navigate_t for the
        /// next_ direction
        template < typename begin_t,
                 typename end_t,
                 typename init_t,
                 typename func_r ,
                 typename ... params_t >
        using forward_iter_t =
            navigate_t<begin_t, end_t, next_, idem_, init_t, func_r, params_t...>;


        /// Specialization of
        /// navigate_t for the
        /// prev_ direction
        template < typename begin_t,
                 typename end_t,
                 typename init_t,
                 typename func_r ,
                 typename ... params_t >
        using backward_iter_t =
            navigate_t<begin_t, end_t, prev_, idem_, init_t, func_r, params_t...>;


        template < typename begin_t,
                 typename end_t,
                 template<typename> typename direction_,
                 template<typename, typename ...> typename test_t,
                 typename ... params_t >
        struct while_t_
        {
            template < typename current_t,
                     typename is_valid_test_t >
            struct while_t_impl_:
                    while_t_impl_ <
                    direction_<current_t>,
                    test_t<next_<current_t>, params_t...> >
            {
            };


            template <typename current_t>
            struct while_t_impl_<current_t, std::true_type>
            {
                using type =
                    current_t ;
            };


            template <typename is_valid_test_t>
            struct while_t_impl_<end_t, is_valid_test_t>
            {
                using type =
                    end_t;
            };


            using type =
                lazy_t<while_t_impl_, begin_t, test_t<begin_t, params_t...>>;
        };


        template < typename begin_t,
                 typename end_t,
                 template<typename> typename direction_,
                 template<typename, typename ...> typename test_t,
                 typename ... params_t >
        using while_t =
            t_<while_t_<begin_t, end_t, direction_, test_t, params_t...>>;
            
            
        template < typename begin_t,
                 typename end_t,
                 template<typename, typename ...> typename test_t,
                 typename ... params_t >
        using while_forward_t =
            while_t<begin_t, end_t, next_, test_t, params_t...>;
            
            
        template < typename begin_t,
                 typename end_t,
                 template<typename, typename ...> typename test_t,
                 typename ... params_t >
        using while_backward_t =
            while_t<begin_t, end_t, prev_, test_t, params_t...>;


        template < typename current_t,
                 typename begin_t,
                 typename nb_steps_t >
        using is_same_distance_t =
            equal_to_t<nb_steps_t, distance_t<begin_t, current_t>>;


        template < typename begin_t,
                 typename nb_steps_t >
        using advance_t =
            item_<while_forward_t<begin_t, next_<last_t<begin_t>>, is_same_distance_t, next_<begin_t>, nb_steps_t>>;
    }
}

#endif
