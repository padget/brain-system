#ifndef __BRAIN_META_UNITARY_HPP__
# define __BRAIN_META_UNITARY_HPP__

#include "core.hpp"
#include "iterator.hpp"

namespace meta
{
    /// Unitary Test
    /// of base.hpp
    namespace test_base
    {
        template<typename type_t>
        using idem_function =
            function_<idem_, type_t>;

        static_assert(v_<is_same_<type_<idem_function<int>>, int>>, "");
    }


    /// Unitary Test
    /// of math.hpp
    namespace test_math
    {
        using one = long_<1>;
        using two = long_<2>;
        using three = long_<3>;

        /// Effective test
        static_assert(v_<inc_<one>> == 2, "");
        static_assert(v_<dec_<one>> == 0, "");
        static_assert(v_<plus_<one, one>> == v_<two>, "");
        static_assert(v_<minus_<two, one>> == v_<one>, "");
        static_assert(v_<multiplies_<two, two>> == 4, "");
        static_assert(v_<divides_<two, two>> == v_<one>, "");
        static_assert(v_<modulus_<three, two>> == v_<one>, "");
        static_assert(v_<negate_<one>> == -1, "");

        /// Lazy test
        static_assert(v_<lazy::inc_<one>> == 2, "");
        static_assert(v_<lazy::dec_<one>> == 0, "");
        static_assert(v_<lazy::plus_<one, one>> == v_<two>, "");
        static_assert(v_<lazy::minus_<two, one>> == v_<one>, "");
        static_assert(v_<lazy::multiplies_<two, two>> == 4, "");
        static_assert(v_<lazy::divides_<two, two>> == v_<one>, "");
        static_assert(v_<lazy::modulus_<three, two>> == v_<one>, "");
        static_assert(v_<lazy::negate_<one>> == -1, "");
    }


    /// Unitary Test
    /// of logic.hpp
    namespace test_logic
    {
        using one = long_<1>;
        using two = long_<2>;
        using three = long_<3>;

        /// Effective test
        static_assert(v_<equal_to_<one, one>>, "");
        static_assert(v_<not_equal_to_<one, two>>, "");
        static_assert(v_<greater_<two, one>>, "");
        static_assert(v_<less_<one, two>>, "");
        static_assert(v_<greater_equal_<two, one>>, "");
        static_assert(v_<greater_equal_<one, one>>, "");
        static_assert(v_<less_equal_<one, two>>, "");
        static_assert(v_<less_equal_<one, one>>, "");
        static_assert(v_<and_<true_, true_>>, "");
        static_assert(!v_<and_<false_, true_>>, "");
        static_assert(v_<or_<true_, false_>>, "");
        static_assert(!v_<or_<false_, false_>>, "");
        static_assert(v_<not_<false_>>, "");

        /// Lazy test
        static_assert(v_<lazy::equal_to_<one, one>>, "");
        static_assert(v_<lazy::not_equal_to_<one, two>>, "");
        static_assert(v_<lazy::greater_<two, one>>, "");
        static_assert(v_<lazy::less_<one, two>>, "");
        static_assert(v_<lazy::greater_equal_<two, one>>, "");
        static_assert(v_<lazy::greater_equal_<one, one>>, "");
        static_assert(v_<lazy::less_equal_<one, two>>, "");
        static_assert(v_<lazy::less_equal_<one, one>>, "");
        static_assert(v_<lazy::and_<true_, true_>>, "");
        static_assert(!v_<lazy::and_<false_, true_>>, "");
        static_assert(v_<lazy::or_<true_, false_>>, "");
        static_assert(!v_<lazy::or_<false_, false_>>, "");
        static_assert(v_<lazy::not_<false_>>, "");
    }


    /// Unitary Test
    /// of select.hpp
    namespace test_select
    {
        /// Effective test
        static_assert(v_<is_same_<if_<true_, int, float>, int>>, "");
        static_assert(v_<is_same_<if_<false_, int, float>, float>>, "");
        static_assert(v_<is_same_<eval_if_<true_, lazy::idem_<int>, lazy::idem_<float>>, int>>, "");
        static_assert(v_<is_same_<eval_if_<false_, lazy::idem_<int>, lazy::idem_<float>>, float>>, "");

