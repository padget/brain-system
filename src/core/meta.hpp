#ifndef __META_BRAIN_HPP
#define __META_BRAIN_HPP

namespace brain
{
    /// TODO Documenter le namespace meta
    /// Respet de la norme struct XXX{ using type = yyy; static constexpr auto value = zzz;}
    namespace meta
    {
        /// //////////////////////////////////// ///
        /// Shortcut for access template members ///
        /// //////////////////////////////////// ///
        namespace member
        {
            /// Access to type member
            /// of type_t
            template<typename type_t>
            using t_ =
                typename type_t::type;


            /// Access to value member
            /// of type_t
            template<typename type_t>
            constexpr auto v_ =
                t_<type_t>::value;


            /// Access to value_type member
            /// of type_t
            template<typename type_t>
            using vt_ =
                typename t_<type_t>::value_type;


            /// Access to size member
            /// of type_t
            template<typename type_t>
            constexpr auto size_ =
                t_<type_t>::size;


            /// Access to return_ member
            /// of type_t
            template < typename type_t,
                     typename ... args_t >
            using return_ =
                typename type_t::
                template return_<args_t...>;
        }


        /// Shortcut for member::t_
        template<typename type_t>
        using t_ =
            member::t_<type_t>;


        /// Shortcut for member::v_
        template<typename type_t>
        constexpr auto v_ =
            member::v_<type_t>;


        /// Shortcut for member::vt_
        template<typename type_t>
        using vt_ =
            member::vt_<type_t>;


        /// Shortcut for member::size_
        template<typename type_t>
        constexpr auto size_ =
            member::size_<type_t>;


        /// Shortcut for member::return_
        template < typename type_t,
                 typename ... args_t >
        using return_ =
            member::return_ <
            type_t, args_t... >;


        /// Shortcut for return_
        template < typename type_t,
                 typename ... args_t >
        using r_ =
            return_<type_t, args_t...>;


        /// ///////////////////////// ///
        /// Wrapper for literal types ///
        /// ///////////////////////// ///
        namespace literal
        {
            /// Shortcut for
            /// std::integral_constant
            template < typename literal_t,
                     literal_t _l >
            using igral =
                std::integral_constant<literal_t, _l>;


            /// Wrapper for bool
            template<bool _b>
            using bool_ =
                igral<bool, _b>;


            /// Wrapper for short
            template<short _s>
            using short_ =
                igral<short, _s>;


            /// Wrapper for unsigned short
            template<unsigned short _us>
            using ushort_ =
                igral<unsigned short, _us>;


            /// Wrapper for char
            template<char _c>
            using char_ =
                igral<char, _c>;


            /// Wrapper for int
            template<int _i>
            using int_ =
                igral<int, _i>;


            /// Wrapper for long
            template<long _l>
            using long_ =
                igral<long, _l>;


            /// Wrapper for long long
            template<long long _ll>
            using longlong_ =
                igral<long long, _ll>;


            /// Wrapper for unsigned
            template<unsigned _u>
            using unsigned_ =
                igral<unsigned, _u>;


            /// Wrapper for unsigned long
            template<unsigned long _ul>
            using unsignedl_ =
                igral<unsigned long, _ul>;


            /// Wrapper for unsigned long long
            template<unsigned long long _ull>
            using unsignedll_ =
                igral<unsigned long long, _ull>;


            /// Wrapper for size_t
            template<std::size_t _s>
            using size_t_ =
                igral<std::size_t, _s>;
        }


        /// Shortcut for
        /// literal::bool_
        template<bool _b>
        using bool_ =
            literal::bool_<_b>;


        /// Shortcut for
        /// literal::short_
        template<short _s>
        using short_ =
            literal::short_<_s>;


        /// Shortcut for
        /// literal::ushort_
        template<unsigned short _us>
        using ushort_ =
            literal::ushort_<_us>;


        /// Shortcut for
        /// literal::char_
        template<char _c>
        using char_ =
            literal::char_<_c>;


        /// Shortcut for
        /// literal::int_
        template<int _i>
        using int_ =
            literal::int_<_i>;


        /// Shortcut for
        /// literal::long_
        template<long _l>
        using long_ =
            literal::long_<_l>;


        /// Shortcut for
        /// literal::longlong_
        template<long long _ll>
        using longlong_ =
            literal::longlong_<_ll>;


        /// Shortcut for
        /// literal::unsigned_
        template<unsigned _u>
        using unsigned_ =
            literal::unsigned_<_u>;


