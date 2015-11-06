#ifndef __META_BRAIN_HPP
#define __META_BRAIN_HPP

#include <type_traits>
namespace brain
{
    /// This library contains tow main principles :
    ///  - list<types_t...>
    ///  - meta function return_<>;
    ///
    /// The public metas functions (with return_)
    /// will present in ft namespace
    /// The private private_ementations of all will be
    /// present in private_ namespace.
    /// For all struct / using that returns 'type'
    /// an '_' will be added to end of its name.
    /// For all using that encapsulate t_<type_t>
    /// '_t' will be added to its name.
    /// For all using / struct that represents
    /// only alias for a private_ implementation
    /// the '_' will be removed from the original
    /// name.
    namespace meta
    {
        /// //////////////////////////////////// ///
        /// Shortcut for access template members ///
        /// //////////////////////////////////// ///


        /// Access to type member
        /// of type_t
        template<typename type_t>
        using t_ =
            typename type_t::type;


        /// Access to value member
        /// of type_t
        template<typename type_t>
        constexpr decltype(t_<type_t>::value) v_ =
            t_<type_t>::value;


        /// Access to value_type member
        /// of type_t
        template<typename type_t>
        using vt_ =
            decltype(v_<type_t>);


        /// Access to size member
        /// of type_t
        template<typename type_t>
        constexpr decltype(t_<type_t>::size) size_ =
            t_<type_t>::size;


        /// Access to return_ member
        /// of type_t
        template < typename type_t,
                 typename ... args_t >
        using return_ =
            typename type_t::
            template return_<args_t...>;


        /// Shortcut for return_
        template < typename type_t,
                 typename ... args_t >
        using r_ =
            return_<type_t, args_t...>;


        /// ///////////////////////// ///
        /// Wrapper for literal types ///
        /// ///////////////////////// ///


        /// Shortcut for
        /// std::integral_constant
        template < typename literal_t,
                 literal_t _l >
        using igral_ =
            std::integral_constant<literal_t, _l>;


        /// Wrapper for bool
        template<bool _b>
        using bool_ =
            igral_<bool, _b>;


        /// Wrapper for short
        template<short _s>
        using short_ =
            igral_<short, _s>;


        /// Wrapper for unsigned short
        template<unsigned short _us>
        using ushort_ =
            igral_<unsigned short, _us>;


        /// Wrapper for char
        template<char _c>
        using char_ =
            igral_<char, _c>;


        /// Wrapper for int
        template<int _i>
        using int_ =
            igral_<int, _i>;


        /// Wrapper for long
        template<long _l>
        using long_ =
            igral_<long, _l>;


        /// Wrapper for long long
        template<long long _ll>
        using longlong_ =
            igral_<long long, _ll>;


        /// Wrapper for unsigned
        template<unsigned _u>
        using unsigned_ =
            igral_<unsigned, _u>;


        /// Wrapper for unsigned long
        template<unsigned long _ul>
        using unsignedl_ =
            igral_<unsigned long, _ul>;


        /// Wrapper for unsigned long long
        template<unsigned long long _ull>
        using unsignedll_ =
            igral_<unsigned long long, _ull>;


        /// Wrapper for size_t
        template<std::size_t _s>
        using size_t_ =
            igral_<std::size_t, _s>;


        /// ////////////////////////////// ///
        /// Wrapper for constness keywords ///
        /// ////////////////////////////// ///


        /// Wrapper for sizeof
        template<typename type_t>
        using sizeof_ =
            size_t_<sizeof(type_t)>;


        /// Wrapper for sizeof...
        template<typename ... types_t>
        using sizeof_pack_ =
            size_t_<sizeof...(types_t)>;


        /// Wrapper for alignof
        template<typename type_t>
        using alignof_ =
            size_t_<alignof(type_t)>;


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
                v_<sizeof_pack_<types_t...>>;
        };


        /// Returns bool_<true>
        /// if list_t is empty_
        template<typename list_t>
        using empty_ =
            bool_<size_<list_t>>;


        /// t_ shortcut for empty_
        template<typename list_t>
        using empty_t =
            t_<empty_<list_t>>;


        namespace private_
        {
            /// Returns first type
            /// of list_t
            template<typename list_t>
            struct front_;


