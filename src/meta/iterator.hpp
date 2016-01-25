#ifndef __BRAIN_META_ITERATOR_HPP__
# define __BRAIN_META_ITERATOR_HPP__

#include "core.hpp"

namespace brain
{
    namespace meta
    {

        member_(item)
        member_(next)
        member_(prev)
        member_(index)


        /// Determines if type_t
        /// is a forward iterator
        template<typename type_t>
        using is_forward_iterator_ =
            and_ <
            has_item_member<type_t>,
            has_next_member<type_t>,
            has_index_member<type_t >>;


        /// Determines if type_t
        /// is a backward iterator
        template<typename type_t>
        using is_backward_iterator_ =
            and_ <
            has_item_member<type_t>,
            has_prev_member<type_t>,
            has_index_member<type_t >>;


        /// Determines if type_t
        /// is a bidirectionnal
        /// iterator
        template<typename type_t>
        using is_bidirectional_iterator_ =
            and_ <
            is_forward_iterator_<type_t>,
            is_backward_iterator_<type_t >>;


        /// //////////////// ///
        /// Forward Iterator ///
        /// //////////////// ///


        /// Minimal index of
        /// iterator sequence
        using begin_iterator_index =
            long_ <0>;


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


        template<typename pack_t>
        using forward_iterator_builder_ =
            type_<impl::forward_iterator_builder_<pack_t>>;


        namespace lazy
        {
            template<typename pack_t>
            struct forward_iterator_builder_ :
                    function_<meta::forward_iterator_builder_, pack_t> {};
        }


        namespace test_forward_iterator
        {
            using begin_t = forward_iterator_builder_<pack<int, double, float>>;

            using next1_t = next_<begin_t>;
            using next2_t = next_<next1_t>;
            using end_t = next_<next2_t>;

            static_assert(v_<is_same_<item_<begin_t>, int>>, "");
            static_assert(v_<is_same_<item_<next1_t>, double>>, "");
            static_assert(v_<is_same_<item_<next2_t>, float>>, "");
            static_assert(v_<is_same_<item_<end_t>, nil>>, "");

            static_assert(v_<equal_to_<index_<begin_t>, begin_iterator_index>>, "");
            static_assert(v_<equal_to_<index_<next1_t>, unsigned_<1>>>, "");
            static_assert(v_<equal_to_<index_<next2_t>, unsigned_<2>>>, "");
            static_assert(v_<equal_to_<index_<end_t>, end_iterator_index>>, "");
        }


        /// ////////////////////// ///
        /// Bidirectional Iterator ///
        /// ////////////////////// ///


        template < typename index_t,
                 typename item_t,
                 typename next_builder_t,
                 typename prev_builder_t >
        struct bidirectional_iterator:
                forward_iterator<index_t, item_t, next_builder_t>
        {
            using prev =
                type_<prev_builder_t>;
        };


        template < typename item_t,
                 typename next_builder_t >
        struct bidirectional_iterator_begin:
                forward_iterator<begin_iterator_index, item_t, next_builder_t>
        {
            using prev =
                bidirectional_iterator_begin;
        };


        template<typename prev_builder_t>
        struct bidirectional_iterator_end
        {
            using index =
                end_iterator_index;

            using item =
                nil;

            using next =
                bidirectional_iterator_end;

            using prev =
                type_<prev_builder_t>;
        };


        namespace impl
        {
            template < typename pack_t,
                     typename prev_builder_t = void,
                     typename index_t = begin_iterator_index >
            struct bidirectional_iterator_builder_;


            template < typename item_t,
                     typename ... items_t,
                     typename prev_builder_t >
            struct bidirectional_iterator_builder_ <
                    meta::pack<item_t, items_t...>,
                    prev_builder_t,
                    begin_iterator_index >
            {
                using type =
                    bidirectional_iterator_begin <
                    item_t,
                    bidirectional_iterator_builder_<meta::pack<items_t...>, bidirectional_iterator_builder_, meta::inc_<begin_iterator_index>> >;
            };