        /// Shortcut for
        /// literal::unsignedl_
        template<unsigned long _ul>
        using unsignedl_ =
            literal::unsignedl_<_ul>;


        /// Shortcut for
        /// literal::unsignedll_
        template<unsigned long long _ull>
        using unsignedll_ =
            literal::unsignedll_<_ull>;


        /// Shortcut for
        /// literal::size_t_
        template<std::size_t _s>
        using size_t_ =
            literal::size_t_<_s>;


        /// ////////////////////////////// ///
        /// Wrapper for constness keywords ///
        /// ////////////////////////////// ///
        namespace constkw
        {
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
        }


        /// Shortcut for
        /// constkw::sizeof_
        template<typename type_t>
        using sizeof_ =
            constkw::sizeof_<type_t>;


        /// Shortcut for
        /// constkw::sizeof_pack_
        template<typename ... types_t>
        using sizeof_pack_ =
            constkw::sizeof_pack_<types_t...>;


        /// Shortcut for
        /// constkw::alignof_
        template<typename type_t>
        using alignof_ =
            constkw::alignof_<type_t>;


        /// //////////////////////////////////////// ///
        /// Wrapper for parameters pack manipulation ///
        /// //////////////////////////////////////// ///
        namespace pack
        {
            /// Wrapper for a
            /// parameters pack.
            template<typename ... types_t>
            struct list
            {
                using type = list;
                static constexpr auto size =
                    v_<sizeof_pack_<types_t...>>;
            };


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


            /// Evaluates t_<front_<list_t>>
            template<typename list_t>
            using front =
                t_<front_<list_t>>;


            /// Returns last type
            /// of list_t
            template<typename list_t>
            struct back_;


            /// Specialisation of
            /// back_ that identifies
            /// the last_t of list_t
            template < typename last_t,
                     typename ... types_t >
            struct back_<list<types_t..., last_t>>
            {
                using type = last_t;
            };


            /// Evaluates t_<back_<list_t>>
            template<typename list_t>
            using back =
                t_<back_<list_t>>;
        }


        /// Shortuct for pack::list
        template<typename ... types_t>
        using list =
            pack::list<types_t...>;


        /// Shortcut for pack::front
        template<typename list_t>
        using front =
            pack::front<list_t>;


        /// Shortcut for pack::back
        template<typename list_t>
        using back =
            pack::back<list_t>;


        /// ///////////////////////////// ///
        /// Mathematical wrapper features ///
        /// ///////////////////////////// ///
        namespace math
        {
            /// Wrapper for incrementing
            template<typename type_t>
            using inc =
                literal::igral <
                decltype(v_<type_t> + 1),
                v_<type_t> + 1 >;


            /// Wrapper for decrementing
            template<typename type_t>
            using dec =
                literal::igral <
                decltype(v_<type_t> - 1),
                v_<type_t> - 1 >;


            /// Wrapper for additing
            template < typename type_t,
                     typename other_t >
            using plus =
                literal::igral <
                decltype(v_<type_t> + v_<other_t>),
                v_<type_t> + v_<other_t >>;


            /// Wrapper for substracting
            template < typename type_t,
                     typename other_t >
            using minus =
                literal::igral <
                decltype(v_<type_t> - v_<other_t>),
                v_<type_t> - v_<other_t >>;


            /// Wrapper for multiplying
            template < typename type_t,
                     typename other_t >
            using multiplies =
                literal::igral <
                decltype(v_<type_t> * v_<other_t>),
                v_<type_t> * v_<other_t >>;


            /// Wrapper for dividing
            template < typename type_t,
                     typename other_t >
            using divides =
                literal::igral <
                decltype(v_<type_t> / v_<other_t>),
                v_<type_t> / v_<other_t >>;


            /// Wrapper for negating
            template <typename type_t>
            using negate =
                literal::igral <
                decltype(-v_<type_t>),
                -v_<type_t >>;


            /// Wrapper for moduling
            template < typename type_t,
                     typename other_t >
            using modulus =
                literal::igral <
                decltype(v_<type_t> % v_<other_t>),
                v_<type_t> % v_<other_t >>;
        }


        /// Shortcut for math::inc
        template<typename type_t>
        using inc =
            math::inc<type_t>;


        /// Shortcut for math::dec
        template<typename type_t>
        using dec =
            math::dec<type_t>;


        /// Shortcut for math::plus
        template < typename type_t,
                 typename other_t >
        using plus =
            math::plus <
            type_t,
            other_t >;


