#ifndef __BRAIN_META_SEQUENCE_HPP__
# define __BRAIN_META_SEQUENCE_HPP__


#include "iterator.hpp"

namespace brain
{
    namespace meta
    {

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
        template<typename sequence_t>
        using begin_ =
            typename sequence_t::begin;


        /// Accessor to
        /// end member
        template<typename sequence_t>
        using end_ =
            typename sequence_t::end;


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
        using empty_t =
            equal_to_ <
            size_<sequence_t>,
            unsigned_<0> >;

        namespace test_empty
        {
            using seq_t = forward_list<>;

            static_assert(v_<empty_t<seq_t>>, "");
        }


        /// Definition of
        /// clear_t_
        template<typename sequence_t>
        struct clear_t_;


        /// Returns an empty
        /// sequence of the
        /// same type of the
        /// sequence_t
        template < template<typename...> typename sequence_t,
                 typename ... items_t >
        struct clear_t_<sequence_t<items_t...>>
        {
            using type =
                sequence_t<>;
        };


        /// t_ shortcut for
        /// clear_t_
        template<typename sequence_t>
        using clear_t =
            lazy_t<clear_t_, sequence_t>;


        namespace test_clear
        {
            using seq_t = forward_list<int, short>;

            static_assert(v_<std::is_same<clear_t<seq_t>, forward_list<>>>, "");
        }


        /// Returns the first
        /// item of sequence_t
        template<typename sequence_t>
        using front_t =
            item_<begin_<sequence_t>>;

        namespace test_front
        {
            using seq_t = forward_list<int, short>;

            static_assert(v_<std::is_same<int, front_t<seq_t>>>, "");
        }

        /// Returns the last
        /// item of sequence_t
        template<typename sequence_t>
        using back_t =
            item_<last_t<begin_<sequence_t>>>;


        namespace test_back
        {
            using seq_t = forward_list<int, short>;

            static_assert(v_<std::is_same<short, back_t<seq_t>>>, "");
        }


        template < template<typename ...> typename sequence_t,
                 typename begin_t,
                 typename end_t >
        using sub_sequence_t =
            forward_item_t <
            begin_t,
            end_t ,
            sequence_t<>,
            as_r_<push_back_t> >;


        namespace test_sub_sequence
        {
            using seq_t = forward_list<int, short, double, unsigned>;

            static_assert(v_<std::is_same<forward_list<short, double, unsigned>, sub_sequence_t<forward_list, next_<begin_<seq_t>>, end_<seq_t>>>>, "");
        }


        /// Reverses the
        /// sequence_t
        template<typename sequence_t>
        using reverse_t =
            forward_item_t <
            begin_<sequence_t>,
            end_<sequence_t> ,
            clear_t<sequence_t>,
            as_r_<push_front_t> >;


        namespace test_reverse
        {
            using seq_t = forward_list<int, short>;

            static_assert(v_<std::is_same<forward_list<short, int>, reverse_t<seq_t>>>, "");
        }


        /// Pops the first
        /// item of sequence_t
        template<typename sequence_t>
        using pop_front_t =
            forward_item_t <
            next_<begin_<sequence_t>>,
            end_<sequence_t>,
            clear_t<sequence_t>,
            as_r_<push_back_t> >;


        namespace test_pop_front
        {
            using seq_t = forward_list<int, short>;

            static_assert(v_<std::is_same<forward_list<short>, pop_front_t<seq_t>>>, "");
        }


        /// Pops the last
        /// item of sequence_t
        template<typename sequence_t>
        using pop_back_t =
            reverse_t<pop_front_t<reverse_t<sequence_t>>>;


        namespace test_pop_back
        {
            using seq_t = forward_list<int, short>;

            static_assert(v_<std::is_same<forward_list<int>, pop_back_t<seq_t>>>, "");
        }



        template < typename sequence_t,
                 typename index_t >
        using at_t =
            advance_t<begin_<sequence_t>, index_t>;

        namespace test_at
        {
            using seq_t = forward_list<int, short>;
            using begin_t = begin_<seq_t>;
            using next1_t = next_<begin_t>;
            using end_t = next_<next1_t>;

            static_assert(v_<std::is_same<begin_t, at_t<seq_t, long_t<0>>>>, "");
            static_assert(v_<std::is_same<next1_t, at_t<seq_t, long_t<1>>>>, "");
            static_assert(v_<std::is_same<end_t, at_t<seq_t, long_t<2>>>>, "");
            static_assert(v_<std::is_same<end_t, at_t<seq_t, long_t<3>>>>, "");
            static_assert(v_<std::is_same<end_t, at_t<seq_t, long_t<4>>>>, "");
        }


        template<typename target_iterator_t>
        struct is_same_position_t
        {
            template<typename current_t>
            using return_ =
                std::is_same<target_iterator_t, current_t>;
        };
        
        
        
        
        /// TODO Introduire une version sequence de tous les algorithmes [begin_t, end_t)
    }
}

#endif
