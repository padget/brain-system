#ifndef __BRAIN_META_CORE_PACk_HPP__
# define  __BRAIN_META_CORE_PACk_HPP__

#include "base.hpp"
#include "select.hpp"
#include "logic.hpp"

namespace meta
{
    /// Main support of the
    /// parameters pack
    template<typename ... items_t>
    struct pack { };


    namespace impl
    {
        /// Returns the size
        /// of a parameters pack
        template<typename pack_t>
        struct size_;


        /// Returns the number
        /// of types_t in pack_t
        template < template<typename...> typename pack_t,
                 typename... types_t >
        struct size_<pack_t<types_t...>>
        {
            using type =
                meta::size_t_<sizeof...(types_t)>;
        };
    }


    /// type_ shortcut
    /// for impl::size_
    template<typename pack_t>
    using size_ =
        type_<impl::size_<pack_t>>;


    /// Returns true_
    /// if the pack_t
    /// has no item
    template<typename pack_t>
    using empty_ =
        equal_to_<size_<pack_t>, size_t_<0>>;


    namespace impl
    {
        /// Concat any number
        /// of packs into one
        /// pack. The type of
        /// the returned pack
        /// is the same as the
        /// first of the list
        template<typename ... packs_t>
        struct cat_;


        /// Specialization that
        /// distribute the work
        /// between the two basic
        /// specializations
        template < typename pack1_t ,
                 typename ... others_t >
        struct cat_ <pack1_t, others_t...>
        {
            using type =
                type_<cat_<pack1_t, type_<cat_<others_t...>>>>;
        };


        /// Concatenates
        /// two packs
        template < template<typename ...> typename pack1_t,
                 typename ... items1_t,
                 template<typename ...> typename pack2_t,
                 typename ... items2_t >
        struct cat_ <
                pack1_t<items1_t...>,
                pack2_t<items2_t...> >
        {
            using type =
                pack1_t<items1_t..., items2_t...>;
        };

        /// Concatenates
        /// one pack
        template < template<typename ...> typename pack1_t,
                 typename ... items1_t >
        struct cat_<pack1_t<items1_t...>>
        {
            using type =
                pack1_t<items1_t...>;
        };
    }


    /// type_ shortcut
    /// for cat_
    template<typename ... packs_t>
    using cat_ =
        type_<impl::cat_<packs_t...>>;


    /// Push back type_t
    /// at the end of pack_t
    template < typename pack_t,
             typename type_t >
    using push_back_ =
        cat_<pack_t, pack<type_t>>;


    /// Push front type_t
    /// at the begin of pack_t
    template < typename pack_t,
             typename type_t >
    using push_front_ =
        cat_<pack<type_t>, pack_t>;


    namespace impl
    {
        /// Returns the nth
        /// type of pack_t
        template < typename pack_t,
                 typename index_t >
        struct at_;


        /// If type_t is
        /// the nth of
        /// pack_t, it will
        /// be returned,
        /// else, see next.
        template < template<typename ...> typename pack_t,
                 typename type_t,
                 typename ... types_t,
                 typename index_t >
        struct at_<pack_t<type_t, types_t...>, index_t>
        {
            using type =
                meta::eval_if_ <
                meta::equal_to_<index_t, meta::unsigned_<0>>,
                lazy::idem_<type_t>,
                at_<pack_t<types_t...>, meta::dec_<index_t> >>;

            static_assert(
                !meta::v_<meta::is_same_<meta::nil, type>>,
                "at_ : [OVERFLOW] index_t is out of parameters pack boundaries !!") ;
        };


        /// Returns nil
        /// if pack_t is
        /// empty.
        template < template<typename...> typename pack_t,
                 typename index_t >
        struct at_<pack_t<>, index_t>
        {
            /// Only here because of use it,
            /// but compilation failed thanks to below
            using type =
                meta::nil;


        };
    }


    template < typename pack_t,
             typename index_t >
    using at_ =
        type_<impl::at_<pack_t, index_t>>;


    namespace impl
    {
        /// Definition of
        /// clear_
        template<typename pack_t>
        struct clear_;


        /// Returns an empty
        /// sequence of the
        /// same type of the
        /// pack_t
        template < template<typename...> typename pack_t,
                 typename ... items_t >
        struct clear_<pack_t<items_t...>>
        {
            using type =
                pack_t<>;
        };
    }


    /// type_ shortcut for
    /// clear_t_
    template<typename pack_t>
    using clear_ =
        type_<impl::clear_<pack_t>>;


    namespace impl
    {
        template < template<typename ...> typename target_t,
                 typename pack_t >
        struct unpack;

        template < template<typename ...> typename target_t,
                 template<typename ...> typename pack_t,
                 typename... types_t >
        struct unpack<target_t, pack_t<types_t...>>
        {
            using type = target_t<types_t...>;
        };
    }

    template < template<typename ...> typename target_t,
             typename pack_t >
    using unpack =
        meta::type_<impl::unpack<target_t, pack_t>>;



    namespace lazy
    {
        /// Lasy signature
        /// of size_
        template<typename pack_t>
        struct size_:
                meta::function_<meta::size_, pack_t> {};


        /// Lasy signature
        /// of size_
        template<typename pack_t>
        struct empty_ :
                meta::function_<meta::empty_, pack_t> {};

        /// Lasy signature
        /// of size_
        template<typename ... packs_t>
        struct cat_ :
                meta::function_<meta::cat_, packs_t...> {};


        /// Lasy signature
        /// of size_
        template < typename pack_t,
                 typename type_t >
        struct push_back_ :
                meta::function_<meta::push_back_, pack_t, type_t> {};


        /// Lasy signature
        /// of size_
        template < typename pack_t,
                 typename type_t >
        struct push_front_ :
                meta::function_<meta::push_front_, pack_t, type_t> {};


        /// Lasy signature
        /// of size_
        template < typename pack_t,
                 typename index_t >
        struct at_ :
                meta::function_<meta::at_, pack_t, index_t> {};


        /// Lasy signature
        /// of size_
        template<typename pack_t>
        struct clear_ :
                meta::function_<meta::clear_, pack_t> {};
    }
}

#endif
