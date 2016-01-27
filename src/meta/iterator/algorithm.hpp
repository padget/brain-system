#ifndef __BRAIN_META_ITERATOR_ALGORITHM_HPP__
# define  __BRAIN_META_ITERATOR_ALGORITHM_HPP__

# include "forward.hpp"
# include "bidirectionnal.hpp"
# include "iteration.hpp"

namespace brain
{
    namespace meta
    {
        namespace iter
        {

            template < typename begin_t,
                     typename nb_steps_t >
            using advance_ =
                fold_ <
                    begin_t,
                    next_<last_valid_<begin_t>>,
                    begin_t,
                    meta::lazy::if_ <
                        meta::lazy::less_ <
                            iter::impl::distance_<begin_t, _1_>,
                            nb_steps_t > ,
                        member::next_<_1_>,
                        _0_ >>;



            namespace test_advance
            {
                using begin_t = forward_iterator_builder_<pack<int, double, short>>;

                using next1_t = next_<begin_t>; /// double
                using next2_t = next_<next1_t>; /// short
                using end_t = next_<next2_t>; /// nil

                static_assert(v_<is_same_<begin_t, advance_<begin_t, long_<0>>>>, "");
                static_assert(v_<is_same_<next1_t, advance_<next1_t, long_<0>>>>, "");
                static_assert(v_<is_same_<next2_t, advance_<next2_t, long_<0>>>>, "");
                static_assert(v_<is_same_<end_t, advance_<end_t, long_<0>>>>, "");

                static_assert(v_<is_same_<next1_t, advance_<begin_t, long_<1>>>>, "");
                static_assert(v_<is_same_<next2_t, advance_<begin_t, long_<2>>>>, "");
                static_assert(v_<is_same_<end_t, advance_<begin_t, long_<3>>>>, "");

                static_assert(v_<is_same_<end_t, advance_<next1_t, long_<2>>>>, "");
            }
        }
    }
}

#endif
