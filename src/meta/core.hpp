#ifndef __BRAIN_META_CORE_HPP__
# define __BRAIN_META_CORE_HPP__

#include <type_traits>
#include "macro.hpp"

namespace brain
{
    namespace meta
    {
        /// Type that
        /// represents
        /// nothing
        struct nil {};


        /// Alias for
        /// std::true_type
        using true_ =
            std::true_type;


        /// Alias for
        /// std::false_type
        using false_ =
            std::false_type;


        /// Wrapper for void
        template<typename ...>
        using void_ =
            void;


        /// Definition
        /// of pack
        template<typename ...>
        struct pack;


        /// //////////////////// ///
        /// Most common shortcut ///
        /// //////////////////// ///


        /// Access to type member
        /// of type_t. Evaluates
        /// the result of the meta
        /// function type_t
        has_(type)
        access_(type)


        /// Access to value
        /// member of type_t
        template<typename type_t>
        constexpr decltype(type_<type_t>::value) v_ =
            type_<type_t>::value;


        /// Access to type_t
        /// itself
        template<typename type_t>
        using idem_ =
            type_t;


        /// type_ shortcut
        /// for std::is_same
        template < typename type_t,
                 typename other_t >
        using is_same_ =
            type_<std::is_same<type_t, other_t>>;


        /// ////////////////////////////// ///
        /// function_ : lazy instantiation ///
        /// ////////////////////////////// ///
        ///
        /// Lazy instanciation is the
        /// mechanism that enables to
        /// defer the evaluation of the
        /// member of a type. While the
        /// member of a type is not used
        /// in the source code, it won't
        /// be evaluated.
        ///
        /// So the most important things
        /// is to be aware the moment
        /// when the processing is used
        /// or not. So the function_
        /// enables to declare only
        /// signature of a metafunction
        /// (a type with type member)


        namespace impl
        {
            /// A function is
            /// the declaration
            /// of a signature of
            /// a meta function.
            template < template<typename ...> typename func_t,
                     typename args_t >
            struct function_;


            /// Specialization that
            /// expands the args_t
            /// for the future
            /// function evaluation
            template < template<typename ...> typename func_t,
                     typename ... args_t >
            struct function_ <
                    func_t,
                    pack<args_t... >>
            {
                /// Only the call to
                /// type member compute
                /// its evaluation.
                using type =
                    func_t<args_t...>;
            };
        }


        /// Public exposition
        /// of the impl::function_
        template < template<typename ...> typename func_t,
                 typename ... args_t >
        using function_ =
            impl::function_ <
            func_t,
            pack<args_t... >>;


        /// Lazy declaration
        /// of type_ and
        /// has_type_member
        lazy_(type)


        namespace lazy
        {
            /// Lazy signature
            /// of idem_
            template<typename type_t>
            struct idem_ :
                    function_<meta::idem_, type_t> {};


            /// Lazy signature
            /// of is_same_
            template < typename type_t,
                     typename other_t >
            struct is_same_ :
                    function_<meta::is_same_, type_t, other_t> {};
        }


        /// Unitary Test
        /// of function_
        namespace test_function
        {
            template<typename type_t>
            using idem_function =
                function_<idem_, type_t>;

            template<typename type_t>
            using lazy_type =
                lazy::type_<type_t>;

            static_assert(v_<std::is_same<type_<idem_function<int>>, int>>, "");
            /// Example of lazy use :
            /// if this expression will be evaluated,
            /// the compilation will fail because of
            /// int has no member type ! So the type
            /// member of function_ demanding of the
            /// evaluation of the type member of int
            /// is not evaluated while the type of
            /// function_ is not used in code !
            static_assert(!v_<is_same_<lazy_type<int>, int>>, "");
            static_assert(v_<is_same_<type_<lazy::type_<function_<idem_, int>>> , int>>, "");
        }


        /// ///////////////////////// ///
        /// Wrapper for literal types ///
        /// ///////////////////////// ///


