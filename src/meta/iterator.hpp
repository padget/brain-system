#ifndef __BRAIN_META_ITERATOR_HPP__
# define __BRAIN_META_ITERATOR_HPP__

#include "core.hpp"

namespace brain
{
    namespace meta
    {
        /// Determines if
        /// type_t has item
        /// member or not
        template < typename type_t,
                 typename = void >
        struct has_item_member_t_:
                std::false_type
        {
        };


        /// Specialization for
        /// has_item_t_ that
        /// returns true_type
        /// because of presence
        /// of item member
        template<typename type_t>
        struct has_item_member_t_<type_t, void_t<typename type_t::item>> :
                        std::true_type
        {
        };


        /// t_ shortcut for
        /// has_item_t_
        template<typename type_t>
        using has_item_member_t =
            lazy_t<has_item_member_t_, type_t>;


        /// Determines if
        /// type_t has next
        /// member or not
        template < typename type_t,
                 typename = void >
        struct has_next_member_t_:
                std::false_type
        {
        };


        /// Specialization for
        /// has_item_t_ that
        /// returns true_type
        /// because of presence
        /// of next member
        template<typename type_t>
        struct has_next_member_t_<type_t, void_t<typename type_t::next>> :
                        std::true_type
        {
        };


        /// t_ shortcut for
        /// has_next_t_
        template<typename type_t>
        using has_next_member_t =
            lazy_t<has_next_member_t_, type_t>;


        /// Determines if
        /// type_t has prev
        /// member or not
        template < typename type_t,
                 typename = void >
        struct has_prev_member_t_:
                std::false_type
        {
        };


        /// Specialization for
        /// has_item_t_ that
        /// returns true_type
        /// because of presence
        /// of prev member
        template<typename type_t>
        struct has_prev_member_t_<type_t, void_t<typename type_t::prev>> :
                        std::true_type
        {
        };


        /// t_ shortcut for
        /// has_prev_t_
        template<typename type_t>
        using has_prev_member_t =
            lazy_t<has_prev_member_t_, type_t>;


        /// Determines if
        /// type_t has index
        /// member or not
        template < typename type_t,
                 typename = void >
        struct has_index_member_t_:
                std::false_type
        {
        };


        /// Specialization for
        /// has_item_t_ that
        /// returns true_type
        /// because of presence
        /// of index member
        template<typename type_t>
        struct has_index_member_t_ <
                type_t,
                void_t<typename type_t::index> > :
                std::true_type
        {
        };


        /// t_ shortcut for
        /// has_index_t_
        template<typename type_t>
        using has_index_member_t =
            lazy_t<has_index_member_t_, type_t>;


        /// Determines if type_t
        /// is a forward iterator
        template<typename type_t>
        using is_forward_iterator_t =
            and_t <
            has_item_member_t<type_t>,
            has_next_member_t<type_t>,
            has_index_member_t<type_t >>;


        /// Determines if type_t
        /// is a backward iterator
        template<typename type_t>
        using is_backward_iterator_t =
            and_t <
            has_item_member_t<type_t>,
            has_prev_member_t<type_t>,
            has_index_member_t<type_t >>;


        /// Determines if type_t
        /// is a bidirectionnal
        /// iterator
        template<typename type_t>
        using is_bidirectional_iterator_t =
            and_t <
            is_forward_iterator_t<type_t>,
            is_backward_iterator_t<type_t >>;


        /// Accessor for
        /// next member
        template<typename iterator_t>
        using next_ =
            typename iterator_t::next;


        /// Accessor for
        /// prev member
        template<typename iterator_t>
        using prev_ =
            typename iterator_t::prev;


        /// Accessor for
        /// index member
        template<typename iterator_t>
        using index_ =
            typename iterator_t::index;


        /// Accessor for
        /// item member
        template<typename iterator_t>
        using item_ =
            typename iterator_t::item;


        /// //////////////// ///
        /// Forward Iterator ///
        /// //////////////// ///


        using begin_iterator_index_t = long_t <0>;
        using end_iterator_index_t = long_t < -1 >;


        template < typename index_t,
                 typename item_t,
                 typename next_t >
        struct forward_iterator
        {
            using index = index_t;
            using item = item_t;
            using next = next_t;


        };


        struct forward_iterator_end
        {
            using index = end_iterator_index_t;
            using item = nil;
            using next = forward_iterator_end;
        };


