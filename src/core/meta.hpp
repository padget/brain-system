#ifndef __META_BRAIN_HPP
#define __META_BRAIN_HPP

#include <type_traits>
namespace brain
{
    /// Inspired by https://github.com/ericniebler/meta
    /// (author https://github.com/ericniebler)
    ///
    /// This library contains tow main principles :
    ///  - list<types_t...>
    ///  - meta function return_<>;
    ///
    /// The public metas functions (with return_)
    /// will present in ft namespace
    /// For all struct / using that returns 'type'
    /// an '_t_' will be added to end of its name.
    /// For all using that encapsulate t_<type_t>
    /// '_t' will be added to its name.
    /// Same things for metafunction with return_
    /// by adding '_r_'(and '_r')
    namespace meta
    {
        /// //////////////////////////////////// ///
        /// Shortcut for access template members ///
        /// //////////////////////////////////// ///

        
        /// Access to value_type member
        /// of type_t
        template<typename type_t>
        using vt_ =
            typename type_t::value_type;





        /// Finds the first type
        /// that respects the
        /// predicate_t. If there
        /// is no element, it
        /// won't compile.
        template < typename list_t,
                 typename predicate_t >
        struct find_one_if_t_;


        /// Specialisation for
        /// find_one_if_t_ that
        /// distings each type
        /// of list_t
        template < typename ... types_t,
                 typename predicate_t >
        struct find_one_if_t_<list<types_t...>, predicate_t>
        {
            using type =
                at_t <
                unsigned_t<0>,
                concat_t<if_t <r_<predicate_t, types_t>, list<types_t>, list<>>...>
                >;

            static_assert(!v_<std::is_same<nil, type>>,
                          "the type is equals to nil !! ");
        };


        /// t_ shortcut for
        /// find_one_if_t_
        template < typename list_t,
                 typename predicate_t >
        using find_one_if_t =
            lazy_t<find_one_if_t_, list_t, predicate_t>;


        

        /// ////////////////////////// ///
        /// Meta function manipulation ///
        /// ////////////////////////// ///

        /// A meta function is
        /// a template that
        /// contains the return_
        /// member. This member
        /// is an alias type
        /// that represents the
        /// transformation that
        /// the input types
        /// delt with








        /// TODO Sort + Doc
        template < typename res_t ,
                 typename type_t,
                 typename ref_t >
        using inc_if_t =
            if_t < std::is_same<ref_t, type_t>,
            inc_t<res_t>, res_t >;


        /// TODO Sort + Doc
        template < typename list_t,
                 typename ref_t >
        using count_t =
            accumulate_t < list_t,
            unsigned_t<0>,
            bind_back_r_<as_r_<inc_if_t>, ref_t >>;


        /// ///////////////////////////////// ///
        /// Lambda with placeholding features ///
        /// ///////////////////////////////// ///


        /// Replaces types from
        /// list_t that represents
        /// a key in map_t
        template < typename list_t,
                 typename map_t >
        struct map_replace_t_;


        /// Specialisation for
        /// map_replace_t_ that
        /// distings each type
        /// of list_t
        template < typename ... types_t,
                 typename map_t >
        struct map_replace_t_<list<types_t...>, map_t>
        {
            using type =
                list<value_of_t<map_t, types_t>...>;
        };


        /// t_ shortcut for
        /// map_replace_t
        template < typename list_t,
                 typename map_t >
        using map_replace_t =
            lazy_t<map_replace_t_, list_t, map_t>;




        /// //////////////// ///
        /// Runtime features ///
        /// //////////////// ///


        /// Execute the same
        /// algorithm func_t
        /// foreach types_t
        /// and can accumulate
        /// results with accum_t
        template < typename types_t,
                 template<typename> typename func_t,
                 typename accum_t = void >
        struct foreach_type;


        /// Specialization for
        /// void accum_t. The
        /// accum_t is not used.
        template < typename first_t,
                 typename next_t,
                 typename ... types_t,
                 template<typename> typename func_t >
        struct foreach_type<list<first_t, next_t, types_t...>, func_t, void>
        {
            /// Operator () for
            /// functor using
            template<typename ... args_t>
            constexpr void operator()(
                args_t && ... args)
            {
                func_t<first_t>()(args...);
                foreach_type<list<next_t, types_t...>, func_t, void>()(args...);
            }
        };