        /// Shortcut for
        /// std::integral_constant
        template < typename literal_t,
                 literal_t _l >
        using igral_ =
            type_<std::integral_constant<literal_t, _l>>;


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


        /// /////////////////////// ///
        /// Logical wrapper feature ///
        /// /////////////////////// ///


        /// Wrapper for equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using equal_to_ =
            bool_ < v_<type_t>
            == v_<other_t >>;


        /// Wrapper for not equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using not_equal_to_ =
            bool_ < v_<type_t>
            != v_<other_t >>;


        /// Wrapper for greater
        /// operator
        template < typename type_t,
                 typename other_t >
        using greater_ =
            bool_ < (v_<type_t>
                     > v_<other_t>) >;


        /// Wrapper for less
        /// operator
        template < typename type_t,
                 typename other_t >
        using less_ =
            bool_ < (v_<type_t>
                     < v_<other_t>) >;


        /// Wrapper for greater equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using greater_equal_ =
            bool_ < (v_<type_t>
                     >= v_<other_t>) >;


        /// Wrapper for less equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using less_equal_ =
            bool_ < (v_<type_t>
                     <= v_<other_t>) >;


        /// Wrapper for bit and
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_and_ =
            bool_ < v_<type_t>
            & v_<other_t >>;


        /// Wrapper for bit or
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_or_ =
            bool_ < v_<type_t>
            | v_<other_t >>;


        /// Wrapper for bit xor
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_xor_ =
            bool_ < v_<type_t>
            ^ v_<other_t >>;


        /// Wrapper for bit not
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_not_ =
            bool_ < ~v_<type_t >>;


        namespace lazy
        {
            /// Lazy signature
            /// of equal_to_
            template < typename type_t,
                     typename other_t >
            struct equal_to_ :
                    function_<meta::equal_to_, type_t, other_t> {};


            /// Lazy signature
            /// of not_equal_to_
            template < typename type_t,
                     typename other_t >
            struct not_equal_to_ :
                    function_<meta::not_equal_to_, type_t, other_t> {};


            /// Lazy signature
            /// of greater_
            template < typename type_t,
                     typename other_t >
            struct greater_ :
                    function_<meta::greater_, type_t, other_t> {};


            /// Lazy signature
            /// of less_
            template < typename type_t,
                     typename other_t >
            struct less_ :
                    function_<meta::less_, type_t, other_t> {};


            /// Lazy signature
            /// of greater_equal_
            template < typename type_t,
                     typename other_t >
            struct greater_equal_ :
                    function_<meta::greater_equal_, type_t, other_t> {};


            /// Lazy signature
            /// of less_equal_
            template < typename type_t,
                     typename other_t >
            struct less_equal_ :
                    function_<meta::less_equal_, type_t, other_t> {};


            /// Lazy signature
            /// of bit_and_
            template < typename type_t,
                     typename other_t >
            struct bit_and_ :
                    function_<meta::bit_and_, type_t, other_t> {};


            /// Lazy signature
            /// of bit_or_
            template < typename type_t,
                     typename other_t >
            struct bit_or_ :
                    function_<meta::bit_or_, type_t, other_t> {};


            /// Lazy signature
            /// of bit_xor_
            template < typename type_t,
                     typename other_t >
            struct bit_xor_ :
                    function_<meta::bit_xor_, type_t, other_t> {};


            /// Lazy signature
            /// of bit_not_
            template < typename type_t,
                     typename other_t >
            struct bit_not_ :
                    function_<meta::bit_not_, type_t> {};
        }


        namespace impl
        {
            /// Returns true_
            /// if all bools_t are true
            template <typename... bools_t>
            struct and_;


            /// Specialisation for
            /// _and_ that returns
            /// std::true_type for
            /// default case.
            template <>
            struct and_<> :
                    true_
            {
            };