        template < typename pack_t,
                 typename index_t = begin_iterator_index_t >
        struct forward_iterator_builder_t_;

        template < typename item_t,
                 typename ... items_t,
                 typename index_t >
        struct forward_iterator_builder_t_<pack<item_t, items_t...>, index_t>
        {
            using type =
                forward_iterator < index_t, item_t,
                lazy_t<forward_iterator_builder_t_, pack<items_t...>, inc_t<index_t>> >;
        };

        template<typename index_t>
        struct forward_iterator_builder_t_<pack<>, index_t>
        {
            using type = forward_iterator_end;
        };

        template<typename pack_t>
        using forward_iterator_builder_t =
            lazy_t<forward_iterator_builder_t_, pack_t>;


        namespace test_forward_iterator
        {
            using begin_t = forward_iterator_builder_t<pack<int, double, float>>;

            using next1_t = next_<begin_t>;
            using next2_t = next_<next1_t>;
            using end_t = next_<next2_t>;

            static_assert(v_<std::is_same<item_<begin_t>, int>>, "");
            static_assert(v_<std::is_same<item_<next1_t>, double>>, "");
            static_assert(v_<std::is_same<item_<next2_t>, float>>, "");
            static_assert(v_<std::is_same<item_<end_t>, nil>>, "");

            static_assert(v_<equal_to_t<index_<begin_t>, begin_iterator_index_t>>, "");
            static_assert(v_<equal_to_t<index_<next1_t>, unsigned_t<1>>>, "");
            static_assert(v_<equal_to_t<index_<next2_t>, unsigned_t<2>>>, "");
            static_assert(v_<equal_to_t<index_<end_t>, end_iterator_index_t>>, "");
        }



        /// ////////////////////// ///
        /// Bidirectional Iterator ///
        /// ////////////////////// ///

        template < typename index_t,
                 typename item_t,
                 typename next_t,
                 typename prev_builder_t >
        struct bidirectional_iterator:
                forward_iterator<index_t, item_t, next_t>
        {
            using prev = t_<prev_builder_t>;
        };


        template < typename item_t,
                 typename next_t >
        struct bidirectional_iterator_begin:
                forward_iterator<begin_iterator_index_t, item_t, next_t>
        {
            using prev = bidirectional_iterator_begin;
        };


        template<typename prev_builder_t>
        struct bidirectional_iterator_end
        {
            using index = end_iterator_index_t;
            using item = nil;
            using next = bidirectional_iterator_end;
            using prev = t_<prev_builder_t>;
        };


        template < typename pack_t,
                 typename prev_builder_t = void,
                 typename index_t = begin_iterator_index_t >
        struct bidirectional_iterator_builder_t_;


        template < typename item_t,
                 typename ... items_t,
                 typename prev_builder_t >
        struct bidirectional_iterator_builder_t_<pack<item_t, items_t...>, prev_builder_t, begin_iterator_index_t>
        {
            using type = bidirectional_iterator_begin <
                         item_t,
                         lazy_t <bidirectional_iterator_builder_t_, pack<items_t...>, bidirectional_iterator_builder_t_, inc_t<begin_iterator_index_t> >>;
        };


        template < typename item_t,
                 typename ... items_t,
                 typename prev_builder_t,
                 typename index_t >
        struct bidirectional_iterator_builder_t_<pack<item_t, items_t...>, prev_builder_t, index_t>
        {
            using type = bidirectional_iterator <
                         index_t,
                         item_t,
                         lazy_t<bidirectional_iterator_builder_t_, pack<items_t...>, bidirectional_iterator_builder_t_, inc_t<index_t>>,
                         prev_builder_t >;
        };


        template < typename prev_builder_t,
                 typename index_t >
        struct bidirectional_iterator_builder_t_<pack<>, prev_builder_t, index_t>
        {
            using type = bidirectional_iterator_end<prev_builder_t>;
        };

        template<typename pack_t>
        using bidirectional_iterator_builder_t =
            lazy_t<bidirectional_iterator_builder_t_, pack_t>;



        namespace test_bidirectionnal_iterator
        {
            using begin_t = bidirectional_iterator_builder_t<pack<int, double, float>>;
            using next1_t = next_<begin_t>;
            using next2_t = next_<next1_t>;
            using end_t = next_<next2_t>;

