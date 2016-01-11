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
        };


        template<typename ... items_t>
        using vector =
            sequence<iterator, items_t...>;


        template<typename sequence_t>
        using begin_ =
            typename sequence_t::begin;


        template<typename sequence_t>
        using end_ =
            typename sequence_t::end;


        template<typename sequence_t>
        using front_t =
            item_<begin_<sequence_t>>;


        template<typename sequence_t>
        using back_t =
            item_<prev_<end_<sequence_t>>>;

    }
}

#endif