            /// Specialisation for
            /// and_ that returns
            /// true_ if
            /// all of bools_t is
            /// true_
            template < typename test_t,
                     typename ... other_t >
            struct and_<test_t, other_t...> :
                    bool_<v_<test_t> and v_<type_<and_<other_t...>>>>
            {
            };
        }


        /// Evaluates the result
        /// of type_<_and_<bools_t...>>
        template<typename ... bools_t>
        using and_ =
            type_<impl::and_<bools_t...>>;


        namespace impl
        {
            /// Returns true_
            /// if one or more bools_t
            /// is true
            template <typename... bools_t>
            struct or_;


            /// Specialisation for
            /// or_ that returns
            /// false_ for default case
            template <>
            struct or_<> :
                    false_
            {
            };


            /// Specialisation for
            /// or_ that returns
            /// true_ if
            /// one of bools_t is
            /// true_
            template < typename bool_t,
                     typename... bools_t >
            struct or_<bool_t, bools_t...> :
                    bool_<v_<bool_t> or v_<type_<or_<bools_t...>>>>

            {
            };
        }


        /// Evaluates the result
        /// of type_<_or_<bools_t...>>
        template<typename ... bools_t>
        using or_ =
            type_<impl::or_<bools_t...>>;


        /// Negates the bool_t
        template<typename bool_t>
        using not_ =
            bool_ < !v_<bool_t >>;


        namespace lazy
        {
            /// Lazy signature
            /// of and_
            template<typename ... bools_t>
            struct and_ :
                    function_<meta::and_, bools_t...> {};


            /// Lazy signature
            /// of or_
            template<typename ... bools_t>
            struct or_ :
                    function_<meta::or_, bools_t...> {};


            /// Lazy signature
            /// of not_
            template<typename bool_t>
            struct not_ :
                    function_<meta::not_, bool_t> {};
        }


        namespace test_logical_wrapper
        {
            /// TODO All test of logical wrapper
        }


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


        namespace lazy
        {
            /// Lazy signature
            /// of sizeof_
            template<typename type_t>
            struct sizeof_ :
                    function_<meta::sizeof_, type_t> {};


            /// Lazy signature
            /// of sizeof_pack_
            template<typename ... types_t>
            struct sizeof_pack_ :
                    function_<meta::sizeof_pack_, types_t...> {};


            /// Lazy signature
            /// of alignof_
            template<typename type_t>
            struct alignof_ :
                    function_<alignof_, type_t> {};
        }


        /// /////////////////////// ///
        /// Keyword Feature Remover ///
        /// /////////////////////// ///


        ///
        template<typename type_t>
        using remove_const_t =
            std::remove_const_t<type_t>;


        ///
        template<typename type_t>
        using remove_volatile_t =
            std::remove_volatile_t<type_t>;


        ///
        template<typename type_t>
        using remove_reference_t =
            std::remove_reference_t<type_t>;


        ///
        template<typename type_t>
        using remove_pointer_t =
            std::remove_pointer_t<type_t>;


        ///
        template<typename type_t>
        using extract_basic_type_t =
            remove_const_t <
            remove_pointer_t <
            remove_reference_t<type_t> > >;


        /// ///////////////////////////// ///
        /// Mathematical wrapper features ///
        /// ///////////////////////////// ///


        /// Wrapper for incrementing
        template<typename type_t>
        using inc_ =
            igral_ <
            decltype(v_<type_t> + 1),
            v_<type_t> + 1 >;


        /// Wrapper for decrementing
        template<typename type_t>
        using dec_ =
            igral_ <
            decltype(v_<type_t> - 1),
            v_<type_t> - 1 >;


        /// Wrapper for additing
        template < typename type_t,
                 typename other_t >
        using plus_ =
            igral_ <
            decltype(v_<type_t> + v_<other_t>),
            v_<type_t> + v_<other_t >>;