            using prev2_t = prev_<end_t>;
            using prev1_t = prev_<prev2_t>;
            using prev0_t = prev_<prev1_t>;

            static_assert(v_<std::is_same<item_<begin_t>, int>>, "");
            static_assert(v_<std::is_same<item_<next1_t>, double>>, "");
            static_assert(v_<std::is_same<item_<next2_t>, float>>, "");
            static_assert(v_<std::is_same<item_<end_t>, nil>>, "");

            static_assert(v_<std::is_same<item_<prev2_t>, float>>, "");
            static_assert(v_<std::is_same<item_<prev1_t>, double>>, "");
            static_assert(v_<std::is_same<item_<prev0_t>, int>>, "");

            static_assert(v_<equal_to_t<index_<begin_t>, begin_iterator_index_t>>, "");
            static_assert(v_<equal_to_t<index_<next1_t>, unsigned_t<1>>>, "");
            static_assert(v_<equal_to_t<index_<next2_t>, unsigned_t<2>>>, "");
            static_assert(v_<equal_to_t<index_<end_t>, end_iterator_index_t>>, "");

            static_assert(v_<equal_to_t<index_<prev2_t>, unsigned_t<2>>>, "");
            static_assert(v_<equal_to_t<index_<prev1_t>, unsigned_t<1>>>, "");
            static_assert(v_<equal_to_t<index_<prev0_t>, begin_iterator_index_t>>, "");
        }


        /// //////////////////// ///
        /// Test of end iterator ///
        /// //////////////////// ///



        template<typename iterator_t>
        using has_next_t =
            not_t<std::is_same<iterator_t, next_<iterator_t>>>;



        namespace test_has_next
        {
            using begin_t = forward_iterator_builder_t<pack<int, int, int>>;
            using next1_t = next_<begin_t>;
            using next2_t = next_<next1_t>;
            using end_t = next_<next2_t>;
            using end2_t = next_<end_t>;

            static_assert(v_<has_next_t<begin_t>>, "");
            static_assert(v_<has_next_t<next1_t>>, "");
            static_assert(v_<has_next_t<next2_t>>, "");
            static_assert(v_<not_t<has_next_t<end_t>>>, "");
            static_assert(v_<not_t<has_next_t<end2_t>>>, "");
        }


        template<typename iterator_t>
        using has_prev_t =
            not_t<std::is_same<iterator_t, prev_<iterator_t>>>;


        namespace test_has_prev
        {
            using begin_t = bidirectional_iterator_builder_t<pack<int, int, int>>;

            using next1_t = next_<begin_t>;
            using next2_t = next_<next1_t>;
            using end_t = next_<next2_t>;
            using end2_t = next_<end_t>;

            using prev2_t = prev_<end2_t>;
            using prev1_t = prev_<prev2_t>;
            using prev0_t = prev_<prev1_t>;

            static_assert(v_<has_next_t<begin_t>>, "");
            static_assert(v_<has_next_t<next1_t>>, "");
            static_assert(v_<has_next_t<next2_t>>, "");
            static_assert(v_<not_t<has_next_t<end_t>>>, "");
            static_assert(v_<not_t<has_next_t<end2_t>>>, "");

            static_assert(v_<has_prev_t<end2_t>>, "");
            static_assert(v_<has_prev_t<prev2_t>>, "");
            static_assert(v_<has_prev_t<prev1_t>>, "");
            static_assert(v_<not_t<has_prev_t<prev0_t>>>, "");
        }


        template < template<typename> typename direction_,
                 typename iterator_t >
        struct is_valid_direction_t;


        template <typename iterator_t>
        struct is_valid_direction_t<next_, iterator_t>:
                has_next_t<iterator_t>
        {
            static_assert(
                v_<is_forward_iterator_t<iterator_t>>,
                "is_valid_direction_t : iterator_t must be forwardable");
        };

        template <typename iterator_t>
        struct is_valid_direction_t<prev_, iterator_t>:
                has_prev_t<iterator_t>
        {
            static_assert(
                v_<is_backward_iterator_t<iterator_t>>,
                "is_valid_direction_t : iterator_t must be backwardable");
        };


        ///
        template < typename iterator_t,
                 typename is_next_valid_t =
                 has_next_t<next_<iterator_t> >>
        struct last_valid_t_;