        /// Shortcut for math::minus
        template < typename type_t,
                 typename other_t >
        using minus =
            math::minus <
            type_t,
            other_t >;


        /// Shortcut for math::multiplies
        template < typename type_t,
                 typename other_t >
        using multiplies =
            math::multiplies <
            type_t,
            other_t >;


        /// Shortcut for math::divides
        template < typename type_t,
                 typename other_t >
        using divides =
            math::divides <
            type_t,
            other_t >;


        /// Shortcut for math::negate
        template <typename type_t>
        using negate =
            math::negate<type_t>;


        /// Shortcut for math::modulus
        template < typename type_t,
                 typename other_t >
        using modulus =
            math::modulus <
            type_t,
            other_t >;


        /// /////////////////////// ///
        /// Logical wrapper feature ///
        /// /////////////////////// ///
        namespace logic
        {
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
        }


        /// Shortcut for
        /// logic::equal_to
        template < typename type_t,
                 typename other_t >
        using equal_to =
            logic::equal_to <
            type_t, other_t >;


        /// Shortcut for
        /// logic::not_equal_to
        template < typename type_t,
                 typename other_t >
        using not_equal_to =
            logic::not_equal_to <
            type_t, other_t >;


        /// Shortcut for
        /// logic::greater
        template < typename type_t,
                 typename other_t >
        using greater =
            logic::greater <
            type_t, other_t >;


        /// Shortcut for
        /// logic::equal_to
        template < typename type_t,
                 typename other_t >
        using less =
            logic::less <
            type_t, other_t >;


        /// Shortcut for
        /// logic::greater_equal
        template < typename type_t,
                 typename other_t >
        using greater_equal =
            logic::greater_equal <
            type_t, other_t >;


        /// Shortcut for
        /// logic::less_equal
        template < typename type_t,
                 typename other_t >
        using less_equal =
            logic::less_equal <
            type_t, other_t >;


        /// Shortcut for
        /// logic::bit_and
        template < typename type_t,
                 typename other_t >
        using bit_and =
            logic::bit_and <
            type_t, other_t >;


        /// Shortcut for
        /// logic::bit_or
        template < typename type_t,
                 typename other_t >
        using bit_or =
            logic::bit_or <
            type_t, other_t >;


        /// Shortcut for
        /// logic::bit_xor
        template < typename type_t,
                 typename other_t >
        using bit_xor =
            logic::bit_xor <
            type_t, other_t >;


        /// Shortcut for
        /// logic::bit_not
        template < typename type_t,
                 typename other_t >
        using bit_not =
            logic::bit_not <
            type_t, other_t >;



        /// ////////////////////////// ///
        /// Meta function manipulation ///
        /// ////////////////////////// ///
        namespace function
        {
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


            /// Meta function that
            /// expands the list
            /// into func_t meta
            /// function parameters packs
            template < typename,
                     typename >
            struct expand_;


            /// Specialisation for
            /// expand that unpacks
            /// list_t
            template < typename func_t,
                     template<typename ...> typename list_t,
                     typename ... args_t >
            struct expand_ <func_t, list_t<args_t...> >:
                    return_<func_t, args_t...>
            {
            };


            /// Evaluates the result
            /// of t_<expand_<func_t, list_t>>
            template < typename func_t,
                     typename list_t >
            using expand =
                t_<expand_<func_t, list_t>>;


            /// TODO Documentation curry
            // template < typename func_t,
            //         typename args_t = quote<list >>
            // using curry =
            //    compose<func_t, args_t>;


            /// TODO Documentation uncurry
            // template <typename F>
            // using uncurry =
            //    bind_front<quote<apply_list>, F>;
        }


        /// Shortcut for
        /// function::always
        template<typename type_t>
        using always =
            function::always<type_t>;


        /// Shortcut for
        /// function::void_
        template<typename ... args_t>
        using void_ =
            function::void_<args_t...>;


        /// Shortcut for
        /// function::compose
        template<typename ... funcs_t>
        using compose =
            function::compose<funcs_t...>;


        /// Shortcut for
        /// function::expand
        template < typename func_t,
                 typename list_t >
        using expand =
            function::expand<func_t, list_t>;


        /// ////////////////////////////////// ///
        /// Features for detect template member ///
        /// ////////////////////////////////// ///
        namespace member
        {
            /// Determines if a
            /// type_t has the
            /// 'type' member
            template < typename ,
                     typename = void >
            struct has_type_
            {
                using type = std::false_type;
            };