        /// Wrapper for substracting
        template < typename type_t,
                 typename other_t >
        using minus_ =
            igral_ <
            decltype(v_<type_t> - v_<other_t>),
            v_<type_t> - v_<other_t >>;


        /// Wrapper for multiplying
        template < typename type_t,
                 typename other_t >
        using multiplies_ =
            igral_ <
            decltype(v_<type_t> * v_<other_t>),
            v_<type_t> * v_<other_t >>;


        /// Wrapper for dividing
        template < typename type_t,
                 typename other_t >
        using divides_ =
            igral_ <
            decltype(v_<type_t> / v_<other_t>),
            v_<type_t> / v_<other_t >>;


        /// Wrapper for negating
        template <typename type_t>
        using negate_ =
            igral_ <
            decltype(-v_<type_t>),
            -v_<type_t >>;


        /// Wrapper for moduling
        template < typename type_t,
                 typename other_t >
        using modulus_ =
            igral_ <
            decltype(v_<type_t> % v_<other_t>),
            v_<type_t> % v_<other_t >>;


        namespace lazy
        {
            /// Lazy signature
            /// of inc_
            template<typename type_t>
            struct inc_ :
                    function_<meta::inc_, type_t> {};


            /// Lazy signature
            /// of dec_
            template<typename type_t>
            struct dec_ :
                    function_<meta::dec_, type_t> {};


            /// Lazy signature
            /// of plus_
            template < typename type_t,
                     typename other_t >
            struct plus_ :
                    function_<meta::plus_, type_t, other_t> {};



            /// Lazy signature
            /// of minus_
            template < typename type_t,
                     typename other_t >
            struct minus_ :
                    function_<meta::minus_, type_t, other_t> {};


            /// Lazy signature
            /// of multiplies_
            template < typename type_t,
                     typename other_t >
            struct multiplies_:
                    function_<meta::multiplies_, type_t, other_t> {};


            /// Lazy signature
            /// of divides_
            template < typename type_t,
                     typename other_t >
            struct divides_ :
                    function_<meta::divides_, type_t, other_t> {};


            /// Lazy signature
            /// of negate_
            template <typename type_t>
            struct negate_ :
                    function_<meta::negate_, type_t> {};


            /// Lazy signature
            /// of modulus_
            template < typename type_t,
                     typename other_t >
            struct modulus_ :
                    function_<meta::modulus_, type_t, other_t> {};
        }


        /// ////////////// ///
        /// Type selection ///
        /// ////////////// ///


        namespace impl
        {
            template < bool _test,
                     typename then_t,
                     typename else_t >
            struct if_c_;

            template < typename then_t,
                     typename else_t >
            struct if_c_<true, then_t, else_t>
            {
                using type =
                    then_t;
            };

            template < typename then_t,
                     typename else_t >
            struct if_c_<false, then_t, else_t>
            {
                using type =
                    else_t;
            };

            /// Type selector
            /// specialisation that
            /// returns then_t
            /// if_t is true
            /// else else_t
            template < typename test_t,
                     typename then_t,
                     typename else_t >
            struct if_
            {
                using type =
                    type_<if_c_<v_<test_t>, then_t, else_t>> ;
            };


            template < typename test_t,
                     typename lthen_t,
                     typename lelse_t >
            struct eval_if_
            {
                using type =
                    type_<type_<if_<test_t, lthen_t, lelse_t>>>;
            };
        }


        /// type_ shorcut
        /// for if_
        template < typename test_t,
                 typename then_t,
                 typename else_t >
        using if_ =
            type_<impl::if_<test_t, then_t, else_t>>;


        /// type_ shortcut for
        /// eval_if_
        template < typename test_t,
                 typename lthen_t,
                 typename lelse_t >
        using eval_if_ =
            type_<impl::eval_if_<test_t, lthen_t, lelse_t>>;