            template < typename item_t,
                     typename ... items_t,
                     typename prev_builder_t,
                     typename index_t >
            struct bidirectional_iterator_builder_<meta::pack<item_t, items_t...>, prev_builder_t, index_t>
            {
                using type =
                    bidirectional_iterator <
                    index_t,
                    item_t,
                    bidirectional_iterator_builder_<meta::pack<items_t...>, bidirectional_iterator_builder_, meta::inc_<index_t>>,
                    prev_builder_t >;
            };


            template < typename prev_builder_t,
                     typename index_t >
            struct bidirectional_iterator_builder_<meta::pack<>, prev_builder_t, index_t>
            {
                using type = bidirectional_iterator_end<prev_builder_t>;
            };

        }

        template<typename pack_t>
        using bidirectional_iterator_builder_ =
            type_<impl::bidirectional_iterator_builder_<pack_t>>;


        namespace lazy
        {
            template<typename pack_t>
            struct bidirectional_iterator_builder_ :
                    function_<meta::bidirectional_iterator_builder_, pack_t> {};
        }


        namespace test_bidirectionnal_iterator
        {
            using begin_t = bidirectional_iterator_builder_<pack<int, double, float>>;
            using next1_t = next_<begin_t>;
            using next2_t = next_<next1_t>;
            using end_t = next_<next2_t>;

            using prev2_t = prev_<end_t>;
            using prev1_t = prev_<prev2_t>;
            using prev0_t = prev_<prev1_t>;

            static_assert(v_<is_same_<item_<begin_t>, int>>, "");
            static_assert(v_<is_same_<item_<next1_t>, double>>, "");
            static_assert(v_<is_same_<item_<next2_t>, float>>, "");
            static_assert(v_<is_same_<item_<end_t>, nil>>, "");

            static_assert(v_<is_same_<item_<prev2_t>, float>>, "");
            static_assert(v_<is_same_<item_<prev1_t>, double>>, "");
            static_assert(v_<is_same_<item_<prev0_t>, int>>, "");

            static_assert(v_<equal_to_<index_<begin_t>, begin_iterator_index>>, "");
            static_assert(v_<equal_to_<index_<next1_t>, unsigned_<1>>>, "");
            static_assert(v_<equal_to_<index_<next2_t>, unsigned_<2>>>, "");
            static_assert(v_<equal_to_<index_<end_t>, end_iterator_index>>, "");

            static_assert(v_<equal_to_<index_<prev2_t>, unsigned_<2>>>, "");
            static_assert(v_<equal_to_<index_<prev1_t>, unsigned_<1>>>, "");
            static_assert(v_<equal_to_<index_<prev0_t>, begin_iterator_index>>, "");
        }


        /// //////////////////// ///
        /// Test of end iterator ///
        /// //////////////////// ///



        template<typename iterator_t>
        using has_next_ =
            not_<is_same_<iterator_t, next_<iterator_t>>>;


        namespace lazy
        {
            template<typename iterator_t>
            struct has_next_ :
                    function_<meta::has_next_, iterator_t> {};
        }

        namespace test_has_next
        {
            using begin_t = forward_iterator_builder_<pack<int, int, int>>;
            using next1_t = next_<begin_t>;
            using next2_t = next_<next1_t>;
            using end_t = next_<next2_t>;
            using end2_t = next_<end_t>;

            static_assert(v_<has_next_<begin_t>>, "");
            static_assert(v_<has_next_<next1_t>>, "");
            static_assert(v_<has_next_<next2_t>>, "");
            static_assert(v_<not_<has_next_<end_t>>>, "");
            static_assert(v_<not_<has_next_<end2_t>>>, "");
        }


        template<typename iterator_t>
        using has_prev_ =
            not_<is_same_<iterator_t, prev_<iterator_t>>>;

        namespace lazy
        {
            template<typename iterator_t>
            struct has_prev_ :
                function_<meta::has_prev_, iterator_t>{};
        }