        /// Returns the last
        /// iterator before the end
        /// iterator
        template <typename iterator_t>
        struct last_valid_t_ <
                iterator_t,
                std::true_type >
        {
            using type =
                lazy_t < last_valid_t_,
                next_<iterator_t >> ;
        };


        template<typename iterator_t>
        struct last_valid_t_ <
                iterator_t,
                std::false_type >
        {
            using type =
                iterator_t;
        };


        /// t_ shortcut for
        /// last_valid_t_
        template<typename iterator_t>
        using last_t =
            lazy_t<last_valid_t_, iterator_t>;


        namespace test_last_valid
        {
            using begin_t = forward_iterator_builder_t<pack<int, double, short>>;
            using next1_t = next_<begin_t>; /// double
            using next2_t = next_<next1_t>; /// short

            static_assert(v_<std::is_same<next2_t, last_t<begin_t>>>, "");
        }
        
        
        /// ////////////// ///
        /// Iteration Ways ///
        /// ////////////// ///


        

        


        /// ////////////////// ///
        /// Navigate iteration ///
        /// ////////////////// ///


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
                 typename func_r >
        struct navigate_t_
        {
            template < typename current_t,
                     typename tmp_t >
            struct navigate_t_impl_
            {
                using type =
                    lazy_t < navigate_t_impl_,
                    direction_<current_t>,
                    r_<func_r, tmp_t, accessor_<current_t> >>;
            };


            template <typename tmp_t>
            struct navigate_t_impl_<end_t, tmp_t>
            {
                using type =
                    tmp_t;
            };


            using type =
                lazy_t<navigate_t_impl_, begin_t, init_t>;
        };


        /// t_ shortcut for
        /// navigate_t_
        template < typename begin_t,
                 typename end_t,
                 template<typename>  typename direction_,
                 template<typename>  typename accessor_,
                 typename init_t,
                 typename func_r >
        using navigate_t =
            t_<navigate_t_<begin_t, end_t, direction_, accessor_, init_t, func_r>>;


        /// Specialization of
        /// navigate_t for the
        /// next_ direction
        template < typename begin_t,
                 typename end_t,
                 typename init_t,
                 typename func_r >
        using forward_item_t =
            navigate_t<begin_t, end_t, next_, item_, init_t, func_r>;


        /// Specialization of
        /// navigate_t for the
        /// prev_ direction
        template < typename begin_t,
                 typename end_t,
                 typename init_t,
                 typename func_r >
        using backward_item_t =
            navigate_t<begin_t, end_t, prev_, item_, init_t, func_r>;


        /// Specialization of
        /// navigate_t for the
        /// next_ direction
        template < typename begin_t,
                 typename end_t,
                 typename init_t,
                 typename func_r >
        using forward_iter_t =
            navigate_t<begin_t, end_t, next_, idem_, init_t, func_r>;


        /// Specialization of
        /// navigate_t for the
        /// prev_ direction
        template < typename begin_t,
                 typename end_t,
                 typename init_t,
                 typename func_r >
        using backward_iter_t =
            navigate_t<begin_t, end_t, prev_, idem_, init_t, func_r>;
            
            
        /// /////////////// ///
        /// While Iteration ///
        /// /////////////// ///

        /*template < typename begin_t,
                 typename end_t,
                 template<typename> typename direction_,
                 typename test_r >
        using while_t_ = navigate_t<begin_t, end_t, direction_, idem_, end_t, as_r_<if_t<test_r>>*/

        /// TOCHANGE While iteration is equivalent with an filter on the current
        /// sequence filtered by the test_r and where we retrieve the first element

        /// Returns the first
        /// that match true with
        /// the test_r or if the
        /// next step is invalid
        /// or if the end_t of the
        /// sequence is reached
        template < typename begin_t,
                 typename end_t,
                 template<typename> typename direction_,
                 typename test_r >
        struct while_t_ /// TOCHANGE <=> navigate_t jusquaceque
        {
            template < typename current_t,
                     typename must_stop_t =
                     or_t <
                     r_<test_r, current_t>,
                     std::is_same<end_t, current_t>,
                     not_t<is_valid_direction_t<direction_, current_t> >> >
            struct while_t_impl_;


            template <typename current_t>
            struct while_t_impl_ <
                    current_t,
                    std::false_type > :
                    while_t_impl_<direction_<current_t>>
            {
            };