        namespace lazy
        {
            /// Lazy signature
            /// of if_
            template < typename test_t,
                     typename then_t,
                     typename else_t >
            struct if_ :
                    function_<meta::if_, test_t, then_t, else_t> {};

            /// Lazy signature
            /// of eval_if_
            template < typename test_t,
                     typename lthen_t,
                     typename lelse_t >
            struct eval_if_ :
                    function_<meta::eval_if_, test_t, lthen_t, lelse_t> {};

        }


        namespace test_selection
        {
            /// TODO Test for all selection features
        }

        /// ///////////// ///
        /// Pack Features ///
        /// ///////////// ///


        /// Main support of the
        /// parameters pack
        template<typename ... items_t>
        struct pack
        {
            using size =
                sizeof_pack_<items_t...>;
        };


        /// size member
        /// accessor
        template<typename pack_t>
        using size_ =
            typename pack_t::size;


        namespace impl
        {
            /// Concat any number
            /// of packs into one
            /// pack. The type of
            /// the returned pack
            /// is the same as the
            /// first of the list
            template<typename ... packs_t>
            struct concat_;


            /// Specialization that
            /// distribute the work
            /// between the two basic
            /// specializations
            template < typename pack1_t ,
                     typename ... others_t >
            struct concat_ <pack1_t, others_t...>
            {
                using type =
                    type_<concat_<pack1_t, type_<concat_<others_t...>>>>;
            };


            /// Concatenates
            /// two packs
            template < template<typename ...> typename pack1_t,
                     typename ... items1_t,
                     template<typename ...> typename pack2_t,
                     typename ... items2_t >
            struct concat_ <
                    pack1_t<items1_t...>,
                    pack2_t<items2_t...> >
            {
                using type =
                    pack1_t<items1_t..., items2_t...>;
            };

            /// Concatenates
            /// one pack
            template < template<typename ...> typename pack1_t,
                     typename ... items1_t >
            struct concat_<pack1_t<items1_t...>>
            {
                using type =
                    pack1_t<items1_t...>;
            };
        }


        /// type_ shortcut
        /// for concat_
        template<typename ... packs_t>
        using concat_ =
            type_<impl::concat_<packs_t...>>;


        namespace lazy
        {
            /// Lazy signature
            /// of concat_
            template<typename ... packs_t>
            struct concat_ :
                    function_<meta::concat_, packs_t...> {};
        }


        namespace test_concat
        {
            using a_list = pack<int, double>;
            using a_list2 = pack<float, short>;
            using a_list3 = pack<char>;

            static_assert(v_<is_same_<pack<int, double>, concat_<a_list>>>, "");
            static_assert(v_<is_same_<pack<int, double, float, short>, concat_<a_list, a_list2>>>, "");
            static_assert(v_<is_same_<pack<int, double, float, short, char>, concat_<a_list, a_list2, a_list3>>>, "");
            static_assert(v_<is_same_<pack<int, double>, concat_<a_list>>>, "");
        }


        /// type_ shortcut for
        /// push_back_t_
        template < typename pack_t,
                 typename type_t >
        using push_back_ =
            concat_<pack_t, pack<type_t>>;


        namespace impl
        {
            /// Definition of
            /// push_front_
            template < typename pack_t,
                     typename type_t >
            struct push_front_;


            /// Pushes type_t at
            /// the front of
            /// pack_t
            template < template<typename...> typename pack_t,
                     typename ... items_t,
                     typename type_t >
            struct push_front_ <
                    pack_t<items_t...>,
                    type_t >
            {
                using type =
                    pack_t<type_t, items_t...>;
            };
        }


        /// type_ shortcut for
        /// push_front_
        template < typename pack_t,
                 typename type_t >
        using push_front_ =
            type_<impl::push_front_<pack_t, type_t>>;


        namespace lazy
        {

            /// Lazy signature
            /// of push_back_
            template < typename pack_t,
                     typename type_t >
            struct push_back_ :
                    function_<meta::push_back_, pack_t, type_t> {};


