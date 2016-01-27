#ifndef __BRAIN_META_ITERATOR_ITERATION_HPP__
# define __BRAIN_META_ITERATOR_ITERATION_HPP__

# include "forward.hpp"
# include "bidirectionnal.hpp"
# include "iteration.hpp"

namespace brain
{
    namespace meta
    {
        namespace iter
        {
            namespace impl
            {
                template < typename begin_t,
                         typename end_t,
                         typename state_t,
                         typename accum_r,
                         template<typename> typename access_t >
                struct fold_
                {
                    using _tmp =
                        meta::return_<accum_r, state_t, access_t<begin_t>>;

                    using type =
                        type_<fold_<next_<begin_t>, end_t, _tmp, accum_r, access_t>>;
                };

                template < typename end_t,
                         typename state_t,
                         typename accum_r,
                         template<typename> typename access_t >
                struct fold_<end_t, end_t, state_t, accum_r, access_t>
                {
                    using type = state_t;
                };
            }


            template < typename begin_t,
                     typename end_t,
                     typename state_t,
                     typename accum_r, 
                     template<typename> typename access_t>
            using fold_ =
                meta::type_<impl::fold_<begin_t, end_t, state_t, accum_r, access_t>>;


            template < typename begin_t,
                     typename end_t,
                     typename state_t,
                     typename accum_r >
            using iter_fold_ =
                fold_<begin_t, end_t, state_t, accum_r, idem_>;

            namespace test_iter_fold
            {
                using begin_t = iter::forward_iterator_builder_<pack<int, double, short>>;
                using end_t = iter::next_<iter::last_valid_<begin_t>>;

                using test_fold = fold_<begin_t, end_t , pack<>, meta::lazy::push_back_<_0_, _1_>, iter::item_>;


            }


            /// Default accumulator
            /// that returns only
            /// the new result without
            /// considering of olds.
            struct default_accumulator_
            {
                template < typename old_t,
                         typename res_t >
                using return_ =
                    res_t;
            };


            /// Default test
            /// that returns only
            /// the true_ value if
            /// the current_t is
            /// same type as end_t.
            template<typename end_t>
            struct default_test_
            {
                template<typename current_t>
                using return_ =
                    not_<is_same_<end_t, current_t>>;
            };


            namespace impl
            {
                /// Navigates between
                /// begin_t and end_t
                /// thanks to direction_t
                /// to accumulate the
                /// results of each call
                /// of func_r on each
                /// item_<iterator>
                template < typename begin_t,
                         typename end_t,
                         template<typename> typename direction_,
                         template<typename> typename accessor_,
                         typename init_t,
                         typename unary_r,
                         typename test_r,
                         typename accum_r = default_accumulator_ >
                struct navigate_
                {
                    template < typename current_t,
                             typename tmp_t,
                             typename test_validated_t = meta::return_<test_r, current_t>, /// Nominal continue condition
                             typename is_out_range_t = meta::is_same_<end_t, current_t> >
                    struct navigate_impl_;


                    template < typename current_t,
                             typename tmp_t >
                    struct navigate_impl_<current_t, tmp_t, true_, false_>:
                            navigate_impl_<direction_<current_t>, meta::return_<accum_r, tmp_t, meta::return_<unary_r, accessor_<current_t>>>>
                    {
                    };

                    template < typename current_t,
                             typename tmp_t >
                    struct navigate_impl_<current_t, tmp_t, false_, false_>
                    {
                        using type =
                            tmp_t;
                    };

                    template < typename current_t,
                             typename tmp_t >
                    struct navigate_impl_<current_t, tmp_t, true_, true_>
                    {
                        using type =
                            meta::return_<accum_r, tmp_t, meta::return_<unary_r, current_t>>;
                    };


                    template < typename current_t,
                             typename tmp_t >
                    struct navigate_impl_<current_t, tmp_t, false_, true_>
                    {
                        using type =
                            tmp_t;
                    };

                    using type =
                        type_<navigate_impl_<begin_t, init_t>>;
                };
            }


            /// type_ shortcut for
            /// navigate_t_
            template < typename begin_t,
                     typename end_t,
                     template<typename>  typename direction_,
                     template<typename>  typename accessor_,
                     typename init_t,
                     typename unary_r,
                     typename test_r,
                     typename accum_r = default_accumulator_ >
            using navigate_ =
                type_<impl::navigate_<begin_t, end_t, direction_, accessor_, init_t, unary_r, test_r, accum_r>>;


            /// Alias for navigate_
            /// that use next_ direction
            template < typename begin_t,
                     typename end_t,
                     template<typename>  typename accessor_,
                     typename init_t,
                     typename unary_r,
                     typename test_r ,
                     typename accum_r  = default_accumulator_ >
            using navigate_next_ =
                navigate_<begin_t, end_t, next_, accessor_, init_t, unary_r, test_r, accum_r>;


            /// Alias for navigate_
            /// that use prev_ direction
            template < typename begin_t,
                     typename end_t,
                     template<typename>  typename accessor_,
                     typename init_t,
                     typename unary_r,
                     typename test_r ,
                     typename accum_r  = default_accumulator_ >
            using navigate_prev_ =
                navigate_<begin_t, end_t, prev_, accessor_, init_t, unary_r, test_r, accum_r>;
        }
    }

}

#endif
