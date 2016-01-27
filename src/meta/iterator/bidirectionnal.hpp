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
        }
    }
}

#endif