            /// Lazy signature
            /// of push_front_
            template < typename pack_t,
                     typename type_t >
            struct push_front_ :
                    function_<meta::push_front_, pack_t, type_t> {};
        }


        /// Unitary test
        /// for push_front_
        /// and push_back_
        namespace test_push_front_back
        {
            using seq_t = pack<int, short>;

            static_assert(v_<is_same_<pack<int, short, double>, push_back_<seq_t, double>>>, "");
            static_assert(v_<is_same_<pack<double, int, short>, push_front_<seq_t, double>>>, "");
        }


        namespace impl
        {
            /// Definition of
            /// clear_
            template<typename pack_t>
            struct clear_;


            /// Returns an empty
            /// sequence of the
            /// same type of the
            /// pack_t
            template < template<typename...> typename pack_t,
                     typename ... items_t >
            struct clear_<pack_t<items_t...>>
            {
                using type =
                    pack_t<>;
            };
        }


        /// type_ shortcut for
        /// clear_t_
        template<typename pack_t>
        using clear_ =
            type_<impl::clear_<pack_t>>;


        namespace lazy
        {
            /// Lazy signature
            /// of clear_
            template<typename pack_t>
            struct clear_ :
                    function_<meta::clear_, pack_t> {};
        }


        namespace test_clear
        {
            using pack_t = pack<int, short>;

            static_assert(v_<std::is_same<clear_<pack_t>, pack<>>>, "");
        }



        /// //////////////////////////////////////// ///
        /// function_class_ : lazy functor computing ///
        /// //////////////////////////////////////// ///


        /// function_class_ is
        /// a metafunction which
        /// the evaluation is in
        /// two times :
        ///  - Configuration with
        ///    parameters of the type func_t
        ///    (not lazy instantiation)
        ///  - Call of the member
        ///    return_ that represents
        ///    the results of the call.
        /// So it can be considered
        /// as a configurable metafunction
        template<template<typename ...> typename func_t>
        struct function_class_
        {
            /// Returns the result
            /// of func_t
            template<typename ... args_t>
            using return_ =
                type_<function_<func_t, args_t...>>;
        };


        template<typename index_t>
        struct placeholder;


        template<typename index_t>
        using arg =
            placeholder<index_t>;


        using _0_ = arg<long_<0>>;
        using _1_ = arg<long_<1>>;
        using _2_ = arg<long_<2>>;
        using _3_ = arg<long_<3>>;
        using _4_ = arg<long_<4>>;
        using _5_ = arg<long_<5>>;
        using _6_ = arg<long_<6>>;
        using _7_ = arg<long_<7>>;
        using _8_ = arg<long_<8>>;
        using _9_ = arg<long_<9>>;
        using _10_ = arg<long_<10>>;
        using _11_ = arg<long_<11>>;
        using _12_ = arg<long_<12>>;
        using _13_ = arg<long_<13>>;
        using _14_ = arg<long_<14>>;
        using _15_ = arg<long_<15>>;


        namespace impl
        {
            template<typename type_t>
            struct is_placeholder_expression_
            {
                using type = false_;
            };

            template < template<typename ...> typename type_t,
                     typename ... args_t >
            struct is_placeholder_expression_<type_t<args_t...>>
            {
                using type =
                   meta::or_<type_<is_placeholder_expression_<args_t>>...>;
            };

            template < template<typename> typename holder_t,
                     typename  _rank >
            struct is_placeholder_expression_<holder_t<_rank>>
            {
                using type =
                    meta::is_same_<meta::placeholder<_rank>, holder_t<_rank>>;
            };
        }


        template<typename type_t>
        using is_placeholder_expression_ =
            type_<impl::is_placeholder_expression_<type_t>>;


        namespace lazy
        {
            template<typename type_t>
            struct is_placeholder_expression_ :
                    function_<is_placeholder_expression_, type_t> {};
        }


