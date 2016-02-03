#ifndef __BRAIN_META_ITERATOR_BIDIRECTIONNAL_HPP__
# define  __BRAIN_META_ITERATOR_BIDIRECTIONNAL_HPP__

# include "../core.hpp"
# include "forward.hpp"

namespace meta
{
    /// Accessor
    template<typename type_t>
    using prev_ =
        typename type_t::prev;

    namespace impl
    {
        template < typename type_t,
                 typename =  void >
        struct has_prev_member
        {
            using type =
                meta::false_ ;
        };

        template <typename type_t>
        struct has_prev_member<type_t, void_<typename type_t::prev>>
        {
            using type =
                meta::true_;
        };
    }


    template<typename type_t>
    using has_prev_member =
        type_<impl::has_prev_member<type_t>>;


    /// Determines if type_t
    /// is a backward iterator
    template<typename type_t>
    using is_backward_iterator_ =
        and_ <
        has_item_member<type_t>,
        has_prev_member<type_t>,
        has_index_member<type_t >>;


    /// Determines if type_t
    /// is a bidirectionnal
    /// iterator
    template<typename type_t>
    using is_bidirectional_iterator_ =
        and_ <
        is_forward_iterator_<type_t>,
        is_backward_iterator_<type_t >>;




    template < typename index_t,
             typename item_t,
             typename next_t,
             typename prev_builder_t >
    struct bidirectional_iterator:
            forward_iterator<index_t, item_t, next_t>
    {
        using prev =
            type_<prev_builder_t>;
    };


    template < typename item_t,
             typename next_t >
    struct bidirectional_iterator_begin:
            forward_iterator<begin_iterator_index, item_t, next_t>
    {
        using prev =
            bidirectional_iterator_begin;
    };


    template<typename prev_builder_t>
    struct bidirectional_iterator_end
    {
        using index =
            end_iterator_index;

        using item =
            nil;

        using next =
            bidirectional_iterator_end;

        using prev =
            type_<prev_builder_t>;
    };


    namespace impl
    {
        template < typename pack_t,
                 typename prev_builder_t = void,
                 typename index_t = begin_iterator_index >
        struct bidirectional_iterator_builder_;


        template < typename item_t,
                 typename ... items_t,
                 typename prev_builder_t >
        struct bidirectional_iterator_builder_ <
                meta::pack<item_t, items_t...>,
                prev_builder_t,
                begin_iterator_index >
        {
            using type =
                bidirectional_iterator_begin <
                item_t,
                type_<bidirectional_iterator_builder_<meta::pack<items_t...>, bidirectional_iterator_builder_, meta::inc_<begin_iterator_index>>>>;
        };


        template < typename item_t,
                 typename ... items_t,
                 typename prev_builder_t,
                 typename index_t >
        struct bidirectional_iterator_builder_<meta::pack<item_t, items_t...>, prev_builder_t, index_t>
        {
            using type =
                bidirectional_iterator <
                index_t,
                item_t,
                type_<bidirectional_iterator_builder_<meta::pack<items_t...>, bidirectional_iterator_builder_, meta::inc_<index_t>>>,
                prev_builder_t >;
        };


        template < typename prev_builder_t,
                 typename index_t >
        struct bidirectional_iterator_builder_<meta::pack<>, prev_builder_t, index_t>
        {
            using type = bidirectional_iterator_end<prev_builder_t>;
        };

    }

    template<typename ... types_t>
    using bidirectional_iterator_builder_ =
        type_<impl::bidirectional_iterator_builder_<pack<types_t...>>>;



    template<typename iterator_t>
    using has_prev_ =
        not_<is_same_<iterator_t, prev_<iterator_t>>>;

    namespace impl
    {
        /// Prev specialization
        template <typename iterator_t>
        struct is_valid_direction_<prev_, iterator_t>
        {
            using type =
                has_prev_<iterator_t>;
        };
    }


    namespace impl
    {
        ///
        template < typename iterator_t,
                 typename is_next_valid_t =
                 has_prev_<prev_<iterator_t> >>
        struct first_valid_;


