#ifndef __BRAIN_META_ITERATOR_FORWARD_HPP__
# define  __BRAIN_META_ITERATOR_FORWARD_HPP__

#include "../core.hpp"


namespace meta
{
    template<typename type_t>
    using item_ =
        typename type_t::item;

    template<typename type_t>
    using next_ =
        typename type_t::next;

    template<typename type_t>
    using index_ =
        typename type_t::index;

    namespace impl
    {
        template < typename type_t,
                 typename =  void >
        struct has_item_member
        {
            using type =
                meta::false_ ;
        };

        template <typename type_t>
        struct has_item_member<type_t, void_<typename type_t::item>>
        {
            using type =
                meta::true_;
        };
    }


    template<typename type_t>
    using has_item_member =
        type_<impl::has_item_member<type_t>>;

    namespace impl
    {
        template < typename type_t,
                 typename =  void >
        struct has_next_member
        {
            using type =
                meta::false_ ;
        };

        template <typename type_t>
        struct has_next_member<type_t, void_<typename type_t::next>>
        {
            using type =
                meta::true_;
        };
    }


    template<typename type_t>
    using has_next_member =
        type_<impl::has_next_member<type_t>>;

    namespace impl
    {
        template < typename type_t,
                 typename =  void >
        struct has_index_member
        {
            using type =
                meta::false_ ;
        };

        template <typename type_t>
        struct has_index_member<type_t, void_<typename type_t::index>>
        {
            using type =
                meta::true_;
        };
    }


    template<typename type_t>
    using has_index_member =
        type_<impl::has_index_member<type_t>>;


    /// Determines if type_t
    /// is a forward iterator
    template<typename type_t>
    using is_forward_iterator_ =
        meta::and_ <
        has_item_member<type_t>,
        has_next_member<type_t>,
        has_index_member<type_t >>;


    /// Minimal index of
    /// iterator sequence
    using begin_iterator_index =
        long_ <0>;



    /// Index of ended
    /// iterator
    using end_iterator_index =
        long_ < -1 >;


    template < typename index_t,
             typename item_t,
             typename next_builder_t >
    struct forward_iterator
    {
        /// Is a constant
        /// index that indicates
        /// the rank of the
        /// iterator in the
        /// sequence
        using index =
            index_t;


        /// The embedded
        /// type element
        using item =
            item_t;


        /// A reference
        /// to the next
        /// iterator
        using next =
            type_<next_builder_t>;
    };


    struct forward_iterator_end
    {
        using index =
            end_iterator_index;


        /// The final element
        /// is arbitrary nil
        using item =
            nil;


        /// Infinite next
        /// call to the
        /// end element
        using next =
            forward_iterator_end;
    };


    namespace impl
    {
        /// Forward iterator
        /// builder. Based on
        /// a pack of list, and
        /// by default the first
        /// index is equals to
        /// begin_iterator_index_t
        template < typename pack_t,
                 typename index_t =
                 begin_iterator_index >
        struct forward_iterator_builder_;


        template < typename item_t,
                 typename ... items_t,
                 typename index_t >
        struct forward_iterator_builder_<meta::pack<item_t, items_t...>, index_t>
        {
            using type =
                forward_iterator < index_t, item_t,
                forward_iterator_builder_<meta::pack<items_t...>, meta::inc_<index_t>> >;
        };

        template<typename index_t>
        struct forward_iterator_builder_<pack<>, index_t>
        {
            using type =
                forward_iterator_end;
        };
    }


    template<typename ... types_t>
    using forward_iterator_builder_ =
        type_<impl::forward_iterator_builder_<pack<types_t...>>>;


    template<typename iterator_t>
    using has_next_ =
        not_<is_same_<iterator_t, next_<iterator_t>>>;


    namespace impl
    {
        template < template<typename> typename direction_,
                 typename iterator_t >
        struct is_valid_direction_;


        template <typename iterator_t>
        struct is_valid_direction_<next_, iterator_t>
        {
            using type =
                meta::has_next_<iterator_t>;
        };
    }

    template < template<typename> typename direction_,
             typename iterator_t >
    using is_valid_direction_ =
        type_<impl::is_valid_direction_<direction_, iterator_t>>;


    namespace impl
    {
        ///
        template < typename iterator_t,
                 typename is_next_valid_t =
                 has_next_<next_<iterator_t> >>
        struct last_valid_;