        namespace test_is_placeholder
        {
            static_assert(v_<is_placeholder_expression_<_0_>>, "");
            static_assert(v_<is_placeholder_expression_<lazy::if_<lazy::if_<_1_, _1_, _1_>, int, int>>>, "");
        }


        namespace impl
        {
            template<typename lfunc_t>
            struct lambda;


            template < typename func_r,
                     typename ... holders_t >
            struct bind_;


            template < typename func_r,
                     typename is_placed_t,
                     typename ... args_t >
            struct return_;


            template < typename func_r,
                     typename ... args_t >
            struct return_<func_r, false_, args_t...>
            {
                using type =
                    typename func_r::template return_<args_t...>;
            };


            template < template<typename ...> typename func_t,
                     typename ... holders_t,
                     typename ... args_t >
            struct  return_<func_t<holders_t...>, false_, args_t...>
            {
                using type =
                    typename func_t<holders_t...>::template return_<args_t...>;
            };


            template < typename func_t,
                     typename ... args_t >
            struct return_<lambda<func_t>, true_, args_t...>
            {
                using type =
                    type_<type_<return_<type_<lambda<func_t>>, true_, args_t...>>>;
            };


            template < template<typename ...> typename func_t,
                     typename ... holders_t,
                     typename ... args_t >
            struct  return_<func_t<holders_t...>, true_, args_t...>
            {
                using bind =
                    bind_<function_class_<func_t>, holders_t...>;
                using type =
                    type_<type_<return_<type_<bind>, false_, args_t...>>>;
            };
        }

        /// Access to return_
        /// member of type_t
        template < typename type_r,
                 typename ... args_t >
        using return_ =
            type_<impl::return_<type_r, meta::is_placeholder_expression_<type_r>, args_t...>>;


        namespace lazy
        {
            /// Lazy signature
            /// of return_
            template < typename type_r,
                     typename ... args_t >
            struct return_ :
                    function_<meta::return_, type_r, args_t...> {};
        }



        namespace impl
        {
            template < typename func_r,
                     typename ... holders_t >
            struct bind_
            {

                using type =
                    bind_;

                template<typename ... reals_t>
                using return_  =
                    return_ <
                    func_r,
                    meta::is_placeholder_expression_<func_r>,
                    type_ <
                    eval_if_ <
                    meta::is_placeholder_expression_<holders_t>,
                    return_<holders_t, meta::is_placeholder_expression_<holders_t>, reals_t...>,
                    lazy::idem_<holders_t>
                    >
                    > ...
                    >;
            };


            template <typename lfunc_t>
            struct lambda;


            template < template<typename...> typename lfunc_t,
                     typename ... holders_t >
            struct lambda<lfunc_t<holders_t...>>
            {
                using type =
                    bind_<function_class_<lfunc_t>, holders_t...> ;

                template<typename ... args_t>
                using return_ =
                    type_<type_<return_<type, meta::is_placeholder_expression_<type>, args_t...>>>;
            };
        }


        template < typename func_r,
                 typename ... holders_t >
        using bind_ =
            type_<impl::bind_<func_r, holders_t...>>;


        template<typename lfunc_t>
        using lambda =
            impl::lambda<lfunc_t>;


        namespace impl
        {
            template<typename lambda_t>
            struct is_lambda_;

            template < template<typename> typename lambda_t,
                     typename lfunc_t >
            struct is_lambda_<lambda_t<lfunc_t>>
            {
                using type =
                    meta::is_same_<meta::lambda<lfunc_t>, lambda_t<lfunc_t>>;
            };
        }

        template<typename lambda_t>
        using is_lambda_ =
            type_<impl::is_lambda_<lambda_t>>;


        namespace lazy
        {
            template<typename lambda_t>
            struct is_lambda_ :
                    function_<is_lambda_, lambda_t> {};
        }


        namespace test_is_lambda
        {
            static_assert(v_<is_lambda_<lambda<_0_>>>, "");
        }