            template <typename current_t>
            struct while_t_impl_ <
                    current_t,
                    std::true_type >
            {
                using type =
                    current_t ;
            };



            using type =
                lazy_t<while_t_impl_, begin_t>;
        };


        template < typename begin_t,
                 typename end_t,
                 template<typename> typename direction_,
                 typename test_r >
        using while_t =
            t_<while_t_<begin_t, end_t, direction_, test_r>>;


        template < typename begin_t,
                 typename end_t,
                 typename test_r >
        using while_forward_t =
            while_t<begin_t, end_t, next_, test_r>;


        template < typename begin_t,
                 typename end_t,
                 typename test_r >
        using while_backward_t =
            while_t<begin_t, end_t, prev_, test_r>;


        /// Computes the
        /// distance between
        /// two iterators
        template < typename begin_t,
                 typename end_t >
        struct distance_t_
        {
            using type =
                minus_t <
                index_<end_t>,
                index_<begin_t> >;
        };


        /// Specialization for
        /// end iterator that
        /// returns the distance
        /// between the begin_t
        /// and prev_<end_t>
        template <typename begin_t>
        struct distance_t_<begin_t, next_<last_t<begin_t>>>
        {
            using type =
                inc_t < minus_t <
                index_<last_t<begin_t>> ,
                index_<begin_t> >>;
        };


        /// t_ shortcut for
        /// distance_t_
        template < typename begin_t,
                 typename end_t >
        using distance_t =
            lazy_t<distance_t_, begin_t, end_t>;

        namespace test_distance
        {
            using begin_t = forward_iterator_builder_t<pack<int, double, short>>;
            using next1_t = next_<begin_t>; /// double
            using next2_t = next_<next1_t>; /// short
            using end_t = next_<next2_t>; /// nil

            static_assert(v_<equal_to_t<distance_t<begin_t, end_t>, long_t<3>>>, "");
            static_assert(v_<equal_to_t<distance_t<begin_t, next2_t>, long_t<2>>>, "");
            static_assert(v_<equal_to_t<distance_t<begin_t, next1_t>, long_t<1>>>, "");
            static_assert(v_<equal_to_t<distance_t<begin_t, begin_t>, long_t<0>>>, "");
        }




        template < typename begin_t,
                 typename nb_steps_t >
        struct is_same_distance_r_
        {
            template<typename current_t>
            using return_ =
                equal_to_t <
                nb_steps_t,
                distance_t<begin_t, current_t >>;
        };


        template < typename begin_t,
                 typename nb_steps_t >
        using advance_t =
            while_forward_t <
            begin_t,
            next_<last_t<begin_t>>,
            is_same_distance_r_<begin_t, nb_steps_t >>;

        namespace test_advance
        {
            using begin_t = forward_iterator_builder_t<pack<int, double, short>>;
            using next1_t = next_<begin_t>; /// double
            using next2_t = next_<next1_t>; /// short
            using end_t = next_<next2_t>; /// nil

            static_assert(v_<std::is_same<begin_t, advance_t<begin_t, long_t<0>>>>, "");
            static_assert(v_<std::is_same<next1_t, advance_t<next1_t, long_t<0>>>>, "");
            static_assert(v_<std::is_same<next2_t, advance_t<next2_t, long_t<0>>>>, "");
            static_assert(v_<std::is_same<end_t, advance_t<end_t, long_t<0>>>>, "");

            static_assert(v_<std::is_same<next1_t, advance_t<begin_t, long_t<1>>>>, "");
            static_assert(v_<std::is_same<next2_t, advance_t<begin_t, long_t<2>>>>, "");
            static_assert(v_<std::is_same<end_t, advance_t<begin_t, long_t<3>>>>, "");

            static_assert(v_<std::is_same<end_t, advance_t<next1_t, long_t<2>>>>, "");
        }


        template < typename begin_t,
                 typename end_t,
                 typename index_t,
                 typename can_continue_t = has_next_t<begin_t >>
        struct clone_forward_t_;

        template < typename begin_t,
                 typename end_t,
                 typename index_t >
        struct clone_forward_t_<begin_t, end_t, index_t, std::true_type>
        {
            using type = forward_iterator <
                         index_t,
                         item_<begin_t>,
                         t_<clone_forward_t_<next_<begin_t>, end_t, inc_t<index_t>>> >;
        };

