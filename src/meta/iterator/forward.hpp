#ifndef __BRAIN_META_ITERATOR_FORWARD_HPP__
# define  __BRAIN_META_ITERATOR_FORWARD_HPP__

#include "../core.hpp"


namespace meta
{
    /// Accessor for
    /// item member
    template<typename type_t>
    using item_ =
        typename type_t::item;


    /// Accessor for
    /// next member
    template<typename type_t>
    using next_ =
        typename type_t::next;


    namespace impl
    {
        /// Returns true_ if
        /// type_t has type
        /// member
        template < typename type_t,
                 typename =  void >
        struct has_item_member
        {
            using type =
                meta::false_ ;
        };


        /// Returns true_ if
        /// type_t has type
        /// member
        template <typename type_t>
        struct has_item_member<type_t, void_<typename type_t::item>>
        {
            using type =
                meta::true_;
        };
    }


    /// type_ shortcut
    /// of has_item_member
    template<typename type_t>
    using has_item_member =
        type_<impl::has_item_member<type_t>>;


    namespace impl
    {
        /// Returns true_ if
        /// type_t has next
        /// member
        template < typename type_t,
                 typename =  void >
        struct has_next_member
        {
            using type =
                meta::false_ ;
        };


        /// Returns true_ if
        /// type_t has next
        /// member
        template <typename type_t>
        struct has_next_member<type_t, void_<typename type_t::next>>
        {
            using type =
                meta::true_;
        };
    }
    
    
    /// type_ shortcut
    /// of has_next_member
    template<typename type_t>
    using has_next_member =
        type_<impl::has_next_member<type_t>>;


    /// Determines if type_t
    /// is a forward iterator
    template<typename type_t>
    using is_forward_iterator_ =
        meta::and_ <
        has_item_member<type_t>,
        has_next_member<type_t>>;


    /// Minimal index of
    /// iterator sequence
    using begin_iterator_index =
        long_ <0>;


    /// Index of ended
    /// iterator
    using end_iterator_index =
        long_ < -1 >;

    
    /// Forward end iterator
    struct forward_iterator_end
    {
        using item = nil;
        using next = forward_iterator_end;
    };
    

    namespace impl
    {
        template<typename pack_t>
        struct forward_builder_;

        template < template <typename...> typename pack_t,
                 typename item_t,
                 typename ... items_t >
        struct forward_builder_<pack_t<item_t, items_t...>>
        {
            struct forward_iterator
            {
                using item = item_t;
                using next = type_<forward_builder_<pack_t<items_t...> > >;
            };

            using type = forward_iterator;
        };

        template < template <typename...> typename pack_t,
                 typename item_t >
        struct forward_builder_<pack_t<item_t>>
        {
            struct forward_iterator
            {
                using item = item_t;
                using next = forward_iterator_end;
            };

            using type = forward_iterator;
        };
    }

    template<typename ... items_t>
    using forward_iterator_builder_ =
        type_<impl::forward_builder_<pack<items_t...>>>;


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
        template < typename begin_t,
                 typename end_t >
        struct clone_forward_
        {
            struct forward_iterator
            {
                using item =
                    item_<begin_t>;

                using next =
                    type_<clone_forward_<next_<begin_t>, end_t>>;
            };


            using type = forward_iterator;
        };

        template < typename end_t >
        struct clone_forward_<end_t, end_t>
        {
            using type =
                meta::forward_iterator_end;
        };
    }


    template < typename begin_t,
             typename end_t >
    using clone_forward_ =
        type_<impl::clone_forward_<begin_t, end_t>>;


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
        /// of clone_forward_
        template < typename begin_t,
                 typename end_t >
        struct clone_forward_ :
                meta::function_<meta::clone_forward_, begin_t, end_t> {};
    }




}
#endif