        namespace test_has_prev
        {
            using begin_t = bidirectional_iterator_builder_<pack<int, int, int>>;

            using next1_t = next_<begin_t>;
            using next2_t = next_<next1_t>;
            using end_t = next_<next2_t>;
            using end2_t = next_<end_t>;

            using prev2_t = prev_<end2_t>;
            using prev1_t = prev_<prev2_t>;
            using prev0_t = prev_<prev1_t>;

            static_assert(v_<has_next_<begin_t>>, "");
            static_assert(v_<has_next_<next1_t>>, "");
            static_assert(v_<has_next_<next2_t>>, "");
            static_assert(v_<not_<has_next_<end_t>>>, "");
            static_assert(v_<not_<has_next_<end2_t>>>, "");

            static_assert(v_<has_prev_<end2_t>>, "");
            static_assert(v_<has_prev_<prev2_t>>, "");
            static_assert(v_<has_prev_<prev1_t>>, "");
            static_assert(v_<not_<has_prev_<prev0_t>>>, "");
        }


        namespace impl
        {
            template < template<typename> typename direction_,
                     typename iterator_t >
            struct is_valid_direction_;


            template <typename iterator_t>
            struct is_valid_direction_<next_, iterator_t>
            {
                using type =
                    has_next_<iterator_t>;
            };


            template <typename iterator_t>
            struct is_valid_direction_<prev_, iterator_t>
            {
                using type =
                    has_prev_<iterator_t>;
            };
        }

        template < template<typename> typename direction_,
                 typename iterator_t >
        using is_valid_direction_ =
            type_<impl::is_valid_direction_<direction_, iterator_t>>;


        namespace lazy
        {
            template < template<typename> typename direction_,
                     typename iterator_t >
            using is_valid_direction_ =
                impl::is_valid_direction_<direction_, iterator_t>;
        }


        namespace test_is_valid_direction
        {
            using begin_t = bidirectional_iterator_builder_<pack<int, float, double>>;
            using next1_t = next_<begin_t>;
            using next2_t = next_<next1_t>;
            using end_t = next_<next2_t>;

            static_assert(v_<is_valid_direction_<next_, begin_t>>, "");
            static_assert(v_<is_valid_direction_<next_, next1_t>>, "");
            static_assert(v_<is_valid_direction_<next_, next2_t>>, "");
            static_assert(!v_<is_valid_direction_<next_, end_t>>, "");
        }



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


        namespace lazy
        {
            /// Lazy signature
            /// of last_valid_
            template<typename iterator_t>
            struct last_valid_ :
                function_<meta::last_valid_, iterator_t>{};
        }


        namespace test_last_valid
        {
            using begin_t = forward_iterator_builder_<pack<int, double, short>>;
            using next1_t = next_<begin_t>; /// double
            using next2_t = next_<next1_t>; /// short

            static_assert(v_<is_same_<next2_t, last_valid_<begin_t>>>, "");
        }


        namespace impl
        {
            ///
            template < typename iterator_t,
                     typename is_next_valid_t =
                     has_prev_<prev_<iterator_t> >>
            struct first_valid_;


            /// Returns the last
            /// iterator before the end
            /// iterator
            template <typename iterator_t>
            struct first_valid_ <
                    iterator_t,
                    true_ > :
                    first_valid_<prev_<iterator_t>>
            {
            };


            template<typename iterator_t>
            struct first_valid_ <
                    iterator_t,
                    false_ >
            {
                using type =
                    prev_<iterator_t>;
            };
        }

        /// type_ shortcut for
        /// last_valid_t_
        template<typename iterator_t>
        using first_valid_ =
            type_<impl::first_valid_<iterator_t>>;


        namespace lazy
        {
            /// Lazy signature
            /// of first_valid_
            template<typename iterator_t>
            struct first_valid_ :
                function_<meta::first_valid_, iterator_t>{};
        }

        namespace test_first_valid
        {
            using begin_t = bidirectional_iterator_builder_<pack<int, double, short>>;
            using next1_t = next_<begin_t>; /// double
            using next2_t = next_<next1_t>; /// short