        /// Unitary Test
        /// of function_class_
        namespace test_function_class
        {
            template<typename type_t>
            using is_int =
                is_same_<type_t, int>;

            using is_int_function =
                function_class_<is_int>;

            static_assert(v_<return_<is_int_function, int>>, "");
        }


        /// //////////////////////////// ///
        /// Composition of metafunctions ///
        /// //////////////////////////// ///


        namespace impl
        {
            /// A meta function that
            /// returns the composition
            /// of other several meta
            /// functions funcs_t
            template < typename func_t,
                     typename ... funcs_t >
            struct compose_;


            /// Specialisation for
            /// compose that takes
            /// a single meta function
            template<typename func_t>
            struct compose_<func_t>
            {
                template<typename ... args_t>
                using return_ =
                    meta::return_<func_t, args_t...>;
            };


            /// Specialisation for
            /// compose that take
            /// more one meta functions
            template < typename func_t,
                     typename next_t,
                     typename ... funcs_t >
            struct compose_<func_t, next_t, funcs_t...>
            {
                template<typename ... args_t>
                using return_ =
                    meta::return_<func_t, meta::return_<compose_<next_t, funcs_t...>, args_t...>>;
            };
        }


        /// Evaluates the result of
        /// impl::compose<funcs_t...>
        template < typename func_t,
                 typename ... funcs_t >
        using compose_ =
            impl::compose_<func_t, funcs_t...>;


        namespace lazy
        {
            /// Lazy signature
            /// of compose_
            template < typename func_t,
                     typename ... funcs_t >
            struct compose_ :
                    function_<meta::compose_, func_t, funcs_t...> {};
        }


        /// Unitary Test
        /// of compose_
        namespace test_compose
        {
            template<typename type_t>
            using is_int = is_same_<type_t, int>;
            using is_int_comp = compose_<function_class_<is_int>>;

            static_assert(v_<meta::return_<is_int_comp, int>>, "");

            template<typename type_t>
            using is_true = is_same_<type_t, true_>;
            using is_int_true_compo = compose_<function_class_<is_true>, is_int_comp>;

            static_assert(v_<meta::return_<is_int_true_compo, int>> , "");
        }


        /// ///////////////////////// ///
        /// Basic bind front and back ///
        /// ///////////////////////// ///


        /// Meta function that
        /// binds the front_args_t...
        /// at the beginning of
        /// the parameters of the
        /// meta function func_t
        template < typename func_t,
                 typename... front_args_t >
        struct bind_front_
        {
            template<typename ... args_t>
            using return_ =
                return_<func_t, front_args_t..., args_t...>;
        };


        /// Metafunction that
        /// binds the back_args_t...
        /// at the ending of
        /// the parameters of the
        /// meta function func_t
        template < typename func_t,
                 typename ... back_args_t >
        struct bind_back_
        {
            template<typename ... args_t>
            using return_ =
                return_<func_t, args_t..., back_args_t...>;
        };


        namespace lazy
        {
            /// Lazy signature
            /// of bind_front_
            template < typename func_t,
                     typename ... front_args_t >
            struct bind_front_ :
                    function_<meta::bind_front_, func_t, front_args_t...> {};


            /// Lazy signature
            /// of bind_back_
            template < typename func_t,
                     typename ... back_args_t >
            struct bind_back_ :
                    function_<meta::bind_back_, func_t, back_args_t...> {};
        }


        namespace test_bind_front_back
        {
            using is_float_front = bind_front_<function_class_<is_same_>, float>;
            using is_float_back = bind_back_<function_class_<is_same_>, float>;

            static_assert(v_<return_<is_float_front, float>>, "");
            static_assert(v_<return_<is_float_back, float>>, "");
            static_assert(!v_<return_<is_float_front, int>>, "");
            static_assert(!v_<return_<is_float_back, int>>, "");
        }





    }
}

#endif
