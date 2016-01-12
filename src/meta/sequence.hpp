#ifndef __BRAIN_META_SEQUENCE_HPP__
# define __BRAIN_META_SEQUENCE_HPP__


#include "iterator.hpp"

namespace brain
{
    namespace meta
    {

        /// Basic sequence that
        /// is built given an
        /// iterator type and
        /// a pack items_t ...
        template < template<typename...> typename iterator_t,
                 typename ... items_t >
        struct sequence
        {
            /// First iterator of
            /// the sequence
            using begin =
                iterator_t<pack<items_t...>>;

            /// Last iterator of
            /// the sequence
            using end =
                next_<last_t<begin>>;

            /// Size of the
            /// pack items_t...
            using size =
                sizeof_pack_t<items_t...>;


            /// Type of the iterator
            template<typename ... args_t>
            using iterator =
                iterator_t<args_t...>;
        };


        /// Specialization of
        /// the basic sequence
        /// with the bidirectionnal
        /// iterator
        template<typename ... items_t>
        struct list :
            public sequence<iterator, items_t...>
        { };


        /// Accessor to 
        /// begin member
        template<typename sequence_t>
        using begin_ =
            typename sequence_t::begin;


        /// Accessor to
        /// end member
        template<typename sequence_t>
        using end_ =
            typename sequence_t::end;


        /// Accessor to
        /// iterator type
        /// member
        template < typename sequence_t,
                 typename ... args_t >
        using iterator_ =
            typename sequence_t::template iterator<args_t...>;


        /// Determines if the
        /// sequence_t is empty
        /// or not
        template<typename sequence_t>
        using empty_t =
            equal_to_t <
            size_<sequence_t>,
            unsigned_t<0> >;


        /// Definition of 
        /// clear_t_
        template<typename sequence_t>
        struct clear_t_;

        
        /// Returns an empty
        /// sequence of the 
        /// same type of the
        /// sequence_t
        template < template<typename...> typename sequence_t,
                 typename ... items_t >
        struct clear_t_<sequence_t<items_t...>>
        {
            using type =
                sequence_t<>;
        };


        /// t_ shortcut for 
        /// clear_t_
        template<typename sequence_t>
        using clear_t =
            lazy_t<clear_t_, sequence_t>;


        /// Returns the first
        /// item of sequence_t
        template<typename sequence_t>
        using front_t =
            item_<begin_<sequence_t>>;


        /// Returns the last
        /// item of sequence_t
        template<typename sequence_t>
        using back_t =
            item_<prev_<end_<sequence_t>>>;


        /// Definition of 
        /// push_back_t_
        template < typename sequence_t,
                 typename type_t >
        struct push_back_t_;

    
        /// Pushes type_t at
        /// the end of 
        /// sequence_t
        template < template<typename...> typename sequence_t,
                 typename ... items_t,
                 typename type_t >
        struct push_back_t_ <
                sequence_t<items_t...>,
                type_t >
        {
            using type =
                sequence_t<items_t..., type_t>;
        };


        /// t_ shortcut for
        /// push_back_t_
        template < typename sequence_t,
                 typename type_t >
        using push_back_t =
            lazy_t<push_back_t_, sequence_t, type_t>;


        /// Definition of
        /// push_front_t_
        template < typename sequence_t,
                 typename type_t >
        struct push_front_t_;

        
        /// Pushes type_t at
        /// the front of 
        /// sequence_t
        template < template<typename...> typename sequence_t,
                 typename ... items_t,
                 typename type_t >
        struct push_front_t_ <
                sequence_t<items_t...>,
                type_t >
        {
            using type =
                sequence_t<type_t, items_t...>;
        };


        /// t_ shortcut for
        /// push_front_t_
        template < typename sequence_t,
                 typename type_t >
        using push_front_t =
            lazy_t<push_front_t_, sequence_t, type_t>;


        /// Pops the last
        /// item of sequence_t
        template<typename sequence_t>
        using pop_back_t =
            forward_t <
            begin_<sequence_t>,
            prev_<end_<sequence_t>>,
            clear_t<sequence_t>,
            as_r_<push_back_t> >;

        
         /// Pops the first
        /// item of sequence_t
        template<typename sequence_t>
        using pop_front_t =
            forward_t <
            next_<begin_<sequence_t>>,
            end_<sequence_t>,
            clear_t<sequence_t>,
            as_r_<push_back_t> >;


        /// Reverses the 
        /// sequence_t
        template<typename sequence_t>
        using reverse_t =
            forward_t <
            begin_<sequence_t>,
            end_<sequence_t> ,
            clear_t<sequence_t>,
            as_r_<push_front_t> >;
    }
}

#endif