            /// Specialisation of
            /// front_ that identifies
            /// the head_t of list_t
            template < typename head_t,
                     typename ... types_t >
            struct front_<list<head_t, types_t...>>
            {
                using type = head_t;
            };
        }


        /// Evaluates t_<front_<list_t>>
        template<typename list_t>
        using front_t =
            t_<private_::front_<list_t>>;


        namespace private_
        {
            /// Private private_ementation
            /// of back_ template
            template<typename ... types_t>
            struct back_;


            /// Private private_ementation
            /// of back_
            template<typename type_t>
            struct back_<type_t>
            {
                using type = type_t;
            };


            /// Private private_ementation
            /// of back_ template
            template < typename type_t,
                     typename ... types_t >
            struct back_<type_t, types_t...>
            {
                using type = t_<back_<types_t...>>;
            };


            /// private_ementation for
            /// back_ in case of list
            template<typename ... types_t>
            struct back_<list<types_t...>>
            {
                using type = t_<back_<types_t...>>;
            };
        }


        /// Evaluates the result of
        /// t_<private_::back_<list_t>>
        template<typename list_t>
        using back_t =
            t_<private_::back_<list_t>>;


        namespace private_
        {
            /// Push a type_t at
            /// back of list_t
            template < typename type_t,
                     typename list_t >
            struct push_back_ {};


            /// Specialisation for
            /// push_back_ to expand
            /// types_t pack parameters
            template < typename type_t,
                     typename ... types_t >
            struct push_back_<type_t, list<types_t...>>
            {
                using type = list<types_t..., type_t>;
            };
        }

        /// Evaluates the result
        /// of t_<push_back_<type_t, list_t>>
        template < typename type_t,
                 typename list_t >
        using push_back_t =
            t_<private_::push_back_<type_t, list_t>>;


        namespace private_
        {
            /// Pushs a type_t at
            /// front_ of list_t
            template < typename type_t,
                     typename list_t >
            struct push_front_;


            /// Specialisation for
            /// push_front_ to expand
            /// types_t pack parameters
            template < typename type_t,
                     typename ... types_t >
            struct push_front_<type_t, list<types_t...>>
            {
                using type = list<type_t, types_t...>;
            };
        }


        /// Evaluates the result
        /// of t_<push_front_<type_t, list_t>>
        template < typename type_t,
                 typename list_t >
        using push_front_t =
            t_<private_::push_front_<type_t, list_t>>;


        namespace private_
        {
            /// Removes the first
            /// type of list_t
            template<typename list_t>
            struct pop_front_;


            /// Specialisation for
            /// pop_front_ that identifies
            /// and removes the first
            /// type
            template < typename first_t,
                     typename ... types_t >
            struct pop_front_<list<first_t, types_t...>>
            {
                using type = list<types_t...>;
            };
        }


        /// Evaluates the result
        /// of t_<pop_front_<list_t>>
        template<typename list_t>
        using pop_front_t =
            t_<private_::pop_front_<list_t>>;


        namespace private_
        {
            /// Concatenates all lists_t
            /// into a single list
            template <typename... lists_t>
            struct concat_;


            /// Specialisation for
            /// concat_ that takes no
            /// list and return an
            /// empty_ list.
            template <>
            struct concat_<>
            {
                using type = list<>;
            };


            /// Specialisation for
            /// concat_ that takes
            /// only one list and
            /// returns the same list
            template <typename... types_t>
            struct concat_<list<types_t...>>
            {
                using type = list<types_t...>;
            };


            /// Specialisation for
            /// concat_ that takes
            /// two lists and returns
            /// the concatenated list
            template < typename... types1_t,
                     typename... types2_t >
            struct concat_ <
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
            struct concat_ <
                    list<types1_t...>,
                    list<types2_t...>,
                    others_t... >

            {
                using type = t_<concat_<list<types1_t..., types2_t...>, others_t...>>;
            };
        }


        /// Evaluates the result
        /// of t_<concat_<lists_t...>>
        template <typename... lists_t>
        using concat_t =
            t_<private_::concat_<lists_t...>>;


        namespace private_
        {
            /// Removes the last
            /// type of list_t
            template<typename list_t>
            struct pop_back_;