        /// Returns the last
        /// iterator before the end
        /// iterator
        template <typename iterator_t>
        struct first_valid_ <
                iterator_t,
                true_ > :
                first_valid_<prev_<iterator_t>>
        {
        };


        template<typename iterator_t>
        struct first_valid_ <
                iterator_t,
                false_ >
        {
            using type =
                prev_<iterator_t>;
        };
    }

    /// type_ shortcut for
    /// last_valid_t_
    template<typename iterator_t>
    using first_valid_ =
        type_<impl::first_valid_<iterator_t>>;



    namespace impl
    {
        template < typename begin_t,
                 typename end_t,
                 typename prev_t,
                 typename index_t,
                 typename can_continue_t = meta::is_valid_direction_<next_, begin_t >>
        struct clone_bidirectional_;


        template < typename begin_t,
                 typename end_t,
                 typename prev_t >
        struct clone_bidirectional_<begin_t, end_t, prev_t, meta::begin_iterator_index, meta::true_>
        {
            using type =
                meta::bidirectional_iterator_begin <
                meta::item_<begin_t>,
                type_<clone_bidirectional_ <
                meta::next_<begin_t>,
                end_t,
                clone_bidirectional_,
                meta::inc_<meta::begin_iterator_index >>>>;
        };


        template < typename begin_t,
                 typename end_t,
                 typename prev_t,
                 typename index_t >
        struct clone_bidirectional_<begin_t, end_t, prev_t, index_t, meta::true_>
        {
            using type =
                meta::bidirectional_iterator <
                index_t,
                meta::item_<begin_t>,
                type_<clone_bidirectional_ <
                meta::next_<begin_t>,
                end_t,
                clone_bidirectional_,
                meta::inc_<index_t> >> ,
                prev_t >;
        };


        template < typename end_t,
                 typename prev_t,
                 typename index_t >
        struct clone_bidirectional_<end_t, end_t, prev_t, index_t, meta::true_>
        {
            using type =
                meta::bidirectional_iterator_end<prev_t>;
        };


        template < typename end_t,
                 typename prev_t,
                 typename index_t >
        struct clone_bidirectional_<end_t, end_t, prev_t, index_t, meta::false_>
        {
            using type =
                meta::bidirectional_iterator_end<prev_t>;
        };
    }


    template < typename begin_t,
             typename end_t >
    using clone_bidirectional_ =
        type_<impl::clone_bidirectional_<begin_t, end_t, nil, begin_iterator_index>>;


    namespace lazy
    {
        /// Lazy signature
        /// of prev_
        template<typename type_t>
        struct prev_ :
                meta::function_<meta::prev_, type_t> {};

        /// Lazy signature
        /// of has_prev_member
        template<typename type_t>
        struct has_prev_member :
                meta::function_<meta::has_prev_member, type_t> {};

        /// Lazy signature
        /// of is_backward_iterator_
        template<typename type_t>
        struct is_backward_iterator_ :
                meta::function_<meta::is_backward_iterator_, type_t> {};


        /// Lazy signature
        /// of is_bidirectional_iterator_
        template<typename type_t>
        struct is_bidirectional_iterator_ :
                meta::function_<meta::is_bidirectional_iterator_, type_t> {};


        /// Lazy signature
        /// of bidirectional_iterator_builder_
        template<typename pack_t>
        struct bidirectional_iterator_builder_ :
                meta::function_<meta::bidirectional_iterator_builder_, pack_t> {};


        /// Lazy signature
        /// of has_prev_
        template<typename iterator_t>
        struct has_prev_ :
                meta::function_<meta::has_prev_, iterator_t> {};


        /// Lazy signature
        /// of first_valid_
        template<typename iterator_t>
        struct first_valid_ :
                meta::function_<meta::first_valid_, iterator_t> {};


        /// Lazy signature
        /// of clone_bidirectional_
        template < typename begin_t,
                 typename end_t >
        struct clone_bidirectional_ :
                meta::function_<meta::clone_bidirectional_, begin_t, end_t> {};
    }
}

#endif
