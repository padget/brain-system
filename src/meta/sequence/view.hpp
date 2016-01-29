#ifndef __BRAIN_META_VIEW_HPP__
# define  __BRAIN_META_VIEW_HPP__

#include "iterator.hpp"

namespace brain
{
    namespace meta
    {
        /// ///////////////////////////////////// ///
        /// View : arbitrary begin_ end_ sequence ///
        /// ///////////////////////////////////// ///


        /// View is the base
        /// class of the view
        /// library. It takes
        /// a cloner, a begin
        /// and an end iterator
        template < template<typename, typename> typename cloner_t,
                 typename begin_t,
                 typename end_t >
        struct view
        {
            using begin =
                cloner_t<begin_t, end_t>;

            using end =
                next_<last_valid_<begin>>;
        };


        /// A forward view is
        /// a view that takes
        /// clone_forward as
        /// cloner
        template < typename begin_t,
                 typename end_t >
        struct forward_view :
                view<clone_forward_, begin_t, end_t>
        {
        };


        /// Alias for
        /// forward_view
        template < typename begin_t,
                 typename end_t >
        using forward_list_view =
            forward_view<begin_t, end_t>;


        /// A bidirectional view is
        /// a view that takes
        /// clone_bidirectional as
        /// cloner
        template < typename begin_t,
                 typename end_t >
        struct bidirectional_view :
                view<clone_bidirectional_, begin_t, end_t>
        {
        };


        /// Alias for
        /// bidirectional_view
        template < typename begin_t,
                 typename end_t >
        using list_view =
            bidirectional_view<begin_t, end_t>;
    }
}

#endif
