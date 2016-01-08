#ifndef __BRAIN_META_STATE_HPP__
# define  __BRAIN_META_STATE_HPP__

namespace brain
{
    namespace meta
    {
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
                lazy_t<func_t, arg_t...>;
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
            equal_to_t<int_t<size_<list_t>>, int_t<1>>;


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
                front_t < if_t < as_r_<is_single_t>,
                filter_t < list<s_<states_t, type_t...>...>,
                as_r_<is_valid_state_t >>> > ;
        };
    }
}

#endif
