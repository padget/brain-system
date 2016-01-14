#include __BRAIN_META_VIEW_HPP__
# define  __BRAIN_META_VIEW_HPP__

#include "iterator.hpp"

namespace brain
{
    namespace meta
    {
        template < template<typename, typename> typename cloner_t,
                 typename begin_t,
                 typename end_t >
        struct view
        {
            using begin = cloner_t<begin_t, end_t>;
            using end = next_<last_t<begin>>;
        };


        template < typename begin_t,
                 typename end_t >
        using forward_view =
            view<clone_forward_t, begin_t, end_t>;


    }
}

#endif
