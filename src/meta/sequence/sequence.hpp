#ifndef __BRAIN_META_SEQUENCE_SEQUENCE_HPP__
# define __BRAIN_META_SEQUENCE_SEQUENCE_HPP__


#include "../core.hpp"
#include "../iterator.hpp"

namespace meta
{
    /// Basic sequence that
    /// is built given an
    /// iterator type and
    /// a pack items_t ...
    template < template<typename...> typename iterator_builder_t,
             typename ... items_t >
    struct sequence
    {
        /// First iterator of
        /// the sequence
        using begin =
            iterator_builder_t<items_t...>;

        /// Last iterator of
        /// the sequence
        using end =
            next_<last_valid_<begin>>;

        /// Size of the
        /// pack items_t...
        using size =
            size_t_<sizeof...(items_t)>;
    };


    /// Specialization of
    /// the basic sequence
    /// with the bidirectionnal
    /// iterator
    template<typename ... items_t>
    struct list :
        public sequence<bidirectional_iterator_builder_, items_t...>
    {
        template<typename pack_t>
        using clone =
            meta::unpack<list, pack_t>;

    };


    /// Specialization of
    /// the basic sequence
    /// with the bidirectionnal
    /// iterator
    template<typename ... items_t>
    struct forward_list :
        public sequence<forward_iterator_builder_, items_t...>
    {
        template<typename pack_t>
        using clone =
            meta::unpack<forward_list, pack_t>;
    };


    /// Accessor to
    /// begin member
    template<typename type_t>
    using begin_ =
        typename type_t::begin;



    /// Accessor to
    /// end member
    template<typename type_t>
    using end_ =
        typename type_t::end;


    /// Accessor to
    /// clone member
    template < typename sequence_t,
             typename pack_t >
    using clone_ =
        typename sequence_t::
        template clone<pack_t>;


    /// Returns the first
    /// item of sequence_t
    template<typename sequence_t>
    using front_ =
        item_<begin_<sequence_t>>;


    /// Returns the last
    /// item of sequence_t
    template<typename sequence_t>
    using back_ =
        item_<last_valid_<begin_<sequence_t>>>;


    namespace lazy
    {
        /// Lazy signature
        /// of begin_
        template<typename type_t>
        struct begin_ :
            meta::function_<meta::begin_, type_t>{};



         /// Lazy signature
        /// of end_
        template<typename type_t>
        struct end_ :
            meta::function_<meta::end_, type_t>{};


        /// Lazy signature
        /// of clone_
        template < typename sequence_t,
                 typename pack_t >
        struct clone_ :
            meta::function_<meta::clone_, sequence_t, pack_t>{};


         /// Lazy signature
        /// of front_
        template<typename sequence_t>
        struct front_ :
           meta::function_<meta::front_, sequence_t>{};


        /// Lazy signature
        /// of back_
        template<typename sequence_t>
        struct back_ :
           meta::function_<meta::back_, sequence_t>{};
    }
}

#endif
