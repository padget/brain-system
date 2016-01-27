#ifndef __BRAIN_META_ITERATOR_FORWARD_HPP__
# define  __BRAIN_META_ITERATOR_FORWARD_HPP__

#include "../core.hpp"

namespace brain
{
    namespace meta
    {
        namespace iter
        {
            member_(item)
            member_(next)
            member_(index)

            /// Determines if type_t
            /// is a forward iterator
            template<typename type_t>
            using is_forward_iterator_ =
                meta::and_ <
                has_item_member<type_t>,
                has_next_member<type_t>,
                has_index_member<type_t >>;


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


            template<typename iterator_t>
            using has_next_ =
                meta::not_<meta::is_same_<iterator_t, iter::next_<iterator_t>>>;

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
            }

            template < template<typename> typename direction_,
                     typename iterator_t >
            using is_valid_direction_ =
                type_<impl::is_valid_direction_<direction_, iterator_t>>;


            namespace test_is_valid_direction
            {
                using begin_t = forward_iterator_builder_<pack<int, float, double>>;
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


            namespace test_last_valid
            {
                using begin_t = forward_iterator_builder_<pack<int, double, short>>;
                using next1_t = next_<begin_t>; /// double
                using next2_t = next_<next1_t>; /// short

                static_assert(v_<is_same_<next2_t, last_valid_<begin_t>>>, "");
            }


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
                struct distance_<begin_t, next_<iter::last_valid_<begin_t>>>
                {
                    using type =
                        if_ < is_same_<begin_t, next_<iter::last_valid_<begin_t>>>,
                        unsigned_<0>,
                        inc_<minus_<index_<iter::last_valid_<begin_t>>, index_<begin_t>>> >;
                };
            }


            /// type_ shortcut for
            /// distance_t_
            template < typename begin_t,
                     typename end_t >
            using distance_ =
                type_<impl::distance_<begin_t, end_t>>;


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


            namespace impl
            {
                template < typename begin_t,
                         typename end_t,
                         typename index_t,
                         typename can_continue_t =
                         iter::is_valid_direction_<next_, begin_t >>
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
                        function_<iter::clone_forward_, begin_t, end_t> {};
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
        }
    }
}
#endif
