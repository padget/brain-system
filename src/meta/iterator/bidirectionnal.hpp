#ifndef __BRAIN_META_ITERATOR_BIDIRECTIONNAL_HPP__
# define  __BRAIN_META_ITERATOR_BIDIRECTIONNAL_HPP__

# include "../core.hpp"
# include "forward.hpp"

namespace brain
{
    namespace meta
    {
        namespace iter
        {

            member_(prev)


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


            template<typename iterator_t>
            using has_prev_ =
                not_<is_same_<iterator_t, prev_<iterator_t>>>;




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
                /// Prev specialization
                template <typename iterator_t>
                struct is_valid_direction_<prev_, iterator_t>
                {
                    using type =
                        has_prev_<iterator_t>;
                };
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


            namespace test_first_valid
            {
                using begin_t = bidirectional_iterator_builder_<pack<int, double, short>>;
                using next1_t = next_<begin_t>; /// double
                using next2_t = next_<next1_t>; /// short

                static_assert(v_<is_same_<begin_t, first_valid_<next2_t>>>, "");
            }


            namespace impl
            {
                template < typename begin_t,
                         typename end_t,
                         typename prev_t,
                         typename index_t,
                         typename can_continue_t = iter::is_valid_direction_<next_, begin_t >>
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
}

#endif