        /// Specialization for
        /// void accum_t. The
        /// accum_t is not used.
        template < typename last_t,
                 template<typename> typename func_t >
        struct foreach_type<list<last_t>, func_t, void>
        {
            /// Operator () for
            /// functor using
            template<typename ... args_t>
            constexpr void operator()(
                args_t && ... args)
            {
                func_t<last_t>()(args...);
            }
        };


        /// Specialization for an
        /// active accum_t. The func_t
        /// is executed for first_t
        /// and is prepared for next_t.
        /// The results are accumulates
        /// with accum_t
        template < typename first_t,
                 typename next_t,
                 typename ... types_t,
                 template<typename> typename func_t ,
                 typename accum_t >
        struct foreach_type<list<first_t, next_t, types_t...>, func_t, accum_t>
        {
            /// Operator () for
            /// functor using
            template<typename ... args_t>
            constexpr auto operator()(
                args_t && ... args)
            {
                /// Accumulates the results
                /// between first_t and next_t
                return accum_t()(func_t<first_t>()(args...),
                                 foreach_type<list<next_t, types_t...>, func_t, accum_t>()(args...));
            }
        };


        /// Specialization for an
        /// active accum_t. The func_t
        /// is executed for last_t
        template < typename last_t,
                 template<typename> typename func_t,
                 typename accum_t >
        struct foreach_type<list<last_t>, func_t, accum_t>
        {
            /// Operator () for
            /// functor using
            template<typename ... args_t>
            constexpr auto operator()(
                args_t && ... args)
            {
                /// Returns only the
                /// the results of last_t,
                /// there is no need of
                /// accum_t
                return func_t<last_t>()(args...);
            }
        };


        /// ////////////////// ///
        /// Standart Extension ///
        /// ////////////////// ///


        /// Alias for member
        /// const_iterator
        template<typename container_t>
        using citerator_t =
            typename container_t::
            const_iterator;


        /// Alias for member
        /// iterator
        template<typename container_t>
        using iterator_t =
            typename container_t::
            iterator;


        /// Alias for member
        /// reverse_iterator
        template<typename container_t>
        using riterator_t =
            typename container_t::
            reverse_iterator;


        /// Alias for member
        /// const_reverse_iterator
        template<typename container_t>
        using criterator_t =
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
                void_r<typename type_t::difference_type> > :
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
                void_r<typename type_t::pointer> > :
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
                void_r<typename type_t::reference> > :
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
                void_r<typename type_t::iterator_category> > :
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
                void_r<typename type_t::value_type> > :
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
        using is_iterator_t =
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
        void_r<decltype(std::declval<type_t>().begin()) >>
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
        void_r<decltype(std::declval<type_t>().end()) >>
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


        /// //////// ///
        /// Unsorted ///
        /// //////// ///





        /// TODO Sort + Doc
        template < unsigned _nb,
                 typename type_t >
        struct repeat_t_
        {
            using type =
                concat_t <
                t_ < repeat_t_ < _nb / 2, type_t >> ,
                t_ < repeat_t_ < _nb / 2, type_t >> ,
                t_ < repeat_t_ < _nb % 2, type_t >>>;
        };


        /// TODO Sort + Doc
        template <typename type_t>
        struct repeat_t_<0u, type_t>
        {
            using type =
                list<>;
        };


        /// TODO Sort + Doc
        template <typename type_t>
        struct repeat_t_<1u, type_t>
        {
            using type =
                list<type_t>;
        };


        /// TODO Sort + Doc
        template < typename nb_t,
                 typename type_t >
        using repeat_t =
            t_<repeat_t_<v_<nb_t>, type_t>>;


        /// TODO Sort + Doc
        template < unsigned _nb,
                 typename type_t >
        using repeat_c =
            lazy_t<repeat_t, unsigned_t<_nb>, type_t>;


        /// TODO Sort + Doc
        template < typename list_t,
                 typename old_t,
                 typename new_t >
        struct replace_t_;


        /// TODO Sort + Doc
        template < typename ... types_t,
                 typename old_t,
                 typename new_t >
        struct replace_t_<list<types_t...>, old_t, new_t>
        {
            using type = /// TODO Faire du replace_if et donc transformer is_same en prédicat.
                list<if_t<std::is_same<types_t, old_t>, new_t, types_t>...>;
        };


        /// TODO Sort + Doc
        template < typename list_t,
                 typename old_t,
                 typename new_t >
        using replace_t =
            lazy_t<replace_t_, list_t, old_t, new_t>;


        template<typename ... types_t>
        struct inherit:
            public types_t ...
        {
        };






    }
}


#endif
