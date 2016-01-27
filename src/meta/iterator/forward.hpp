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


        }
    }
}
#endif