            /// Specialisation for
            /// has_type_ if type_t
            /// has 'type' member
            template<typename type_t>
            struct has_type_ < type_t,
                    void_<typename type_t::type> >
            {
                using type = std::true_type;
            };


            /// Evaluates the result
            /// of t_<has_type_<type_t>>
            template<typename type_t>
            using has_type =
                t_<has_type_<type_t>>;


            /// Evaluates the result
            /// of v_<has_type<type_t>>;
            template<typename type_t>
            constexpr auto has_type_v =
                v_<has_type<type_t>>;


            /// Determines if a
            /// type has a return_
            /// member
            template < typename,
                     typename = void >
            struct has_return_
            {
                using type = std::false_type;
            };


            /// Specialisation for
            /// has_return_ if
            /// type_t has return_
            template <typename type_t>
            struct has_return_ < type_t,
                    void_ < typename
                    type_t::template return_<> > >
            {
                using type = std::true_type;
            };


            /// Evaluates the result
            /// of t_<has_return_<type_t>>
            template<typename type_t>
            using has_return =
                t_<has_return_<type_t>>;


            /// Evaluates the result
            /// of v_<has_return<type_t>>
            template<typename type_t>
            constexpr auto has_return_v =
                v_<has_return<type_t>>;


            /// Determines if type_t
            /// is a meta function
            /// or not.
            template<typename type_t>
            using is_meta_function =
                has_return<type_t>;


            /// Evaluates the result
            /// of v_<is_meta_function<type_t>>
            template<typename type_t>
            constexpr auto is_meta_function_v =
                v_<is_meta_function<type_t>>;
        }


        /// Shortcut for
        /// member::has_type
        template<typename type_t>
        using has_type =
            member::has_type<type_t>;


        /// Shortcut for
        /// member::has_type_v
        template<typename type_t>
        constexpr auto has_type_v =
            member::has_type_v<type_t>;


        /// Shortcut for
        /// member::has_return
        template<typename type_t>
        using has_return =
            member::has_return<type_t>;


        /// Shortcut for
        /// member::has_return_v
        template<typename type_t>
        constexpr auto has_return_v =
            member::has_return_v<type_t>;


        /// Shortcut for
        /// member::is_meta_function
        template<typename type_t>
        using is_meta_function =
            member::is_meta_function<type_t>;


        /// Shortcut for
        /// member::is_meta_function_v
        template<typename type_t>
        constexpr auto is_meta_function_v =
            member::is_meta_function_v<type_t>;

        /// //////////////////////////// ///
        /// Type instanciation deferring ///
        /// //////////////////////////// ///
        namespace deferring
        {
            template < template<typename...> typename,
                     typename,
                     typename = void >
            struct defer_;

            template < template <typename...> class func_t,
                     typename... args_t >
            struct defer_ < func_t,
                    list<args_t...>,
                    void_<func_t<args_t...> >>
            {
                using type = func_t<args_t...>;
            };

            template < template <typename...> class func_t,
                     typename... args_t >
            struct defer :
                    defer_<func_t, list<args_t...>>
            {
            };
        }


        /// Shortcut for
        /// deferring::defer
        template < template<typename...> typename func_t,
                 typename... args_t >
        using defer =
            deferring::defer<func_t, args_t...>;


        /// //////////////////////// ///
        /// Meta function conversion ///
        /// //////////////////////// ///
        namespace function
        {
            /// Transforms type_t into
            /// a meta function
            template <template<typename...> typename type_t>
            struct quote
            {
                template<typename...args_t>
                using return_ =
                    type_t<args_t...>;
                ///using return_ = t_<defer<type_t, args_t...>>; /// WHY DEFFERING ?
            };
        }


        /// Shortcut for
        /// function::quote
        template < template<typename ...>
        typename type_t >
        using quote =
            function::quote<type_t>;

        /// ////////////// ///
        /// Type selection ///
        /// ////////////// ///
        namespace conditional
        {
            /// Type selector
            template<typename ...>
            struct _if_;


            /// Type selector
            /// specialisation that
            /// returns void
            /// if_t is true
            template<typename if_t>
            struct _if_<if_t> :
                    std::enable_if<v_<if_t> >
            {
            };


            /// Type selector
            /// specialisation that
            /// returns then_t
            /// if_t is true
            template < typename if_t,
                     typename then_t >
            struct _if_<if_t, then_t>:
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
            struct _if_<if_t, then_t, else_t>:
                    std::conditional<v_<if_t>, then_t, else_t>
            {
            };


