#ifndef __BRAIN_META_ITERATOR_ALGORITHM_HPP__
# define  __BRAIN_META_ITERATOR_ALGORITHM_HPP__

# include "forward.hpp"
# include "bidirectionnal.hpp"
# include "iteration.hpp"

namespace meta
{

    /// type_ shortcut for
    /// distance_t_
    template < typename begin_t,
               typename end_t >
    using distance_ =
        fold_ <
        begin_t,
        end_t,
        int_<0>,
        lazy::inc_<_0_ >>;


    namespace lazy
    {
        /// Lazy signature
        /// of distance_
        template < typename begin_t,
                   typename end_t >
        struct distance_ :
            meta::function_<meta::distance_, begin_t, end_t> {};
    }

    /// Advance the iterator
    /// from begin the next
    /// nb_steps_t steps.
    template < typename begin_t,
               typename nb_steps_t >
    using advance_ =
        fold_ <
        begin_t,
        next_<last_valid_<begin_t>>,
        begin_t,
        lazy::if_ <
            lazy::less_ <
                lazy::distance_<begin_t, _1_>,
                nb_steps_t > ,
            lazy::next_<_1_>,
            _0_ >>;


    /// Finds the first
    /// iterator that
    /// matches with the
    /// predicates pred_r
    template < typename begin_t,
               typename end_t,
               typename pred_r >
    using find_if_ =
        at_ <
        fold_ <
            begin_t,
            end_t,
            pack<>,
            lazy::if_ <
                bind_<pred_r, _1_>,
                lazy::push_back_<___, ___>,
                _0_ > > ,
        int_<0 >>;


    /// Finds the first
    /// iterator where the
    /// type is the same
    /// as target_t
    template < typename begin_t,
               typename end_t,
               typename target_t >
    using find_ =
        find_if_ <
        begin_t,
        end_t,
        lambda<
            lazy::is_same_<
                target_t,
                lazy::item_<_0_>>> >;


    /// Count the number
    /// of iterator that
    /// matches wit the
    /// predicate pred_r
    template <typename begin_t,
              typename end_t,
              typename pred_r>
    using count_if_ =
        fold_ <
        begin_t,
        end_t,
        int_<0>,
        lazy::if_ <
            bind_<pred_r, _1_>,
            lazy::inc_<_0_>,
            _0_ >>;


    /// Count the number
    /// of occurence of
    /// the type target_t
    template < typename begin_t,
               typename end_t,
               typename target_t >
    using count_ =
        count_if_ <
        begin_t,
        end_t,
        lambda<lazy::is_same_<target_t, lazy::item_<___>> >>;


    /// Returns true_ if
    /// the type target_t
    /// is present at least
    /// once
    template < typename begin_t,
               typename end_t,
               typename target_t >
    using contains_ =
        greater_<count_<begin_t, end_t, target_t>, unsigned_<0>>;


    /// Transforms each iterator
    /// item with the meta
    /// function class func_r
    template < typename begin_t,
               typename end_t,
               typename func_r >
    using transform_ =
        fold_ <
        begin_t,
        end_t,
        pack<>,
        lazy::push_back_<_0_, bind_<func_r, _1_> >>;


    /// Replace all items
    /// with new_t if they
    /// matche with the
    /// predicate pred_r
    template < typename begin_t,
               typename end_t,
               typename new_t,
               typename pred_r >
    using replace_if_ =
        transform_ <
        begin_t,
        end_t,
        lambda<lazy::if_<bind_<pred_r, _0_>, new_t, lazy::item_<_0_>> >>;


    /// Replace all old_t
    /// by the new_t
    template < typename begin_t,
               typename end_t,
               typename old_t,
               typename new_t >
    using replace_ =
        replace_if_ <
        begin_t,
        end_t,
        new_t,
        lambda<lazy::is_same_<old_t, lazy::item_<_0_>> >>;