            ///
            template<typename type_t>
            struct pop_back_<list<type_t>>
            {
                using type = list<>;
            };


            ///
            template < typename type_t,
                     typename ... types_t >
            struct pop_back_<list<type_t, types_t...>>
            {
                using type = concat_t < list<type_t>,
                      t_<pop_back_<list<types_t...>> >>;
            };
        }


        /// Evaluates the result
        /// of t_<pop_back_<list_t>>
        template<typename list_t>
        using pop_back_t =
            t_<private_::pop_back_<list_t>>;


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


        namespace private_
        {
            /// A meta function that
            /// returns the composition
            /// of other several meta
            /// functions funcs_t
            template<typename ... funcs_t>
            struct compose;


            /// Specialisation for
            /// compose that takes
            /// a single meta function
            template<typename func_t>
            struct compose<func_t>
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
            struct compose<func_t, funcs_t...>
            {
                template<typename ... args_t>
                using return_ =
                    r_ < func_t,
                    r_ < compose<funcs_t...>,
                    args_t... > >;
            };
        }


        /// Evaluates the result of
        /// private_::compose<funcs_t...>
        template<typename ... funcs_t>
        using compose =
            private_::compose<funcs_t...>;


        /// A meta function
        /// that always returns
        /// the type_t itself
        template<typename type_t>
        struct always
        {
            template<typename ... args_t>
            using return_ = type_t;
        };


        /// Evaluates the args_t
        /// and returns always
        /// the type void
        template<typename ... args_t>
        using void_ = r_ <
                      always<void>,
                      args_t... >;


        namespace private_
        {
            /// Determines if a
            /// type_t has the
            /// 'type' member
            template < typename ,
                     typename = void >
            struct has_type:
                    std::false_type
            {
            };


            /// Specialisation for
            /// has_type_ if type_t
            /// has 'type' member
            template<typename type_t>
            struct has_type < type_t,
                    void_<typename type_t::type> > :
                    std::true_type
            {
            };
        }

        /// Evaluates the result
        /// of t_<has_type_<type_t>>
        template<typename type_t>
        using has_type =
            private_::has_type<type_t>;


        namespace private_
        {
            /// Determines if a
            /// type has a return_
            /// member
            template < typename,
                     typename = void >
            struct has_return
            {
                using type = std::false_type;
            };


            /// Specialisation for
            /// has_return_ if
            /// type_t has return_
            template <typename type_t>
            struct has_return < type_t,
                    void_ < typename
                    type_t::template return_<> > >
            {
                using type = std::true_type;
            };
        }

        /// Evaluates the result
        /// of t_<has_return_<type_t>>
        template<typename type_t>
        using has_return =
            t_<private_::has_return<type_t>>;


        /// Determines if type_t
        /// is a meta function
        /// or not.
        template<typename type_t>
        using is_meta_function =
            has_return<type_t>;


        /// Meta function that
        /// binds the front_args_t...
        /// at the beginning of
        /// the parameters of the
        /// meta function func_t
        template < typename func_t,
                 typename... front_args_t >
        struct bind_front
        {
            template<typename ... args_t>
            using return_ = return_ <
                            func_t,
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
        struct bind_back
        {
            template<typename ... args_t>
            using return_ = return_ <
                            func_t,
                            args_t...,
                            back_args_t... >;
        };


        namespace private_
        {
            /// Meta function that
            /// expands the list
            /// into func_t meta
            /// function parameters packs
            template < typename func_t,
                     typename list_t >
            struct expand;


            /// Specialisation for
            /// expand that unpacks
            /// list_t into args_t...
            template < typename func_t,
                     template<typename ...> typename list_t,
                     typename ... args_t >
            struct expand < func_t,
                    list_t <args_t... >>
            {
                using type = return_<func_t, args_t...>;
            };
        }


        /// Evaluates the result of
        /// t_<private_::expand<func_t, list_t>>
        template < typename func_t,
                 typename list_t >
        using expand =
            t_<private_::expand<func_t, list_t>>;


        /// //////////////////////////// ///
        /// Type instanciation deferring ///
        /// //////////////////////////// ///


        /// Defers the instation of
        /// a template
        template < template<typename ...> typename func_t,
                 typename ... args_t >
        struct defer :
                func_t<args_t...>
        {
        };