            /// Evaluates the result
            /// of t_<_if_<args_t...>>
            template<typename ... args_t>
            using if_ = t_<_if_<args_t...>>;


            /// Evaluates the result
            /// of if_<bool_<_b>, args_t... >
            template < bool _b,
                     typename... args_t >
            using if_c =  if_<bool_<_b>, args_t... >;


            /// Evaluates the result
            /// of if_<if_t, then_t, else_t>
            template < typename if_t,
                     typename then_t,
                     typename else_t >
            using select = if_<if_t, then_t, else_t> ;


            /// Evaluates the result
            /// of if_c<_b, then_t, else_t>
            template < bool _b,
                     typename then_t,
                     typename else_t >
            using select_c = if_c<_b, then_t, else_t> ;


            /// Returns std::true_type
            /// if all bools_t are true
            template <typename... bools_t>
            struct _and_;


            /// Specialisation for
            /// _and_ that returns
            /// std::true_type for
            /// default case.
            template <>
            struct _and_<> :
                    std::true_type
            {
            };


            /// Specialisation for
            /// _and_ that returns
            /// std::false_type if
            /// one of bools_t is
            /// false
            template < typename bool_t,
                     typename... bools_t >
            struct _and_<bool_t, bools_t...>:
                    if_c < !v_<bool_t>, std::false_type, _and_<bools_t... >>
            {
            };


            /// Evaluates the result
            /// of t_<_and_<bools_t...>>
            template<typename ... bools_t>
            using and_ =
                t_<_and_<bools_t...>>;


            /// Returns std::true_type
            /// if one or more bools_t
            /// is true
            template <typename... bools_t>
            struct _or_;


            /// Specialisation for
            /// _or_ that returns
            /// std::false_type
            /// for default case
            template <>
            struct _or_<> :
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
            struct _or_<bool_t, bools_t...> :
                    if_c < v_<bool_t>,
                    std::true_type,
                    _or_<bools_t... >>
            {
            };


            /// Evaluates the result
            /// of t_<_or_<bools_t...>>
            template<typename ... bools_t>
            using or_ =
                t_<_or_<bools_t...>>;


            /// Negates the bool_t
            template<typename bool_t>
            using not_ =
                bool_ < !v_<bool_t >>>;
        }


        namespace pack /// TODO THAT
        {
            ///////////////////////////////////////////////////////////////////////////////////////////
            // concat
            /// \cond
            namespace detail
            {
                template <typename... Lists>
                struct concat_
                {
                };

                template <>
                struct concat_<>
                {
                    using type = list<>;
                };

                template <typename... List1>
                struct concat_<list<List1...>>
                {
                    using type = list<List1...>;
                };

                template <typename... List1, typename... List2>
                struct concat_<list<List1...>, list<List2...>>
                {
                    using type = list<List1..., List2...>;
                };

                template <typename... List1, typename... List2, typename... List3>
                struct concat_<list<List1...>, list<List2...>, list<List3...>>
                {
                    using type = list<List1..., List2..., List3...>;
                };

                template <typename... List1, typename... List2, typename... List3, typename... Rest>
                struct concat_<list<List1...>, list<List2...>, list<List3...>, Rest...>
                        : concat_<list<List1..., List2..., List3...>, Rest...>
                {
                };
            } // namespace detail
            /// \endcond

            /// Concatenates several lists into a single list.
            /// \pre The parameters must all be instantiations of \c meta::list.
            /// \par Complexity
            /// \f$ O(L) \f$ where \f$ L \f$ is the number of lists in the list of lists.
            /// \ingroup transformation
            template <typename... Lists>
            using concat = _t<detail::concat_<Lists...>>;

            namespace lazy
            {
                /// \sa 'meta::concat'
                /// \ingroup lazy_transformation
                template <typename... Lists>
                using concat = defer<concat, Lists...>;
            }

            /// Joins a list of lists into a single list.
            /// \pre The parameter must be an instantiation of \c meta::list\<T...\>
            /// where each \c T is itself an instantiation of \c meta::list.
            /// \par Complexity
            /// \f$ O(L) \f$ where \f$ L \f$ is the number of lists in the list of
            /// lists.
            /// \ingroup transformation
            template <typename ListOfLists>
            using join = apply_list<quote<concat>, ListOfLists>;

            namespace lazy
            {
                /// \sa 'meta::join'
                /// \ingroup lazy_transformation
                template <typename ListOfLists>
                using join = defer<join, ListOfLists>;
            }
        }
    }
}


#endif
