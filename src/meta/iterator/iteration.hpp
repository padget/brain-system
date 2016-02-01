#ifndef __BRAIN_META_ITERATOR_ITERATION_HPP__
# define __BRAIN_META_ITERATOR_ITERATION_HPP__

# include "forward.hpp"
# include "bidirectionnal.hpp"
# include "iteration.hpp"

namespace meta
{
    namespace impl
    {
        template < typename begin_t,
                 typename end_t,
                 typename state_t,
                 typename accum_r >
        struct fold_
        {
            using _tmp =
                meta::return_<accum_r, state_t, begin_t>;

            using type =
                type_<fold_<next_<begin_t>, end_t, _tmp, accum_r>>;
        };

        template < typename end_t,
                 typename state_t,
                 typename accum_r >
        struct fold_<end_t, end_t, state_t, accum_r>
        {
            using type = state_t;
        };
    }

    template < typename begin_t,
             typename end_t,
             typename state_t,
             typename accum_r >
    using fold_ =
        meta::type_<impl::fold_<begin_t, end_t, state_t, accum_r>>;


    namespace impl
    {
        template < typename begin_t,
                 typename end_t,
                 typename state_t,
                 typename accum_r >
        struct rfold_
        {
            using _tmp =
                meta::return_<accum_r, state_t, prev_<end_t>>;

            using type =
                type_<rfold_<begin_t, prev_<end_t>, _tmp, accum_r>>;
        };

        template < typename begin_t,
                 typename state_t,
                 typename accum_r >
        struct rfold_<begin_t, begin_t, state_t, accum_r>
        {
            using type =
                state_t;
        };
    }

    template < typename begin_t,
             typename end_t,
             typename state_t,
             typename accum_r >
    using rfold_ =
        meta::type_<impl::rfold_<begin_t, end_t, state_t, accum_r>>;
}

#endif
