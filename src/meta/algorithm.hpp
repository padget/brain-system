#ifndef __BRAIN_META_ALGORITHM_HPP__
# define __BRAIN_META_ALGORITHM_HPP__

# include "sequence.hpp"

namespace brain
{
    namespace meta
    {
        template < typename sequence_t,
                 typename pred_r >
        using find_if_ =
            navigate_next_ <
            begin_<sequence_t>,
            end_<sequence_t>,
            idem_,
            end_<sequence_t>,
            function_class_<next_>,
            pred_r >;


        template<typename target_t>
        struct is_same_iter_r_ /// TODO To replace by lambda when done
        {
            template<typename current_t>
            using return_ =
                is_same_<item_<current_t>, target_t>;
        };

        template<typename target_t>
        struct is_not_same_iter_r_  /// TODO To replace by lambda when done
        {
            template<typename current_t>
            using return_ =
                not_<is_same_<item_<current_t>, target_t> >;
        };


        template < typename sequence_t,
                 typename type_t >
        using find_ =
            find_if_<sequence_t, is_not_same_iter_r_<type_t>>;


        namespace lazy
        {
            template < typename sequence_t,
                     typename pred_r >
            using find_if_ =
                function_<find_if_, sequence_t, pred_r>;

            template < typename sequence_t,
                     typename type_t >
            using find_ =
                function_<find_, sequence_t, type_t>;
        }


        namespace test_find_if
        {
            using a_list = forward_list<int, short, double>;

            static_assert(v_<is_same_<find_if_<a_list, is_not_same_iter_r_<short>>, next_<begin_<a_list>>>>, "");
            static_assert(v_<is_same_<find_<a_list, short>, next_<begin_<a_list>>>>, "");
        }


        template < typename sequence_t,
                 typename type_t >
        using contains_ =
            not_<is_same_<find_<sequence_t, type_t>, end_<sequence_t>>>;


        namespace test_contains
        {
            static_assert(v_<contains_<forward_list<int, short, double>, double>>, "");
            static_assert(!v_<contains_<forward_list<int, short, double>, char>>, "");
        }


        template <typename pred_r>
        struct if_true_one_
        {
            template<typename current_t>
            using return_ =
                if_ <
                return_<pred_r, current_t>,
                unsigned_<1>,
                unsigned_<0> >;
        };


        template < typename sequence_t,
                 typename pred_r >
        using count_if_ =
            navigate_next_ <
            begin_<sequence_t>,
            end_<sequence_t>,
            idem_,
            unsigned_<0>,
            if_true_one_<pred_r>,
            default_test_<end_<sequence_t>>,
            function_class_<plus_> >;

        template < typename sequence_t,
                 typename type_t >
        using count_ =
            count_if_<sequence_t, is_same_iter_r_<type_t>>;

        namespace lazy
        {
            template < typename sequence_t,
                     typename pred_r >
            using count_if_ =
                function_<count_if_, sequence_t, pred_r>;
        }

        namespace test_count_
        {
            using seq_t = forward_list<int, short, short, short, double>;
            static_assert(v_<equal_to_<count_if_<seq_t, is_not_same_iter_r_<short>>, unsigned_<2> > >, "");
            static_assert(v_<equal_to_<count_if_<seq_t, is_same_iter_r_<short>>, unsigned_<3> > >, "");
        }
}

#endif
