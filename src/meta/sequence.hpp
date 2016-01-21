#ifndef __BRAIN_META_SEQUENCE_HPP__
# define __BRAIN_META_SEQUENCE_HPP__


#include "iterator.hpp"

namespace brain
{
    namespace meta
    {
        /// ////////////////////// ///
        /// Sequence over iterator ///
        /// ////////////////////// ///
        ///
        /// A sequence is a pack of
        /// types that has been populated
        /// by an iterator builder.
        /// It contains the begin and
        /// the end member that
        /// respectively point to
        /// the first and the last
        /// elements of the sequence.
        ///

        /// Basic sequence that
        /// is built given an
        /// iterator type and
        /// a pack items_t ...
        template < template<typename> typename iterator_builder_t,
                 typename ... items_t >
        struct sequence
        {
            /// First iterator of
            /// the sequence
            using begin =
                iterator_builder_t<pack<items_t...>>;

            /// Last iterator of
            /// the sequence
            using end =
                next_<last_valid_<begin>>;

            /// Size of the
            /// pack items_t...
            using size =
                sizeof_pack_<items_t...>;


            /// Type of the iterator
            template<typename ... args_t>
            using iterator =
                iterator_builder_t<pack<args_t...>>;
        };


        /// Specialization of
        /// the basic sequence
        /// with the bidirectionnal
        /// iterator
        template<typename ... items_t>
        struct list :
            public sequence<bidirectional_iterator_builder_, items_t...>
        { };


        /// Specialization of
        /// the basic sequence
        /// with the bidirectionnal
        /// iterator
        template<typename ... items_t>
        struct forward_list :
            public sequence<forward_iterator_builder_, items_t...>
        { };


        /// Accessor to
        /// begin member
        member_(begin)


        /// Accessor to
        /// end member
        member_(end)


        /// Accessor to
        /// iterator type
        /// member
        template < typename sequence_t,
                 typename ... args_t >
        using iterator_ =
            typename sequence_t::
            template iterator<args_t...>;


        /// Determines if the
        /// sequence_t is empty
        /// or not
        template<typename sequence_t>
        using empty_ =
            equal_to_ <
            size_<sequence_t>,
            unsigned_<0> >;


        /// Unitary test of
        /// empty_
        namespace test_empty
        {
            using seq_t = forward_list<>;
            static_assert(v_<empty_<seq_t>>, "");
            static_assert(!v_<empty_<forward_list<int>>>, "");
        }


        /// Returns the first
        /// item of sequence_t
        template<typename sequence_t>
        using front_ =
            item_<begin_<sequence_t>>;


        /// Returns the last
        /// item of sequence_t
        template<typename sequence_t>
        using back_ =
            item_<last_valid_<begin_<sequence_t>>>;


        /// Unitary test of
        /// front_ and back_
        namespace test_front_back
        {
            using seq_t = forward_list<int, short>;

            static_assert(v_<is_same_<int, front_<seq_t>>>, "");
            static_assert(v_<is_same_<short, back_<seq_t>>>, "");
            static_assert(v_<is_same_<nil, back_<clear_<seq_t>>>>, "");
            static_assert(v_<is_same_<nil, front_<clear_<seq_t>>>>, "");
        }


        /// Reverses the
        /// sequence_t
        template<typename sequence_t>
        using reverse_ =
            navigate_next_ <
            begin_<sequence_t>,
            end_<sequence_t>,
            idem_,
            clear_<sequence_t>,
            function_class_<item_>,
            default_test_<end_<sequence_t>>,
            function_class_<push_front_> >;


        namespace lazy
        {
            /// Lazy signature
            /// of reverse_
            template<typename sequence_t>
            struct reverse_ :
                function_<meta::reverse_, sequence_t>{};
        }


        /// Unitary test of
        /// reverse_
        namespace test_reverse
        {
            using seq_t = forward_list<int, short>;
            static_assert(v_<std::is_same<forward_list<short, int>, reverse_<seq_t>>>, "");
            static_assert(v_<std::is_same<forward_list<>, reverse_<clear_<seq_t>>>>, "");
        }


        /// Pops the first
        /// item of sequence_t
        template<typename sequence_t>
        using pop_front_ =
            navigate_next_ <
            next_<begin_<sequence_t>>,
            end_<sequence_t>,
            idem_,
            clear_<sequence_t>,
            function_class_<item_>,
            default_test_<end_<sequence_t>>,
            function_class_<push_back_> >;


        /// Pops the last
        /// item of sequence_t
        template<typename sequence_t>
        using pop_back_ =
            reverse_<pop_front_<reverse_<sequence_t>>>;


        namespace lazy
        {
            /// Lazy signature
            /// of pop_front_
            template<typename sequence_t>
            struct pop_front_ :
                function_<meta::pop_front_, sequence_t>{};


            /// Lazy signature
            /// of pop_back_
            template<typename sequence_t>
            struct pop_back_ :
                function_<meta::pop_back_, sequence_t>{};
        }


        /// Unitary test of
        /// pop_front_ and
        /// pop_back_
        namespace test_pop_back
        {
            using seq_t = forward_list<int, short>;

            static_assert(v_<is_same_<forward_list<>, pop_back_<forward_list<>>>>, "");
            static_assert(v_<is_same_<forward_list<>, pop_front_<forward_list<>>>>, "");
            static_assert(v_<is_same_<forward_list<short>, pop_front_<seq_t>>>, "");
            static_assert(v_<is_same_<forward_list<int>, pop_back_<seq_t>>>, "");
        }


        /// Returns the iterator
        /// at the index_t from
        /// the sequence_t
        template < typename sequence_t,
                 typename index_t >
        using at_ =
            advance_<begin_<sequence_t>, index_t>;


        namespace lazy
        {
            /// Lazy signature
            /// of at_
            template < typename sequence_t,
                     typename index_t >
            struct at_ :
                function_<meta::at_, sequence_t, index_t>{};
        }


        /// Unitary test of
        /// at_
        namespace test_at
        {
            using seq_t = forward_list<int, short>;
            using begin_t = begin_<seq_t>;
            using next1_t = next_<begin_t>;
            using end_t = next_<next1_t>;

            static_assert(v_<is_same_<begin_t, at_<seq_t, long_<0>>>>, "");
            static_assert(v_<is_same_<next1_t, at_<seq_t, long_<1>>>>, "");
            static_assert(v_<is_same_<end_t, at_<seq_t, long_<2>>>>, "");
            static_assert(v_<is_same_<end_t, at_<seq_t, long_<3>>>>, "");
            static_assert(v_<is_same_<end_t, at_<seq_t, long_<4>>>>, "");
        }
    }
}

#endif