        /// Lazy test
        static_assert(v_<is_same_<type_<lazy::if_<true_, int, float>>, int>>, "");
        static_assert(v_<is_same_<type_<lazy::if_<false_, int, float>>, float>>, "");
        static_assert(v_<is_same_<type_<lazy::eval_if_<true_, lazy::idem_<int>, lazy::idem_<float>>>, int>>, "");
        static_assert(v_<is_same_<type_<lazy::eval_if_<false_, lazy::idem_<int>, lazy::idem_<float>>>, float>>, "");
    }


    /// Unitary test
    /// of pack.hpp
    namespace test_pack
    {
        using p = pack<int, short, double>;
        using a_list = pack<int, double>;
        using a_list2 = pack<float, short>;
        using a_list3 = pack<char>;
        using p_empty = pack<>;
        using seq_t = pack<int, short>;
        using p = pack<int, short, double>;

        /// Effective test
        static_assert(v_<equal_to_<size_<p>, size_t_<3>>>, "");
        static_assert(v_<equal_to_<size_<p_empty>, size_t_<0>>>, "");
        static_assert(v_<empty_<p_empty>>, "");

        static_assert(v_<is_same_<pack<int, double>, cat_<a_list>>>, "");
        static_assert(v_<is_same_<pack<int, double, float, short>, cat_<a_list, a_list2>>>, "");
        static_assert(v_<is_same_<pack<int, double, float, short, char>, cat_<a_list, a_list2, a_list3>>>, "");
        static_assert(v_<is_same_<pack<int, double>, cat_<a_list>>>, "");

        static_assert(v_<is_same_<pack<int, double>, cat_<a_list>>>, "");
        static_assert(v_<is_same_<pack<int, double, float, short>, cat_<a_list, a_list2>>>, "");
        static_assert(v_<is_same_<pack<int, double, float, short, char>, cat_<a_list, a_list2, a_list3>>>, "");
        static_assert(v_<is_same_<pack<int, double>, cat_<a_list>>>, "");

        static_assert(v_<is_same_<pack<int, short, double>, push_back_<seq_t, double>>>, "");
        static_assert(v_<is_same_<pack<double, int, short>, push_front_<seq_t, double>>>, "");

        static_assert(v_<is_same_<int, at_<p, unsigned_<0>>>>, "");
        static_assert(v_<is_same_<short, at_<p, unsigned_<1>>>>, "");
        static_assert(v_<is_same_<double, at_<p, unsigned_<2>>>>, "");
        static_assert(v_<is_same_<nil, at_<p, unsigned_<3>>>>, "");
        static_assert(v_ < is_same_ < nil, at_ < p, unsigned_ < -1 >>> > , "");

        static_assert(v_<is_same_<clear_<p>, pack<>>>, "");

        /// Lazy test
        static_assert(v_<equal_to_<type_<lazy::size_<p>>, size_t_<3>>>, "");
        static_assert(v_<equal_to_<type_<lazy::size_<p_empty>>, size_t_<0>>>, "");
        static_assert(v_<type_<lazy::empty_<p_empty>>>, "");

        static_assert(v_<is_same_<pack<int, double>, type_<lazy::cat_<a_list>>>>, "");
        static_assert(v_<is_same_<pack<int, double, float, short>, type_<lazy::cat_<a_list, a_list2>>>>, "");
        static_assert(v_<is_same_<pack<int, double, float, short, char>, type_<lazy::cat_<a_list, a_list2, a_list3>>>>, "");
        static_assert(v_<is_same_<pack<int, double>, type_<lazy::cat_<a_list>>>>, "");

        static_assert(v_<is_same_<pack<int, double>, type_<lazy::cat_<a_list>>>>, "");
        static_assert(v_<is_same_<pack<int, double, float, short>, type_<lazy::cat_<a_list, a_list2>>>>, "");
        static_assert(v_<is_same_<pack<int, double, float, short, char>, type_<lazy::cat_<a_list, a_list2, a_list3>>>>, "");
        static_assert(v_<is_same_<pack<int, double>, type_<lazy::cat_<a_list>>>>, "");