        /// Returns the last
        /// iterator before the end
        /// iterator
        template <typename iterator_t>
        struct last_valid_ <
                iterator_t,
                true_ > :
                last_valid_<next_<iterator_t>>
        {
        };


        template<typename iterator_t>
        struct last_valid_ <
                iterator_t,
                false_ >
        {
            using type =
                iterator_t;
        };
    }

    /// type_ shortcut for
    /// last_valid_t_
    template<typename iterator_t>
    using last_valid_ =
        type_<impl::last_valid_<iterator_t>>;


    namespace impl
    {
        /// Computes the
        /// distance between
        /// two iterators
        template < typename begin_t,
                 typename end_t >
        struct distance_
        {
            using type =
                meta::minus_ <
                meta::index_<end_t>,
                meta::index_<begin_t> >;
        };


        /// Specialization for
        /// end iterator that
        /// returns the distance
        /// between the begin_t
        /// and prev_<end_t>
        template <typename begin_t>
        struct distance_<begin_t, next_<meta::last_valid_<begin_t>>>
        {
            using type =
                meta::if_ < meta::is_same_<begin_t, next_<meta::last_valid_<begin_t>>>,
                meta::unsigned_<0>,
                meta::inc_<minus_<meta::index_<meta::last_valid_<begin_t>>, meta::index_<begin_t>>> >;
        };
    }


    /// type_ shortcut for
    /// distance_t_
    template < typename begin_t,
             typename end_t >
    using distance_ =
        type_<impl::distance_<begin_t, end_t>>;


    namespace impl
    {
        template < typename begin_t,
                 typename end_t,
                 typename index_t,
                 typename can_continue_t =
                 meta::is_valid_direction_<next_, begin_t >>
        struct clone_forward_;

        template < typename begin_t,
                 typename end_t,
                 typename index_t >
        struct clone_forward_<begin_t, end_t, index_t, true_>
        {
            using type = meta::forward_iterator <
                         index_t,
                         meta::item_<begin_t>,
                         clone_forward_<meta::next_<begin_t>, end_t, meta::inc_<index_t> >>;
        };

        template < typename end_t,
                 typename index_t >
        struct clone_forward_<end_t, end_t, index_t, meta::true_>
        {
            using type =
                meta::forward_iterator_end;
        };


        template < typename begin_t,
                 typename end_t,
                 typename index_t >
        struct clone_forward_<begin_t, end_t, index_t, meta::false_>
        {
            using type = meta::forward_iterator_end;
        };
    }


    template < typename begin_t,
             typename end_t >
    using clone_forward_ =
        type_<impl::clone_forward_<begin_t, end_t, begin_iterator_index>>;


    namespace lazy
    {
        /// Lazy signature
        /// of item_
        template<typename type_t>
        struct item_ :
                meta::function_<meta::item_, type_t> {};


        /// Lazy signature
        /// of next_
        template<typename type_t>
        struct next_ :
                meta::function_<meta::next_, type_t> {};


        /// Lazy signature
        /// of index_
        template<typename type_t>
        struct index_ :
                meta::function_<meta::index_, type_t> {};


        /// Lazy signature
        /// of is_forward_iterator_
        template<typename type_t>
        struct is_forward_iterator_ :
                meta::function_<meta::is_forward_iterator_, type_t> {};


        /// Lazy signature
        /// of forward_iterator_builder_
        template<typename pack_t>
        struct forward_iterator_builder_ :
                meta::function_<meta::forward_iterator_builder_, pack_t> {};


        /// Lazy signature
        /// of has_next_
        template<typename iterator_t>
        struct has_next_ :
                meta::function_<meta::has_next_, iterator_t> {};


        /// Lazy signature
        /// of is_valid_direction_
        template < template<typename> typename direction_,
                 typename iterator_t >
        struct is_valid_direction_ :
                impl::is_valid_direction_<direction_, iterator_t> {};


        /// Lazy signature
        /// of last_valid_
        template<typename iterator_t>
        struct last_valid_ :
                meta::function_<meta::last_valid_, iterator_t> {};


        /// Lazy signature
        /// of distance_
        template < typename begin_t,
                 typename end_t >
        struct distance_ :
                meta::function_<meta::distance_, begin_t, end_t> {};


        /// Lazy signature
        /// of clone_forward_
        template < typename begin_t,
                 typename end_t >
        struct clone_forward_ :
                meta::function_<meta::clone_forward_, begin_t, end_t> {};
    }
}
#endif