        template < typename end_t,
                 typename index_t >
        struct clone_forward_t_<end_t, end_t, index_t, std::true_type>
        {
            using type = forward_iterator_end;
        };


        template < typename begin_t,
                 typename end_t,
                 typename index_t >
        struct clone_forward_t_<begin_t, end_t, index_t, std::false_type>
        {
            using type = forward_iterator_end;
        };


        template < typename begin_t,
                 typename end_t >
        using clone_forward_t =
            lazy_t<clone_forward_t_, begin_t, end_t, begin_iterator_index_t>;

        namespace test_clone_forward
        {
            using begin_t = forward_iterator_builder_t<pack<int, short, double, float>>;
            using a_range = clone_forward_t<next_<begin_t>, next_<last_t<begin_t>>>;

            static_assert(v_<std::is_same<item_<a_range>, short>>, "");
            static_assert(v_<std::is_same<item_<last_t<a_range>>, float>>, "");

            static_assert(v_<std::is_same<index_<a_range>, long_t<0>>>, "");
            static_assert(v_<std::is_same<index_<next_<a_range>>, long_t<1>>>, "");

            static_assert(v_<std::is_same<index_<next_<next_<a_range>>>, long_t<2>>>, "");
            static_assert(v_<std::is_same<index_<next_<next_<next_<a_range>>>>, end_iterator_index_t>>, "");
        }


        /*
         *
                template < typename index_t,
                         typename item_t,
                         typename next_t,
                         typename prev_builder_t >
         *
         * */

        template < typename begin_t,
                 typename end_t,
                 typename prev_t,
                 typename index_t,
                 typename can_continue_t = has_next_t<begin_t >>
        struct clone_bidirectional_t_;


        template < typename begin_t,
                 typename end_t,
                 typename prev_t >
        struct clone_bidirectional_t_<begin_t, end_t, prev_t, begin_iterator_index_t, std::true_type>
        {
            using type = bidirectional_iterator_begin <
                         item_<begin_t>,
                         lazy_t < clone_bidirectional_t_,
                         next_<begin_t>,
                         end_t,
                         clone_bidirectional_t_,
                         inc_t<begin_iterator_index_t >>>;
        };


        template < typename begin_t,
                 typename end_t,
                 typename prev_t,
                 typename index_t >
        struct clone_bidirectional_t_<begin_t, end_t, prev_t, index_t, std::true_type>
        {
            using type = bidirectional_iterator <
                         index_t,
                         item_<begin_t>,
                         lazy_t < clone_bidirectional_t_,
                         next_<begin_t>,
                         end_t,
                         clone_bidirectional_t_,
                         inc_t<index_t> > ,
                         prev_t >;
        };


        template < typename end_t,
                 typename prev_t,
                 typename index_t >
        struct clone_bidirectional_t_<end_t, end_t, prev_t, index_t, std::true_type>
        {
            using type = bidirectional_iterator_end<prev_t>;
        };


        template < typename end_t,
                 typename prev_t,
                 typename index_t >
        struct clone_bidirectional_t_<end_t, end_t, prev_t, index_t, std::false_type>
        {
            using type = bidirectional_iterator_end<prev_t>;
        };


        template < typename begin_t,
                 typename end_t >
        using clone_bidirectional_t =
            lazy_t<clone_bidirectional_t_, begin_t, end_t, void, begin_iterator_index_t>;


        namespace test_clone_bidirectional
        {
            using begin_t = bidirectional_iterator_builder_t<pack<int, short, double, float>>;
            using a_range = clone_bidirectional_t<next_<begin_t>, next_<last_t<begin_t>>>;

            static_assert(v_<std::is_same<item_<a_range>, short>>, "");
            static_assert(v_<std::is_same<item_<last_t<a_range>>, float>>, "");
            
            static_assert(v_<std::is_same<item_<prev_<next_<a_range>>>, short>>, "");
            static_assert(v_<std::is_same<item_<prev_<next_<last_t<a_range>>>>, float>>, "");

            static_assert(v_<std::is_same<index_<a_range>, long_t<0>>>, "");
            static_assert(v_<std::is_same<index_<next_<a_range>>, long_t<1>>>, "");

            static_assert(v_<std::is_same<index_<next_<next_<a_range>>>, long_t<2>>>, "");
            static_assert(v_<std::is_same<index_<next_<next_<next_<a_range>>>>, end_iterator_index_t>>, "");
        }

    }
}

#endif