    /// Remove all types
    /// that matche with
    /// predicate pred_r
    template < typename begin_t,
               typename end_t,
               typename pred_r >
    using remove_if_ =
        fold_ <
        begin_t,
        end_t,
        pack<>,
        lazy::if_ <
            bind_<pred_r, _1_>,
            _0_,
            lazy::push_back_<_0_, lazy::item_<_1_> >>>;


    /// Remove all deleted_t
    /// occurences
    template < typename begin_t,
               typename end_t,
               typename deleted_t >
    using remove_ =
        remove_if_ <
        begin_t,
        end_t,
        lambda<lazy::is_same_<deleted_t, lazy::item_<_0_>> >>;


    namespace lazy
    {
        /// Lazy signature
        /// of advance_
        template < typename begin_t,
                   typename nb_steps_t >
        struct advance_ :
            meta::function_<meta::advance_, begin_t, nb_steps_t> {};


        /// Lazy signature
        /// of find_if_
        template < typename begin_t,
                   typename end_t,
                   typename pred_r >
        struct find_if_ :
            meta::function_<meta::find_if_, begin_t, end_t, pred_r> {};


        /// Lazy signature
        /// of find_
        template < typename begin_t,
                   typename end_t,
                   typename type_t >
        struct find_ :
            meta::function_<meta::find_, begin_t, end_t, type_t> {};


        /// Lazy signature
        /// of count_if_
        template < typename begin_t,
                   typename end_t,
                   typename pred_r >
        struct count_if_ :
            meta::function_<meta::count_if_, begin_t, end_t, pred_r> {};


        /// Lazy signature
        /// of count_
        template < typename begin_t,
                   typename end_t,
                   typename target_t >
        struct count_ :
            meta::function_<meta::count_, begin_t, end_t, target_t> {};


        /// Lazy signature
        /// of contains_
        template < typename begin_t,
                   typename end_t,
                   typename target_t >
        struct contains_ :
            meta::function_<meta::contains_, begin_t, end_t, target_t> {};


        /// Lazy signature
        /// of transform_
        template < typename begin_t,
                   typename end_t,
                   typename func_r >
        struct transform_ :
            meta::function_<meta::transform_, begin_t, end_t, func_r> {};


        /// Lazy signature
        /// of replace_if_
        template < typename begin_t,
                   typename end_t,
                   typename new_t,
                   typename pred_r >
        struct replace_if_ :
            meta::function_<meta::replace_if_, begin_t, end_t, new_t, pred_r> {};


        /// Lazy signature
        /// of replace_
        template < typename begin_t,
                   typename end_t,
                   typename old_t,
                   typename new_t >
        struct replace_ :
            meta::function_<meta::transform_, begin_t, end_t, old_t, new_t> {};


        /// Lazy signature
        /// of remove_if_
        template < typename begin_t,
                   typename end_t,
                   typename pred_r >
        struct remove_if_ :
            meta::function_<meta::transform_, begin_t, end_t, pred_r> {};


        /// Lazy signature
        /// of remove_
        template < typename begin_t,
                   typename end_t,
                   typename deleted_t >
        struct remove_ :
            meta::function_<meta::transform_, begin_t, end_t, deleted_t> {};

    }


    template < typename begin_t,
               typename end_t >
    using unique_ =
        remove_if_ <
        begin_t,
        end_t,
        lambda<
            lazy::greater_<
                lazy::count_<
                    begin_t, lazy::next_<_0_>,
                    lazy::item_<_0_>>,
                int_<1>>>>;


    /// Reverses the
    /// types order
    template < typename begin_t,
               typename end_t >
    using reverse_ =
        rfold_<begin_t, end_t, pack<>, lazy::push_back_<_0_, lazy::item_<_1_>>>;


    namespace lazy
    {
        /// Lazy signature
        /// of unique_
        template < typename begin_t,
                   typename end_t >
        struct unique_ :
            meta::function_<meta::unique_, begin_t, end_t> {};


        /// Lazy signature
        /// of reverse_
        template < typename begin_t,
                   typename end_t >
        using reverse_ =
            meta::function_<meta::reverse_, begin_t, end_t>;
    }

    /// TODO All reversed algorithms...
}

#endif