        static_assert(v_<is_same_<pack<int, short, double>, type_<lazy::push_back_<seq_t, double>>>>, "");
        static_assert(v_<is_same_<pack<double, int, short>, type_<lazy::push_front_<seq_t, double>>>>, "");

        static_assert(v_<is_same_<int, type_<lazy::at_<p, unsigned_<0>>>>>, "");
        static_assert(v_<is_same_<short, type_<lazy::at_<p, unsigned_<1>>>>>, "");
        static_assert(v_<is_same_<double, type_<lazy::at_<p, unsigned_<2>>>>>, "");
        static_assert(v_<is_same_<nil, type_<lazy::at_<p, unsigned_<3>>>>>, "");
        static_assert(v_ < is_same_ < nil, type_ < lazy::at_ < p, unsigned_ < -1 >>> > > , "");

        static_assert(v_<is_same_<clear_<p>, pack<>>>, "");
    }


    /// Unitary Test
    /// of functionclass.hpp
    namespace test_functionclass
    {
        static_assert(v_<is_placeholder_expression_<bind_<_0_, int>>>, "");
        static_assert(v_<is_placeholder_expression_<_0_>>, "");

        template<typename type_t>
        using is_int =
            is_same_<type_t, int>;

        using is_int_function =
            function_class_<is_int>;

        static_assert(v_<return_<is_int_function, int>>, "");
    }


    /// Unitary test
    /// of forward.hpp
    namespace test_forward
    {
        using begin_t = forward_iterator_builder_<pack<int, double, float>>;

        using next1_t = next_<begin_t>;
        using next2_t = next_<next1_t>;
        using end_t = next_<next2_t>;
        using end2_t = next_<end_t>;

        using a_range = clone_forward_<next_<begin_t>, end_t>;


        /// Effective test
        static_assert(v_<is_same_<item_<begin_t>, int>>, "");
        static_assert(v_<is_same_<item_<next1_t>, double>>, "");
        static_assert(v_<is_same_<item_<next2_t>, float>>, "");
        static_assert(v_<is_same_<item_<end_t>, nil>>, "");

        static_assert(v_<equal_to_<index_<begin_t>, begin_iterator_index>>, "");
        static_assert(v_<equal_to_<index_<next1_t>, unsigned_<1>>>, "");
        static_assert(v_<equal_to_<index_<next2_t>, unsigned_<2>>>, "");
        static_assert(v_<equal_to_<index_<end_t>, end_iterator_index>>, "");

        static_assert(v_<has_next_<begin_t>>, "");
        static_assert(v_<has_next_<next1_t>>, "");
        static_assert(v_<has_next_<next2_t>>, "");
        static_assert(v_<not_<has_next_<end_t>>>, "");
        static_assert(v_<not_<has_next_<end2_t>>>, "");

        static_assert(v_<is_valid_direction_<next_, begin_t>>, "");
        static_assert(v_<is_valid_direction_<next_, next1_t>>, "");
        static_assert(v_<is_valid_direction_<next_, next2_t>>, "");
        static_assert(!v_<is_valid_direction_<next_, end_t>>, "");

        static_assert(v_<is_same_<next2_t, last_valid_<begin_t>>>, "");

        static_assert(v_<is_same_<item_<begin_t>, int>>, "");
        static_assert(v_<equal_to_<distance_<begin_t, end_t>, long_<3>>>, "");
        static_assert(v_<equal_to_<distance_<begin_t, next2_t>, long_<2>>>, "");
        static_assert(v_<equal_to_<distance_<begin_t, next1_t>, long_<1>>>, "");
        static_assert(v_<equal_to_<distance_<begin_t, begin_t>, long_<0>>>, "");
        static_assert(v_<equal_to_<distance_<end_t, end_t>, long_<0>>>, "");

        static_assert(v_<is_same_<item_<a_range>, double>>, "");
        static_assert(v_<is_same_<item_<last_valid_<a_range>>, float>>, "");