        /// //////////////////////// ///
        /// Meta function conversion ///
        /// //////////////////////// ///

        /// Transforms type_t into
        /// a meta function
        template <template<typename...> typename type_t>
        struct quote
        {
            template<typename ... args_t>
            using return_ =
                type_t<args_t...>;
        };


        /// TODO Documentation curry
        // template < typename func_t,
        //         typename args_t = quote<list >>
        // using curry =
        //    compose<func_t, args_t>;


        /// TODO Documentation uncurry
        // template <typename F>
        // using uncurry =
        //    bind_front<quote<apply_list>, F>;



        /// ///////////////////////////// ///
        /// Mathematical wrapper features ///
        /// ///////////////////////////// ///


        /// Wrapper for incrementing
        template<typename type_t>
        using inc =
            igral_ <
            decltype(v_<type_t> + 1),
            v_<type_t> + 1 >;


        /// Wrapper for decrementing
        template<typename type_t>
        using dec =
            igral_ <
            decltype(v_<type_t> - 1),
            v_<type_t> - 1 >;


        /// Wrapper for additing
        template < typename type_t,
                 typename other_t >
        using plus =
            igral_ <
            decltype(v_<type_t> + v_<other_t>),
            v_<type_t> + v_<other_t >>;


        /// Wrapper for substracting
        template < typename type_t,
                 typename other_t >
        using minus =
            igral_ <
            decltype(v_<type_t> - v_<other_t>),
            v_<type_t> - v_<other_t >>;


        /// Wrapper for multiplying
        template < typename type_t,
                 typename other_t >
        using multiplies =
            igral_ <
            decltype(v_<type_t> * v_<other_t>),
            v_<type_t> * v_<other_t >>;


        /// Wrapper for dividing
        template < typename type_t,
                 typename other_t >
        using divides =
            igral_ <
            decltype(v_<type_t> / v_<other_t>),
            v_<type_t> / v_<other_t >>;


        /// Wrapper for negating
        template <typename type_t>
        using negate =
            igral_ <
            decltype(-v_<type_t>),
            -v_<type_t >>;


        /// Wrapper for moduling
        template < typename type_t,
                 typename other_t >
        using modulus =
            igral_ <
            decltype(v_<type_t> % v_<other_t>),
            v_<type_t> % v_<other_t >>;


        /// /////////////////////// ///
        /// Logical wrapper feature ///
        /// /////////////////////// ///


        /// Wrapper for equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using equal_to =
            bool_ < v_<type_t>
            == v_<other_t >>;


        /// Wrapper for not equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using not_equal_to =
            bool_ < v_<type_t>
            != v_<other_t >>;


        /// Wrapper for greater
        /// operator
        template < typename type_t,
                 typename other_t >
        using greater =
            bool_ < (v_<type_t>
                     > v_<other_t>) >;


        /// Wrapper for less
        /// operator
        template < typename type_t,
                 typename other_t >
        using less =
            bool_ < (v_<type_t>
                     < v_<other_t>) >;


        /// Wrapper for greater equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using greater_equal =
            bool_ < (v_<type_t>
                     >= v_<other_t>) >;


        /// Wrapper for less equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using less_equal =
            bool_ < (v_<type_t>
                     <= v_<other_t>) >;


        /// Wrapper for bit and
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_and =
            bool_ < v_<type_t>
            & v_<other_t >>;


        /// Wrapper for bit or
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_or =
            bool_ < v_<type_t>
            | v_<other_t >>;


        /// Wrapper for bit xor
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_xor =
            bool_ < v_<type_t>
            ^ v_<other_t >>;


        /// Wrapper for bit not
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_not =
            bool_ < ~v_<type_t >>;


        /// ////////////// ///
        /// Type selection ///
        /// ////////////// ///


        namespace private_
        {
            /// Type selector
            template<typename ...>
            struct if_;


            /// Type selector
            /// specialisation that
            /// returns void
            /// if_t is true
            template<typename if_t>
            struct if_<if_t> :
                    std::enable_if<v_<if_t>>
            {
            };


