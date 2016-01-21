#ifndef __BRAIN_META_STANDART_HPP__
# define __BRAIN_META_STANDART_HPP__

#include "logic.hpp"
#include <type_traits>

namespace brain
{
    namespace meta
    {
        /// ////////////////// ///
        /// Standart Extension ///
        /// ////////////////// ///


        /// Access to value_type member
        /// of type_t
        template<typename type_t>
        using vt_ =
            typename type_t::value_type;



        /// Alias for member
        /// const_iterator
        template<typename container_t>
        using citerator_ =
            typename container_t::
            const_iterator;


        /// Alias for member
        /// iterator
        template<typename container_t>
        using iterator_ =
            typename container_t::
            iterator;


        /// Alias for member
        /// reverse_iterator
        template<typename container_t>
        using riterator_ =
            typename container_t::
            reverse_iterator;


        /// Alias for member
        /// const_reverse_iterator
        template<typename container_t>
        using criterator_ =
            typename container_t::
            const_reverse_iterator;


        /// Determines if a
        /// type_t has the
        /// 'differen_type'
        /// member
        template < typename type_t,
                 typename = void >
        struct has_difference_type_t_:
                std::false_type
        {
        };


        /// Specialization for
        /// the case of type_t
        /// has the difference_type
        /// member
        template<typename type_t>
        struct has_difference_type_t_ <
                type_t,
                void_t<typename type_t::difference_type> > :
                std::true_type
        {
        };


        /// t_ shortcut for
        /// has_difference_type_t_
        template<typename type_t>
        using has_difference_type_t =
            lazy_t<has_difference_type_t_, type_t>;


        /// Determines if a
        /// type_t has the
        /// 'pointer' member
        template < typename type_t,
                 typename = void >
        struct has_pointer_t_:
                std::false_type
        {
        };


        /// Specialization for
        /// the case of type_t
        /// has the pointer
        /// member
        template<typename type_t>
        struct has_pointer_t_ <
                type_t,
                void_t<typename type_t::pointer> > :
                std::true_type
        {
        };


        /// t_ shortcut for
        /// has_pointer_t_
        template<typename type_t>
        using has_pointer_t =
            lazy_t<has_pointer_t_, type_t>;


        /// Determines if a
        /// type_t has the
        /// 'reference' member
        template < typename type_t,
                 typename = void >
        struct has_reference_t_:
                std::false_type
        {
        };


        /// Specialization for
        /// the case of type_t
        /// has the reference
        /// member
        template<typename type_t>
        struct has_reference_t_ <
                type_t,
                void_t<typename type_t::reference> > :
                std::true_type
        {
        };


        /// t_ shortcut for
        /// has_reference_t_
        template<typename type_t>
        using has_reference_t =
            lazy_t<has_reference_t_, type_t>;


        /// Determines if a
        /// type_t has the
        /// 'iterator_category'
        /// member
        template < typename type_t,
                 typename = void >
        struct has_iterator_category_t_:
                std::false_type
        {
        };


        /// Specialization for
        /// the case of type_t
        /// has the iterator_category
        /// member
        template<typename type_t>
        struct has_iterator_category_t_ <
                type_t,
                void_t<typename type_t::iterator_category> > :
                std::true_type
        {
        };


        /// t_ shortcut for
        /// has_iterator_category_t_
        template<typename type_t>
        using has_iterator_category_t =
            lazy_t<has_iterator_category_t_, type_t>;


        /// Determines if a
        /// type_t has the
        /// 'value_type'
        /// member
        template < typename type_t,
                 typename = void >
        struct has_value_type_t_:
                std::false_type
        {
        };


        /// Specialization for
        /// the case of type_t
        /// has the value_type
        /// member
        template<typename type_t>
        struct has_value_type_t_ <
                type_t,
                void_t<typename type_t::value_type> > :
                std::true_type
        {
        };


        /// t_ shortcut for
        /// has_value_type_t_
        template<typename type_t>
        using has_value_type_t =
            lazy_t<has_value_type_t_, type_t>;



        /// Returns true_type
        /// type_t has the members :
        /// - difference_type
        /// - value_type
        /// - pointer
        /// - reference
        /// - iterator_category
        template<typename type_t>
        using is_stditerator_t =
            and_t <
            has_difference_type_t<type_t>,
            has_value_type_t<type_t>,
            has_pointer_t<type_t>,
            has_reference_t<type_t>,
            has_iterator_category_t<type_t >>;


        /// Determines if the
        /// type_t has begin()
        /// method
        template < typename type_t,
                 typename = void >
        struct has_begin_method_t_
                : std::false_type {};


        /// Specialization for
        /// the case where begin()
        /// is member of type_t
        template<typename type_t>
        struct has_begin_method_t_ < type_t,
        void_t<decltype(std::declval<type_t>().begin()) >>
            : std::true_type {};


        /// t_ shortcut for
        /// has_begin_method_t_
        template<typename type_t>
        using has_begin_method_t =
            lazy_t<has_begin_method_t_, type_t>;


        /// Determines if the
        /// type_t has end()
        /// method
        template < typename type_t,
                 typename = void >
        struct has_end_method_t_
                : std::false_type {};


        /// Specialization for
        /// the case where end()
        /// is member of type_t
        template<typename type_t>
        struct has_end_method_t_ < type_t,
        void_t<decltype(std::declval<type_t>().end()) >>
            : std::true_type {};


        /// t_ shortcut for
        /// has_end_method_t_
        template<typename type_t>
        using has_end_method_t =
            lazy_t<has_end_method_t_, type_t>;


        /// Returns true_type
        /// if type_t is iterable :
        /// - has begin() method
        /// - has end() method
        template <typename type_t>
        using is_iterable_t =
            and_t < has_begin_method_t<type_t>,
            has_end_method_t<type_t> >;


        /// Returns iterable_state_t
        /// if type_t is conformed
        /// with is_iterable_t test
        /// else, returns invalid_state
        struct iterable_state
        {
            template<typename type_t>
            using state = void;
            ///state_s<type_t, is_iterable_t, iterable_state>;
        };

    }
}

#endif