            static_assert(v_<is_same_<begin_t, first_valid_<next2_t>>>, "");
        }


        /// ////////////// ///
        /// Iteration Ways ///
        /// ////////////// ///
        ///
        /// There is many ways to
        /// iterate over a iterator
        /// sequence. however for
        /// maintenability, all these
        /// ways is here generalized
        /// in a single template


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


        namespace lazy
        {
            /// Lazy signature
            /// of navigate_
            template < typename begin_t,
                     typename end_t,
                     template<typename>  typename direction_,
                     template<typename>  typename accessor_,
                     typename init_t,
                     typename unary_r,
                     typename test_r ,
                     typename accum_r = default_accumulator_ >
            using navigate_ =
                impl::navigate_<begin_t, end_t, direction_, accessor_, init_t, unary_r, test_r, accum_r>;
        }


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
                    minus_ <
                    index_<end_t>,
                    index_<begin_t> >;
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
                    if_ < is_same_<begin_t, next_<meta::last_valid_<begin_t>>>,
                    unsigned_<0>,
                    inc_<minus_<index_<meta::last_valid_<begin_t>>, index_<begin_t>>> >;
            };
        }


        /// type_ shortcut for
        /// distance_t_
        template < typename begin_t,
                 typename end_t >
        using distance_ =
            type_<impl::distance_<begin_t, end_t>>;


        namespace lazy
        {
            /// Lazy signature
            /// of distance_
            template < typename begin_t,
                     typename end_t >
            struct distance_ :
                function_<meta::distance_, begin_t, end_t>{};
        }


        namespace test_distance
        {
            using begin_t = forward_iterator_builder_<pack<int, double, short>>;
            using next1_t = next_<begin_t>; /// double
            using next2_t = next_<next1_t>; /// short
            using end_t = next_<next2_t>; /// nil

            static_assert(v_<is_same_<item_<begin_t>, int>>, "");
            static_assert(v_<equal_to_<distance_<begin_t, end_t>, long_<3>>>, "");
            static_assert(v_<equal_to_<distance_<begin_t, next2_t>, long_<2>>>, "");
            static_assert(v_<equal_to_<distance_<begin_t, next1_t>, long_<1>>>, "");
            static_assert(v_<equal_to_<distance_<begin_t, begin_t>, long_<0>>>, "");
            static_assert(v_<equal_to_<distance_<end_t, end_t>, long_<0>>>, "");
        }


        /// Determines if begin_t
        /// and current_t are
        /// separated by nb_steps_t
        template < typename begin_t,
                 typename nb_steps_t >
        struct is_same_distance_r_
        {
            template<typename current_t>
            using return_ =
                less_equal_ <
                distance_<begin_t, current_t>,
                nb_steps_t
                >;
        };


        template < typename begin_t,
                 typename nb_steps_t >
        using advance_ =
            navigate_next_ <
            begin_t,
            next_<last_valid_<begin_t>>,
            idem_,
            nil,
            function_class_<idem_>,
            is_same_distance_r_<begin_t, nb_steps_t >,
            default_accumulator_ >;


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
                using type = forward_iterator <
                             index_t,
                             item_<begin_t>,
                             clone_forward_<next_<begin_t>, end_t, meta::inc_<index_t> >>;
            };

            template < typename end_t,
                     typename index_t >
            struct clone_forward_<end_t, end_t, index_t, true_>
            {
                using type = forward_iterator_end;
            };


            template < typename begin_t,
                     typename end_t,
                     typename index_t >
            struct clone_forward_<begin_t, end_t, index_t, false_>
            {
                using type = forward_iterator_end;
            };
        }


        template < typename begin_t,
                 typename end_t >
        using clone_forward_ =
            type_<impl::clone_forward_<begin_t, end_t, begin_iterator_index>>;


        namespace lazy
        {
            /// Lazy signature
            /// of clone_forward_
            template < typename begin_t,
                     typename end_t >
            struct clone_forward_ :
                function_<meta::clone_forward_, begin_t, end_t>{};
        }


        namespace test_clone_forward
        {
            using begin_t = forward_iterator_builder_<pack<int, short, double, float>>;
            using a_range = clone_forward_<next_<begin_t>, next_<last_valid_<begin_t>>>;

            static_assert(v_<is_same_<item_<a_range>, short>>, "");
            static_assert(v_<is_same_<item_<last_valid_<a_range>>, float>>, "");

            static_assert(v_<is_same_<index_<a_range>, long_<0>>>, "");
            static_assert(v_<is_same_<index_<next_<a_range>>, long_<1>>>, "");

            static_assert(v_<is_same_<index_<next_<next_<a_range>>>, long_<2>>>, "");
            static_assert(v_<is_same_<index_<next_<next_<next_<a_range>>>>, end_iterator_index>>, "");
        }

        namespace impl
        {
            template < typename begin_t,
                     typename end_t,
                     typename prev_t,
                     typename index_t,
                     typename can_continue_t = meta::is_valid_direction_<next_, begin_t >>
            struct clone_bidirectional_;


            template < typename begin_t,
                     typename end_t,
                     typename prev_t >
            struct clone_bidirectional_<begin_t, end_t, prev_t, begin_iterator_index, true_>
            {
                using type =
                    bidirectional_iterator_begin <
                    item_<begin_t>,
                    clone_bidirectional_ <
                    next_<begin_t>,
                    end_t,
                    clone_bidirectional_,
                    meta::inc_<begin_iterator_index >>>;
            };


            template < typename begin_t,
                     typename end_t,
                     typename prev_t,
                     typename index_t >
            struct clone_bidirectional_<begin_t, end_t, prev_t, index_t, true_>
            {
                using type =
                    bidirectional_iterator <
                    index_t,
                    item_<begin_t>,
                    clone_bidirectional_ <
                    next_<begin_t>,
                    end_t,
                    clone_bidirectional_,
                    meta::inc_<index_t> > ,
                    prev_t >;
            };


            template < typename end_t,
                     typename prev_t,
                     typename index_t >
            struct clone_bidirectional_<end_t, end_t, prev_t, index_t, true_>
            {
                using type =
                    bidirectional_iterator_end<prev_t>;
            };


            template < typename end_t,
                     typename prev_t,
                     typename index_t >
            struct clone_bidirectional_<end_t, end_t, prev_t, index_t, false_>
            {
                using type =
                    bidirectional_iterator_end<prev_t>;
            };
        }


        template < typename begin_t,
                 typename end_t >
        using clone_bidirectional_ =
            type_<impl::clone_bidirectional_<begin_t, end_t, nil, begin_iterator_index>>;


        namespace lazy
        {
            /// Lazy signature
            /// of clone_bidirectional_
            template < typename begin_t,
                     typename end_t >
            struct clone_bidirectional_ :
                function_<meta::clone_bidirectional_, begin_t, end_t>{};
        }


        namespace test_clone_bidirectional
        {
            using begin_t = bidirectional_iterator_builder_<pack<int, short, double, float>>;
            using a_range = clone_bidirectional_<next_<begin_t>, next_<last_valid_<begin_t>>>;

            static_assert(v_<is_same_<item_<a_range>, short>>, "");
            static_assert(v_<is_same_<item_<last_valid_<a_range>>, float>>, "");

            static_assert(v_<is_same_<item_<prev_<next_<a_range>>>, short>>, "");
            static_assert(v_<is_same_<item_<prev_<next_<last_valid_<a_range>>>>, float>>, "");

            static_assert(v_<is_same_<index_<a_range>, long_<0>>>, "");
            static_assert(v_<is_same_<index_<next_<a_range>>, long_<1>>>, "");

            static_assert(v_<is_same_<index_<next_<next_<a_range>>>, long_<2>>>, "");
            static_assert(v_<is_same_<index_<next_<next_<next_<a_range>>>>, end_iterator_index>>, "");
        }
    }
}

#endif
