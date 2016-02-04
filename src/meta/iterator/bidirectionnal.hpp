#ifndef __BRAIN_META_ITERATOR_BIDIRECTIONNAL_HPP__
# define  __BRAIN_META_ITERATOR_BIDIRECTIONNAL_HPP__

# include "../core.hpp"
# include "forward.hpp"

namespace meta
{
    /// Accessor for
    /// prev member
    template<typename type_t>
    using prev_ =
        typename type_t::prev;


    namespace impl
    {
        /// Returns true_ if
        /// type_t has prev
        /// member
        template < typename type_t,
                 typename =  void >
        struct has_prev_member
        {
            using type =
                meta::false_ ;
        };


        /// Returns true_ if
        /// type_t has prev
        /// member
        template <typename type_t>
        struct has_prev_member<type_t, void_<typename type_t::prev>>
        {
            using type =
                meta::true_;
        };
    }


    /// type_ shortcut
    /// of has_prev_member
    template<typename type_t>
    using has_prev_member =
        type_<impl::has_prev_member<type_t>>;


    /// Determines if type_t
    /// is a backward iterator
    template<typename type_t>
    using is_backward_iterator_ =
        and_ <
        has_item_member<type_t>,
        has_prev_member<type_t >>;


    /// Determines if type_t
    /// is a bidirectionnal
    /// iterator
    template<typename type_t>
    using is_bidirectional_iterator_ =
        and_ <
        is_forward_iterator_<type_t>,
        is_backward_iterator_<type_t >>;


    /// Bidirectional
    /// end iterator
    template<typename prev_t>
    struct bidirectional_iterator_end
    {
        using item = nil;
        using next = bidirectional_iterator_end;
        using prev = prev_t;
    };


    namespace impl
    {
        /// Builds bidirectionnal
        /// iterator from pack_t
        template < typename pack_t,
                 typename initial_prev_t >
        struct bi_builder_;


        /// Builds bidirectionnal
        /// iterator from pack_t
        template < template<typename...> typename pack_t,
                 typename item_t,
                 typename ... items_t >
        struct bi_builder_<pack_t<item_t, items_t...>, nil>
        {
            struct bidirectional_iterator
            {
                using item = item_t;
                using next = type_<bi_builder_<pack_t<items_t...>, bidirectional_iterator>>;
                using prev = bidirectional_iterator;
            };

            using type = bidirectional_iterator;
        };


        /// Builds bidirectionnal
        /// iterator from pack_t
        template < template<typename...> typename pack_t,
                 typename item_t,
                 typename ... items_t ,
                 typename prev_t >
        struct bi_builder_<pack_t<item_t, items_t...>, prev_t>
        {
            struct bidirectional_iterator
            {
                using item = item_t;
                using next = type_<bi_builder_<pack_t<items_t...>, bidirectional_iterator>>;
                using prev = prev_t;
            };

            using type = bidirectional_iterator;
        };


        /// Builds bidirectionnal
        /// iterator from pack_t
        template < template<typename...> typename pack_t,
                 typename item_t,
                 typename prev_t >
        struct bi_builder_<pack_t<item_t>, prev_t>
        {
            struct bidirectional_iterator
            {
                using item = item_t;
                using next = bidirectional_iterator_end<bidirectional_iterator>;
                using prev = prev_t;
            };

            using type = bidirectional_iterator;
        };
    }


    /// type_ shortcut
    /// of bi_builder_
    template<typename ... types_t>
    using bidirectional_iterator_builder_ =
        type_<impl::bi_builder_<pack<types_t...>, nil>>;


    /// Returns true_ if
    /// iterator_t has prev
    /// member
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
        /// Returns the last
        /// iterator before the end
        /// iterator
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


        /// Returns the last
        /// iterator before the end
        /// iterator
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
        /// Clones bidirectional
        /// sequence from begin_t
        /// and end_t iterators
        template < typename begin_t,
                 typename end_t,
                 typename prev_t >
        struct clone_bi_
        {
            struct bidirectional_iterator
            {
                using item = item_<begin_t>;
                using next = type_<clone_bi_<next_<begin_t>, end_t, bidirectional_iterator>>;
                using prev = prev_t;
            };


            using type = bidirectional_iterator;
        };


        /// Clones bidirectional
        /// sequence from begin_t
        /// and end_t iterators
        template < typename begin_t,
                 typename end_t >
        struct clone_bi_<begin_t, end_t, meta::nil>
        {
            struct bidirectional_iterator
            {
                using item = item_<begin_t>;
                using next = type_<clone_bi_<next_<begin_t>, end_t, bidirectional_iterator>>;
                using prev = bidirectional_iterator;
            };


            using type = bidirectional_iterator;
        };


        /// Clones bidirectional
        /// sequence from begin_t
        /// and end_t iterators
        template < typename end_t,
                 typename prev_t >
        struct clone_bi_<end_t, end_t, prev_t>
        {
            using type = bidirectional_iterator_end<prev_t>;
        };
    }


    /// type_ shortcut
    /// of clone_bidirectional_
    template < typename begin_t,
             typename end_t >
    using clone_bi_ =
        type_<impl::clone_bi_<begin_t, end_t, nil>>;


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
                meta::function_<meta::clone_bi_, begin_t, end_t> {};
    }

}

#endif
