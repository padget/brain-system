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

        struct nil {};


        /// Access to value_type member
        /// of type_t
        template<typename type_t>
        using vt_ =
            typename type_t::value_type;


        /// Access to size member
        /// of type_t
        template<typename type_t>
        constexpr decltype(t_<type_t>::size) size_ =
            t_<type_t>::size;


        /// Access to return_ member
        /// of type_t
        template < typename type_r,
                 typename ... args_t >
        using return_ =
            typename type_r::
            template return_<args_t...>;


        /// Shortcut for return_
        template < typename type_r,
                 typename ... args_t >
        using r_ =
            return_<type_r, args_t...>;


        /// //////////////////////// ///
        /// Meta function conversion ///
        /// //////////////////////// ///


        /// Transforms func_t into
        /// a meta function
        template <template<typename...> typename func_t>
        struct as_r_
        {
            template<typename ... args_t>
            using return_ =
                t_<defer_t_<func_t, args_t...>>;
        };


        /// r_ shortcut for
        /// as_r_<type_t>, args_t...
        template < template<typename ...> typename type_t,
                 typename ... args_t >
        using as_r =
            r_<as_r_<type_t>, args_t...>;





        /// ////////////// ///
        /// Type selection ///
        /// ////////////// ///


        /// Type selector
        template<typename ...>
        struct if_t_;


        /// Type selector
        /// specialisation that
        /// returns void
        /// if_t is true
        template<typename if_t>
        struct if_t_<if_t> :
                std::enable_if<v_<if_t>>
        {
        };


        /// Type selector
        /// specialisation that
        /// returns then_t
        /// if_t is true
        template < typename if_t,
                 typename then_t >
        struct if_t_<if_t, then_t>:
                std::enable_if<v_<if_t>, then_t>
        {
        };


        /// Type selector
        /// specialisation that
        /// returns then_t
        /// if_t is true
        /// else else_t
        template < typename if_t,
                 typename then_t,
                 typename else_t >
        struct if_t_<if_t, then_t, else_t>:
                std::conditional<v_<if_t>, then_t, else_t>
        {
        };


        /// Evaluates the result
        /// of t_<_if_<args_t...>>
        template<typename ... args_t>
        using if_t =
            defer_t<if_t_, args_t...>;


        /// Evaluates the result
        /// of if_<bool_<_b>, args_t... >
        template < bool _b,
                 typename... args_t >
        using if_c =
            if_t<bool_t_<_b>, args_t...>;


        /// Evaluates the result
        /// of if_<if_t, then_t, else_t>
        template < typename test_t,
                 typename then_t,
                 typename else_t >
        using select_t =
            if_t<test_t, then_t, else_t> ;


        /// Evaluates the result
        /// of if_c<_b, then_t, else_t>
        template < bool _b,
                 typename then_t,
                 typename else_t >
        using select_c =
            if_c<_b, then_t, else_t> ;


        /// Returns std::true_type
        /// if all bools_t are true
        template <typename... bools_t>
        struct and_t_;


        /// Specialisation for
        /// _and_ that returns
        /// std::true_type for
        /// default case.
        template <>
        struct and_t_<> :
                std::true_type
        {
        };

        template < typename test_t,
                 typename ... other_t >
        struct and_t_<test_t> :
                bool_t_<v_<test_t> and v_<t_<and_t_<other_t...>>>>
        {
        };




        /// Specialisation for
        /// and_ that returns
        /// std::false_type if
        /// one of bools_t is
        /// false
        template < typename bool_t,
                 typename... bools_t >
        struct and_t_<bool_t, bools_t...>:
                if_c < !v_<bool_t>, std::false_type, and_t_<bools_t... >>
        {
        };


        /// Evaluates the result
        /// of t_<_and_<bools_t...>>
        template<typename ... bools_t>
        using and_t =
            defer_t<and_t_, bools_t...>;


        /// Returns std::true_type
        /// if one or more bools_t
        /// is true
        template <typename... bools_t>
        struct or_t_;


        /// Specialisation for
        /// _or_ that returns
        /// std::false_type
        /// for default case
        template <>
        struct or_t_<> :
                std::false_type
        {
        };


        /// Specialisation for
        /// _and_ that returns
        /// std::false_type if
        /// all of bools_t is
        /// false
        template < typename bool_t,
                 typename... bools_t >
        struct or_t_<bool_t, bools_t...> :
                if_c < v_<bool_t>,
                std::true_type,
                or_t_<bools_t... >>
        {
        };


        /// Evaluates the result
        /// of t_<_or_<bools_t...>>
        template<typename ... bools_t>
        using or_t =
            defer_t<or_t_, bools_t...>;


        /// Negates the bool_t
        template<typename bool_t>
        using not_t_ =
            bool_t_ < !v_<bool_t >>;


        /// t_ shortcut for not_t_
        template<typename bool_t>
        using not_t =
            defer_t<not_t_, bool_t>;


        /// //////////////////////////////////////// ///
        /// Wrapper for parameters pack manipulation ///
        /// //////////////////////////////////////// ///


        /// Wrapper for a
        /// parameters pack.
        template<typename ... types_t>
        struct list
        {
            using type = list;
            static constexpr auto size =
                v_<sizeof_pack_t_<types_t...>>;
        };


        /// Returns an empty
        /// list. Its a convenient
        /// shortcut for many
        /// list algorithm
        struct empty_list_t_
        {
            using type = list<>;
        };


        /// t_ shortcut for
        /// empty_list_t_
        using empty_list_t =
            t_<empty_list_t_>;


        /// Returns bool_<true>
        /// if list_t is empty_
        template<typename list_t>
        using empty_t_ =
            bool_t_<size_<list_t>>;


        /// t_ shortcut for empty_
        template<typename list_t>
        using empty_t =
            defer_t<empty_t_, list_t>;


        /// Returns the type
        /// at the target_t
        /// position if current_t
        /// and target_t represents
        /// the same position in
        /// pack list_t
        template < typename target_t,
                 typename current_t,
                 typename list_t >
        struct at_t_;


        /// Specialisation for
        /// at_t that takes an
        /// empty list and returns
        /// nil type
        template < typename target_t,
                 typename current_t >
        struct at_t_<target_t, current_t, list<>>
        {
            using type =
                nil;

            static_assert(v_<std::is_same<type, nil>>,
                          "nil detected !!!");
        };


        /// Specialisation for
        /// at_t_ that distings
        /// the first type_t off
        /// the others types_t
        /// from the list.
        template < typename target_t,
                 typename current_t,
                 typename type_t,
                 typename ... types_t >
        struct at_t_ < target_t,
                current_t,
                list<type_t, types_t... >>
        {
            using type =
                if_t <
                equal_to_t<target_t, current_t>,
                type_t,
                t_<at_t_<target_t, inc_t<current_t>, list<types_t...>> >>;

        };


        /// t_ shortcut for at_t_
        template < typename target_t,
                 typename list_t >
        using at_t =
            defer_t<at_t_, target_t, unsigned_t<0>, list_t>;



        /// Shortcut for at_t that
        /// takes directly an unsigned
        template < unsigned _target,
                 typename list_t >
        using at_c =
            at_t<unsigned_t<_target>, list_t>;


        /// Returns first type
        /// of list_t
        template<typename list_t>
        struct front_t_;


        /// Specialisation of
        /// front_ that identifies
        /// the head_t of list_t
        template < typename head_t,
                 typename ... types_t >
        struct front_t_<list<head_t, types_t...>>
        {
            using type =
                head_t;
        };


        /// Evaluates t_<front_<list_t>>
        template<typename list_t>
        using front_t =
            defer_t<front_t_, list_t>;


        /// Private private_ementation
        /// of back_ template
        template<typename ... types_t>
        struct back_t_;


        /// Private private_ementation
        /// of back_
        template<typename type_t>
        struct back_t_<type_t>
        {
            using type =
                type_t;
        };


        /// Private private_ementation
        /// of back_ template
        template < typename type_t,
                 typename ... types_t >
        struct back_t_<type_t, types_t...>
        {
            using type = t_<back_t_<types_t...>>;
        };


        /// private_ementation for
        /// back_ in case of list
        template<typename ... types_t>
        struct back_t_<list<types_t...>>
        {
            using type = t_<back_t_<types_t...>>;
        };


        /// Evaluates the result of
        /// t_<private_::back_<list_t>>
        template<typename list_t>
        using back_t =
            defer_t<back_t_, list_t>;


        /// Push a type_t at
        /// back of list_t
        template < typename type_t,
                 typename list_t >
        struct push_back_t_ ;


        /// Specialisation for
        /// push_back_ to expand
        /// types_t pack parameters
        template < typename type_t,
                 typename ... types_t >
        struct push_back_t_<type_t, list<types_t...>>
        {
            using type = list<types_t..., type_t>;
        };


        /// Evaluates the result
        /// of t_<push_back_<type_t, list_t>>
        template < typename type_t,
                 typename list_t >
        using push_back_t =
            defer_t<push_back_t_, type_t, list_t>;


        /// Pushs a type_t at
        /// front_ of list_t
        template < typename type_t,
                 typename list_t >
        struct push_front_t_;


        /// Specialisation for
        /// push_front_ to expand
        /// types_t pack parameters
        template < typename type_t,
                 typename ... types_t >
        struct push_front_t_<type_t, list<types_t...>>
        {
            using type = list<type_t, types_t...>;
        };


        /// Evaluates the result
        /// of t_<push_front_<type_t, list_t>>
        template < typename type_t,
                 typename list_t >
        using push_front_t =
            defer_t<push_front_t_, type_t, list_t>;


        /// Removes the first
        /// type of list_t
        template<typename list_t>
        struct pop_front_t_;


        /// Specialisation for
        /// pop_front_ that identifies
        /// and removes the first
        /// type
        template < typename first_t,
                 typename ... types_t >
        struct pop_front_t_<list<first_t, types_t...>>
        {
            using type = list<types_t...>;
        };


        /// Evaluates the result
        /// of t_<pop_front_<list_t>>
        template<typename list_t>
        using pop_front_t =
            defer_t<pop_front_t_, list_t>;


        /// Concatenates all lists_t
        /// into a single list
        template <typename... lists_t>
        struct concat_t_;


        /// Specialisation for
        /// concat_ that takes no
        /// list and return an
        /// empty_ list.
        template <>
        struct concat_t_<>
        {
            using type = list<>;
        };


        /// Specialisation for
        /// concat_ that takes
        /// only one list and
        /// returns the same list
        template <typename... types_t>
        struct concat_t_<list<types_t...>>
        {
            using type = list<types_t...>;
        };


        /// Specialisation for
        /// concat_ that takes
        /// two lists and returns
        /// the concatenated list
        template < typename... types1_t,
                 typename... types2_t >
        struct concat_t_ <
                list<types1_t...>,
                list<types2_t...> >
        {
            using type =
                list<types1_t..., types2_t...>;
        };


        /// Specialisation for
        /// concat_ that represents
        /// the general case.
        template < typename... types1_t,
                 typename... types2_t,
                 typename... others_t >
        struct concat_t_ <
                list<types1_t...>,
                list<types2_t...>,
                others_t... >

        {
            using type =
                t_<concat_t_<list<types1_t..., types2_t...>, others_t...>>;
        };


        /// Evaluates the result
        /// of t_<concat_<lists_t...>>
        template <typename... lists_t>
        using concat_t =
            defer_t<concat_t_, lists_t...>;


        /// Removes the last
        /// type of list_t
        template<typename list_t>
        struct pop_back_t_;


        /// Specialisation for
        /// pop_back_t_ used
        /// for list with one
        /// element inside
        template<typename type_t>
        struct pop_back_t_<list<type_t>>
        {
            using type =
                list<>;
        };


        /// Specialisation for
        /// pop_back_t_ used
        /// for list with no
        /// element inside
        template < typename type_t,
                 typename ... types_t >
        struct pop_back_t_<list<type_t, types_t...>>
        {
            using type =
                concat_t < list<type_t>,
                t_<pop_back_t_<list<types_t...>> >>;
        };


        /// Evaluates the result
        /// of t_<pop_back_<list_t>>
        template<typename list_t>
        using pop_back_t =
            defer_t<pop_back_t_, list_t>;


        /// Convert any pack
        /// representation into
        /// a list
        template<typename pack_t>
        struct to_list_t_;


        /// Specialisation of
        /// to_list_t_ that
        /// distings the types_t
        template < template<typename ...> typename pack_t,
                 typename ... types_t >
        struct to_list_t_<pack_t<types_t...>>
        {
            using type =
                list<types_t...>;
        };


        /// t_ shortcut for to_list_t_
        template<typename pack_t>
        using to_list_t =
            defer_t<to_list_t_, pack_t>;


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
            defer_t<find_one_if_t_, list_t, predicate_t>;


        /// //////////////////////////// ///
        /// Wrapper for map manipulation ///
        /// //////////////////////////// ///


        /// Wrapper for pair
        /// key-value
        template < typename key_t,
                 typename value_t >
        using pair =
            list<key_t, value_t>;


        /// Returns the first
        /// type of a pair
        template<typename pair_t>
        using first_t =
            at_t<unsigned_t<0>, pair_t>;


        /// Returns the second
        /// type of a pair
        template<typename pair_t>
        using second_t =
            at_t<unsigned_t<1>, pair_t>;


        /// Build a map from
        /// list of keys and
        /// list of values
        template < typename keys_t,
                 typename values_t >
        struct to_map_t_;


        /// Specialisation for
        /// to_map_t_ that distings
        /// elements of keys_t
        /// and values_t
        template < typename ... keys_t,
                 typename ... values_t >
        struct to_map_t_ <
                list<keys_t...>,
                list<values_t... >>
        {
            using type =
                list<pair<keys_t, values_t>...>;
        };


        /// t_ shortcut for to_map_t_
        template < typename keys_t,
                 typename values_t >
        using to_map_t =
            defer_t<to_map_t_, keys_t, values_t>;


        /// Returns the value
        /// of mapped key_t
        /// from map_t
        template < typename map_t,
                 typename key_t >
        struct value_of_t_
        {
            template<typename type_t>
            using predicate_ =
                std::is_same<key_t, first_t<type_t>>;

            using type =
                second_t<find_one_if_t<map_t, as_r_<predicate_>>>;
        };


        /// t_ shortcut for value_of_t_
        template < typename map_t,
                 typename key_t >
        using value_of_t =
            defer_t<value_of_t_, map_t, key_t>;


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


        /// A meta function that
        /// returns the composition
        /// of other several meta
        /// functions funcs_t
        template<typename ... funcs_t>
        struct compose_r_;


        /// Specialisation for
        /// compose that takes
        /// a single meta function
        template<typename func_t>
        struct compose_r_<func_t>
        {
            template<typename ... args_t>
            using return_ =
                r_<func_t, args_t...>;
        };


        /// Specialisation for
        /// compose that take
        /// more one meta functions
        template < typename func_t,
                 typename ... funcs_t >
        struct compose_r_<func_t, funcs_t...>
        {
            template<typename ... args_t>
            using return_ =
                r_ < func_t,
                r_ < compose_r_<funcs_t...>,
                args_t... > >;
        };


        /// Evaluates the result of
        /// private_::compose<funcs_t...>
        template<typename ... funcs_t>
        using compose_r =
            compose_r_<funcs_t...>;


        /// A meta function
        /// that always returns
        /// the type_t itself
        template<typename type_t>
        struct always_r_
        {
            template<typename ...>
            using return_ = type_t;
        };


        /// r_ shortcut always_r_
        template < typename type_t,
                 typename ... args_t >
        using always_r =
            r_<always_r_<type_t>, args_t...>;


        /// Evaluates the args_t
        /// and returns always
        /// the type void
        template<typename ... args_t>
        using void_r =
            always_r<void, args_t...>;


        /// Returns type_t only_if
        /// predicate_t<type_t> returns
        /// true_type, else returns nil
        template < typename type_t,
                 typename predicate_t >
        struct always_if_t_
        {
            using type =
                if_t<r_<predicate_t, type_t>, type_t, nil>;
        };


        /// t_ shortcut for
        /// always_if_t_
        template < typename type_t,
                 typename predicate_t >
        using always_if_t =
            defer_t<always_if_t_, type_t, predicate_t>;


        /// Determines if a
        /// type_t has the
        /// 'type' member
        template < typename ,
                 typename = void >
        struct has_type_t_:
                std::false_type
        {
        };


        /// Specialisation for
        /// has_type_ if type_t
        /// has 'type' member
        template<typename type_t>
        struct has_type_t_ < type_t,
                void_r<typename type_t::type> > :
                std::true_type
        {
        };


        /// Evaluates the result
        /// of t_<has_type_<type_t>>
        template<typename type_t>
        using has_type_t =
            defer_t<has_type_t_, type_t>;


        /// Determines if a
        /// type has a return_
        /// member
        template < typename,
                 typename = void >
        struct has_return_t_
        {
            using type =
                std::false_type;
        };


        /// Specialisation for
        /// has_return_ if
        /// type_t has return_
        template <typename type_t>
        struct has_return_t_ < type_t,
                void_r < typename
                type_t::template return_<> > >
        {
            using type =
                std::true_type;
        };


        /// Evaluates the result
        /// of t_<has_return_<type_t>>
        template<typename type_t>
        using has_return_t =
            defer_t<has_return_t_, type_t>;


        /// Determines if type_t
        /// is a meta function
        /// or not.
        template<typename type_t>
        using is_meta_function_t =
            has_return_t<type_t>;


        /// Meta function that
        /// binds the front_args_t...
        /// at the beginning of
        /// the parameters of the
        /// meta function func_t
        template < typename func_t,
                 typename... front_args_t >
        struct bind_front_r_
        {
            template<typename ... args_t>
            using return_ =
                r_ < func_t,
                front_args_t...,
                args_t... >;
        };


        /// Metafunction that
        /// binds the back_args_t...
        /// at the ending of
        /// the parameters of the
        /// meta function func_t
        template < typename func_t,
                 typename ... back_args_t >
        struct bind_back_r_
        {
            template<typename ... args_t>
            using return_ =
                r_ < func_t,
                args_t...,
                back_args_t... >;
        };


        /// Meta function that
        /// expands the list
        /// into func_t meta
        /// function parameters packs
        template < typename func_t,
                 typename list_t >
        struct expand_t_;


        /// Specialisation for
        /// expand that unpacks
        /// list_t into args_t...
        template < typename func_t,
                 template<typename ...> typename list_t,
                 typename ... args_t >
        struct expand_t_ < func_t,
                list_t <args_t... >>
        {
            using type =
                r_<func_t, args_t...>;
        };



        /// Evaluates the result of
        /// t_<private_::expand<func_t, list_t>>
        template < typename func_t,
                 typename list_t >
        using expand_t =
            defer_t <expand_t_, func_t, list_t>;


        /// ////////////////// ///
        /// Iteration features ///
        /// ////////////////// ///


        /// Accumulates res_t over list_t
        /// the meta function func_t
        /// that must take two
        /// parameters res_t and
        /// current type_t of list_t
        /// and finally returns the
        /// result res_t
        template < typename list_t,
                 typename res_t,
                 typename func_t >
        struct accumulate_t_;


        /// Specialisation for
        /// accumulate that takes
        /// an empty list as first
        /// parameter. It returns
        /// res_t itself. So this
        /// has no effect on the
        /// result.
        template < typename res_t,
                 typename func_t >
        struct accumulate_t_<list<>, res_t, func_t>
        {
            using type =
                res_t;
        };


        /// Specialisation for
        /// accumulate that takes
        /// a list with one or more
        /// types and inherits from
        /// the next step of the
        /// accumulation on res_t
        template < typename type_t,
                 typename ... types_t,
                 typename res_t,
                 typename func_t >
        struct accumulate_t_ <list<type_t, types_t...>, res_t, func_t> :
                accumulate_t_ <list<types_t...>, r_<func_t, res_t, type_t>, func_t>
        {
        };


        /// Evaluates the result
        /// of t_<accumulate<list_t, res_t, func_t>>
        template < typename list_t,
                 typename res_t,
                 typename func_t >
        using accumulate_t =
            defer_t < accumulate_t_ ,
            list_t, res_t, func_t >;


        /// Iterates a meta
        /// function over each
        /// element of a list
        /// and return the new list
        template < typename list_t,
                 typename func_t >
        struct iterate_t_;


        /// Specialisation for
        /// iterate_t_ that
        /// distings elements
        /// of list_t
        template < typename ... types_t,
                 typename func_t >
        struct iterate_t_<list<types_t...>, func_t>
        {
            using type =
                list<r_<func_t, types_t>...>;
        };


        /// t_ shortcut
        /// for iterate_t_
        template < typename list_t,
                 typename func_t >
        using iterate_t =
            defer_t<iterate_t_, list_t, func_t>;


        /// Meta function that
        /// add type_t to list_t
        /// if r_<predicate_t, type_t>
        /// returns true. Else it
        /// returns list_t itself
        template<typename predicate_t>
        struct filter_r_
        {
            template < typename list_t,
                     typename type_t >
            using return_ =
                select_t <
                r_<predicate_t, type_t>,
                push_back_t<type_t, list_t>,
                list_t >;
        };


        /// Evaluates the result
        /// of accumulate < list_t, list<>,
        /// private_::filter<predicate_t >>;
        template < typename list_t,
                 typename predicate_t >
        using filter_t =
            defer_t < accumulate_t ,  list_t, list<>,
            filter_r_<predicate_t >>;


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
            defer_t<map_replace_t_, list_t, map_t>;


        /// placeholders
        template<unsigned _u>
        struct placeholder;

        using _0_ = placeholder<0>;
        using _1_ = placeholder<1>;
        using _2_ = placeholder<2>;
        using _3_ = placeholder<3>;
        using _4_ = placeholder<4>;
        using _5_ = placeholder<5>;
        using _6_ = placeholder<6>;
        using _7_ = placeholder<7>;
        using _8_ = placeholder<8>;
        using _9_ = placeholder<9>;
        using _10_ = placeholder<10>;
        using _11_ = placeholder<11>;
        using _12_ = placeholder<12>;
        using _13_ = placeholder<13>;
        using _14_ = placeholder<14>;


        /// A lambda is a anonymous
        /// meta function that can
        /// support placeholding
        /// feature between lambda
        /// arguments and meta function
        /// func_t arguments
        template < typename lambda_args_t,
                 typename func_t ,
                 typename func_args_t >
        struct lambda;


        /// Specialisation for
        /// lambda that distings
        /// each type of lambda_args_t
        /// and of func_args_t
        template < typename ... lambda_args_t,
                 typename func_t,
                 typename ... func_args_t >
        struct lambda < list<lambda_args_t...>,
                func_t, list<func_args_t... >>
        {
            using lambda_args_ =
                list<lambda_args_t...>;
            using func_args_ =
                list<func_args_t...>;

            template<typename ... args_t>
            using return_ =
                expand_t<func_t, map_replace_t<func_args_, to_map_t<lambda_args_, list<args_t...>>>>;
        };


        /// ////////////// ///
        /// States Algebra ///
        /// ////////////// ///


        /// A state help to
        /// partial/fully specialize
        /// template class.
        /// If a given type_t
        /// statisfies a particular
        /// state, so the specialization
        /// a of template is automatically
        /// used for this state.
        /// USe of state member
        /// instead of type member
        /// is only semantics.


        /// Access to state member
        /// of type_t
        template < typename state_t,
                 typename ... type_t >
        using state_ =
            typename state_t::
            template state<type_t...>;


        /// Access to state member
        /// of type_t
        template < typename state_t,
                 typename ... type_t >
        using s_ =
            state_<state_t, type_t...>;


        /// Transforms a func_t
        /// base on type member
        /// to a state base on
        /// state parametric member
        template<template<typename...> typename func_t>
        struct as_s_
        {
            template<typename... arg_t>
            using state =
                defer_t<func_t, arg_t...>;
        };


        /// Returns the result
        /// s_<as_s_<func_t>, arg_t>
        template < template<typename...> typename func_t,
                 typename ... arg_t >
        using as_s =
            s_<as_s_<func_t>, arg_t...>;


        /// State that means
        /// the compiler is
        /// used an invalid
        /// implementation
        struct invalid_state
        {
            template<typename ... type_t>
            using state =
                invalid_state;
        };


        /// Returns true_type if
        /// the state_t is not
        /// invalid_state
        template <typename state_t>
        using is_valid_state_t =
            not_t<std::is_same<state_t, invalid_state>>;



        /// Translation of
        /// true_type to
        /// true_state
        struct true_state
        {
            template<typename...>
            using state =
                std::true_type;
        };


        /// Translation of
        /// false_type to
        /// false_state
        struct false_state
        {
            template<typename...>
            using state =
                std::false_type;
        };


        /// Returns true_type
        /// if the size of the
        /// list is one
        template<typename list_t>
        using is_single_t =
            bool_t<size_<list_t> == 1>;


        /// Resolves wich state
        /// will be selected
        template<typename states_t>
        struct select_s_;


        /// Specialization that
        /// distings the elements
        /// of the states_t list
        template<typename ... states_t>
        struct select_s_<list<states_t...>>
        {
            /// Returns the only
            /// state that is valid
            /// for the type_t
            template<typename... type_t>
            using state =
                front_t < always_if_t < filter_t < list<s_<states_t, type_t...>...>,
                as_r_<is_valid_state_t >> , as_r_<is_single_t >>> ;
        };


        /// /////////////////// ///
        /// Compile time string ///
        /// /////////////////// ///


        /// Compile time string
        /// definition
        template<typename char_t>
        class basic_string
        {
            private:
                /// Inner value
                const char_t* const m_value;


                /// Size of the m_value
                const std::size_t m_size;


            public:
                /// Constructor taking
                /// a literal string
                template<std::size_t N>
                constexpr basic_string(
                    const char_t(&a)[N]) :
                    m_value(a),
                    m_size(N - 1)
                {
                }

                /// Overload of
                /// operator[]
                constexpr char_t operator[](
                    std::size_t n)
                {
                    return n < m_size ?
                           m_value[n] :
                           throw std::out_of_range("");
                }


                /// Returns the size
                /// of m_value;
                constexpr std::size_t size()
                {
                    return m_size;
                }


                /// Returns the
                /// m_value pointer
                constexpr const char_t * const get() const
                {
                    return m_value;
                }
        };


        /// String alias for
        /// basic_string<char>
        using string =
            basic_string<char>;


        /// WString alias for
        /// basic_string<wchar_t>
        using wstring =
            basic_string<wchar_t>;


        /// WString alias for
        /// basic_string<char16_t>
        using u16string	 =
            basic_string<char16_t>;


        /// WString alias for
        /// basic_string<char32_t>
        using u32string =
            basic_string<char32_t>;


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
            defer_t<has_difference_type_t_, type_t>;


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
            defer_t<has_pointer_t_, type_t>;


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
            defer_t<has_reference_t_, type_t>;


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
            defer_t<has_iterator_category_t_, type_t>;


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
            defer_t<has_value_type_t_, type_t>;



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
            defer_t<has_begin_method_t_, type_t>;


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
            defer_t<has_end_method_t_, type_t>;


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
            defer_t<repeat_t, unsigned_t<_nb>, type_t>;


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
            defer_t<replace_t_, list_t, old_t, new_t>;


        template<typename ... types_t>
        struct inherit:
            public types_t ...
        {
        };






    }
}


#endif