            /// Type selector
            /// specialisation that
            /// returns then_t
            /// if_t is true
            template < typename if_t,
                     typename then_t >
            struct if_<if_t, then_t>:
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
            struct if_<if_t, then_t, else_t>:
                    std::conditional<v_<if_t>, then_t, else_t>
            {
            };
        }

        /// Evaluates the result
        /// of t_<_if_<args_t...>>
        template<typename ... args_t>
        using if_ =
            t_<private_::if_<args_t...>>;


        /// Evaluates the result
        /// of if_<bool_<_b>, args_t... >
        template < bool _b,
                 typename... args_t >
        using if_c =
            t_<private_::if_<bool_<_b>, args_t...>>;


        /// Evaluates the result
        /// of if_<if_t, then_t, else_t>
        template < typename if_t,
                 typename then_t,
                 typename else_t >
        using select =
            if_<if_t, then_t, else_t> ;


        /// Evaluates the result
        /// of if_c<_b, then_t, else_t>
        template < bool _b,
                 typename then_t,
                 typename else_t >
        using select_c =
            if_c<_b, then_t, else_t> ;


        namespace private_
        {
            /// Returns std::true_type
            /// if all bools_t are true
            template <typename... bools_t>
            struct and_;


            /// Specialisation for
            /// _and_ that returns
            /// std::true_type for
            /// default case.
            template <>
            struct and_<> :
                    std::true_type
            {
            };


            /// Specialisation for
            /// and_ that returns
            /// std::false_type if
            /// one of bools_t is
            /// false
            template < typename bool_t,
                     typename... bools_t >
            struct and_<bool_t, bools_t...>:
                    if_c < !v_<bool_t>, std::false_type, and_<bools_t... >>
            {
            };
        }

        /// Evaluates the result
        /// of t_<_and_<bools_t...>>
        template<typename ... bools_t>
        using and_ =
            t_<private_::and_<bools_t...>>;

        namespace private_
        {
            /// Returns std::true_type
            /// if one or more bools_t
            /// is true
            template <typename... bools_t>
            struct or_;


            /// Specialisation for
            /// _or_ that returns
            /// std::false_type
            /// for default case
            template <>
            struct or_<> :
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
            struct or_<bool_t, bools_t...> :
                    if_c < v_<bool_t>,
                    std::true_type,
                    or_<bools_t... >>
            {
            };
        }

        /// Evaluates the result
        /// of t_<_or_<bools_t...>>
        template<typename ... bools_t>
        using or_ =
            t_<private_::or_<bools_t...>>;


        /// Negates the bool_t
        template<typename bool_t>
        using not_ =
            bool_ < !v_<bool_t >>;


        /// ////////////////// ///
        /// Iteration features ///
        /// ////////////////// ///


        namespace private_
        {
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
            struct accumulate
            {
            };


            /// Specialisation for
            /// accumulate that takes
            /// an empty_ list as first
            /// parameter. It returns
            /// res_t itself. So this
            /// has no effect on the
            /// result.
            template < typename res_t,
                     typename func_t >
            struct accumulate<list<>, res_t, func_t>
            {
                using type = res_t;
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
            struct accumulate <list<type_t, types_t...>, res_t, func_t> :
                    accumulate <list<types_t...>, r_<func_t, res_t, type_t>, func_t>
            {
            };
        }


        /// Evaluates the result
        /// of t_<private_::accumulate<list_t, res_t, func_t>>
        template < typename list_t,
                 typename res_t,
                 typename func_t >
        using accumulate =
            t_ < private_::accumulate <
            list_t, res_t, func_t >>;


        namespace private_
        {
            /// Meta function that
            /// add type_t to list_t
            /// if r_<predicate_t, type_t>
            /// returns true. Else it
            /// returns list_t itself
            template<typename predicate_t>
            struct filter
            {
                template < typename list_t,
                         typename type_t >
                using return_ =
                    select <
                    r_<predicate_t, type_t>,
                    push_back_t<type_t, list_t>,
                    list_t >;
            };
        }


        /// Evaluates the result
        /// of accumulate < list_t, list<>,
        /// private_::filter<predicate_t >>;
        template < typename list_t,
                 typename predicate_t >
        using filter =
            meta::accumulate < list_t, list<>,
            private_::filter<predicate_t >>;
    }

}


#endif