        static_assert(v_<is_same_<index_<a_range>, long_<0>>>, "");
        static_assert(v_<is_same_<index_<next_<a_range>>, long_<1>>>, "");

        static_assert(v_ < is_same_ < index_<next_<next_<a_range>>>, long_ < -1 >>> , "");
        static_assert(v_<is_same_<index_<next_<next_<next_<a_range>>>>, end_iterator_index>>, "");
    }

    /// Unitary test
    /// of bidirectionnal.hpp
    namespace test_bidirectionnal
    {
        using begin_t = bidirectional_iterator_builder_<pack<int, double, float>>;
        using next1_t = next_<begin_t>;
        using next2_t = next_<next1_t>;
        using end_t = next_<next2_t>;
        using end2_t = next_<end_t>;

        using prev2_t = prev_<end_t>;
        using prev1_t = prev_<prev2_t>;
        using prev0_t = prev_<prev1_t>;

        using begin2_t = bidirectional_iterator_builder_<pack<int, short, double, float>>;
        using a_range = clone_bidirectional_<next_<begin2_t>, next_<last_valid_<begin2_t>>>;

        /// Effective test
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

        static_assert(v_<has_next_<begin_t>>, "");
        static_assert(v_<has_next_<next1_t>>, "");
        static_assert(v_<has_next_<next2_t>>, "");
        static_assert(v_<not_<has_next_<end_t>>>, "");
        static_assert(v_<not_<has_next_<end2_t>>>, "");

        static_assert(v_<has_prev_<end2_t>>, "");
        static_assert(v_<has_prev_<prev2_t>>, "");
        static_assert(v_<has_prev_<prev1_t>>, "");
        static_assert(v_<not_<has_prev_<prev0_t>>>, "");

        static_assert(v_<is_same_<item_<a_range>, short>>, "");
        static_assert(v_<is_same_<item_<last_valid_<a_range>>, float>>, "");

        static_assert(v_<is_same_<item_<prev_<next_<a_range>>>, short>>, "");
        static_assert(v_<is_same_<item_<prev_<next_<last_valid_<a_range>>>>, float>>, "");

        static_assert(v_<is_same_<index_<a_range>, long_<0>>>, "");
        static_assert(v_<is_same_<index_<next_<a_range>>, long_<1>>>, "");

        static_assert(v_<is_same_<index_<next_<next_<a_range>>>, long_<2>>>, "");
        static_assert(v_<is_same_<index_<next_<next_<next_<a_range>>>>, end_iterator_index>>, "");

        static_assert(v_<is_same_<begin_t, first_valid_<next2_t>>>, "");
    }


    /// Unitary test
    /// of algorithm.hpp
    namespace test_algorithm
    {
        using begin_t = forward_iterator_builder_<pack<int, double, short>>;

        using next1_t = next_<begin_t>; /// double
        using next2_t = next_<next1_t>; /// short
        using end_t = next_<next2_t>; /// nil

        /// Effective test
        static_assert(v_<is_same_<begin_t, advance_<begin_t, long_<0>>>>, "");
        static_assert(v_<is_same_<next1_t, advance_<next1_t, long_<0>>>>, "");
        static_assert(v_<is_same_<next2_t, advance_<next2_t, long_<0>>>>, "");
        static_assert(v_<is_same_<end_t, advance_<end_t, long_<0>>>>, "");
        static_assert(v_<is_same_<next1_t, advance_<begin_t, long_<1>>>>, "");
        static_assert(v_<is_same_<next2_t, advance_<begin_t, long_<2>>>>, "");
        static_assert(v_<is_same_<end_t, advance_<begin_t, long_<3>>>>, "");
        static_assert(v_<is_same_<end_t, advance_<next1_t, long_<2>>>>, "");

        static_assert(v_<is_same_<find_if_<begin_t, end_t, lambda<lazy::is_same_<next_<begin_t>, _0_> > > , next_<begin_t> > >, "");
        static_assert(v_<is_same_<find_<begin_t, end_t, item_<next_<begin_t>>> , next_<begin_t>> > , "");
    }

}

#endif
