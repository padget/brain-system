#ifndef __BRAIN_META_CORE_PACk_HPP__
# define  __BRAIN_META_CORE_PACk_HPP__

#include "base.hpp"
#include "select.hpp"
#include "logic.hpp"

namespace brain
{
    namespace meta
    {
        /// /////////////////// ///
        /// Pack basic features ///
        /// /////////////////// ///
        ///
        /// Some metafunction that
        /// operates directly on 
        /// paramters pack of types :
        ///  - size_
        ///  - empty_
        ///  - cat_
        ///  - push_back_/front_
        ///  - at_
        ///  - clear_
        namespace core
        {
            /// Main support of the
            /// parameters pack
            template<typename ... items_t>
            struct pack { };


            namespace impl
            {
                /// Returns the size
                /// of a parameters pack
                template<typename pack_t>
                struct size_;


                /// Returns the number
                /// of types_t in pack_t
                template < template<typename...> typename pack_t,
                         typename... types_t >
                struct size_<pack_t<types_t...>>
                {
                    using type =
                        core::size_t_<sizeof...(types_t)>;
                };
            }


            /// type_ shortcut
            /// for impl::size_
            template<typename pack_t>
            using size_ =
                core::type_<impl::size_<pack_t>>;
                
            
            /// Returns true_
            /// if the pack_t
            /// has no item
            template<typename pack_t>
            using empty_ =
                core::equal_to_<core::size_<pack_t>, size_t_<0>>;


            /// Unitary test
            /// for size_
            namespace test_size_empty
            {
                using p = pack<int, short, double>;
                using p_empty = pack<>;

                static_assert(core::v_<core::equal_to_<core::size_<p>, size_t_<3>>>, "");
                static_assert(core::v_<core::equal_to_<core::size_<p_empty>, size_t_<0>>>, "");
                static_assert(core::v_<core::empty_<p_empty>>, "");
            }
            
            
            namespace impl
            {
                /// Concat any number
                /// of packs into one
                /// pack. The type of
                /// the returned pack
                /// is the same as the
                /// first of the list
                template<typename ... packs_t>
                struct cat_;


                /// Specialization that
                /// distribute the work
                /// between the two basic
                /// specializations
                template < typename pack1_t ,
                         typename ... others_t >
                struct cat_ <pack1_t, others_t...>
                {
                    using type =
                        type_<cat_<pack1_t, type_<cat_<others_t...>>>>;
                };


                /// Concatenates
                /// two packs
                template < template<typename ...> typename pack1_t,
                         typename ... items1_t,
                         template<typename ...> typename pack2_t,
                         typename ... items2_t >
                struct cat_ <
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
                struct cat_<pack1_t<items1_t...>>
                {
                    using type =
                        pack1_t<items1_t...>;
                };
            }


            /// type_ shortcut
            /// for cat_
            template<typename ... packs_t>
            using cat_ =
                type_<impl::cat_<packs_t...>>;


            /// Unitary test for
            /// cat_
            namespace test_concat
            {
                using a_list = pack<int, double>;
                using a_list2 = pack<float, short>;
                using a_list3 = pack<char>;

                static_assert(v_<is_same_<pack<int, double>, cat_<a_list>>>, "");
                static_assert(v_<is_same_<pack<int, double, float, short>, cat_<a_list, a_list2>>>, "");
                static_assert(v_<is_same_<pack<int, double, float, short, char>, cat_<a_list, a_list2, a_list3>>>, "");
                static_assert(v_<is_same_<pack<int, double>, cat_<a_list>>>, "");
            }


            /// Push back type_t
            /// at the end of pack_t
            template < typename pack_t,
                     typename type_t >
            using push_back_ =
                cat_<pack_t, pack<type_t>>;


            /// Push front type_t
            /// at the begin of pack_t
            template < typename pack_t,
                     typename type_t >
            using push_front_ =
                cat_<pack<type_t>, pack_t>;


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
                /// Returns the nth
                /// type of pack_t
                template < typename pack_t,
                         typename index_t >
                struct at_;


                /// If type_t is
                /// the nth of
                /// pack_t, it will
                /// be returned,
                /// else, see next.
                template < template<typename ...> typename pack_t,
                         typename type_t,
                         typename ... types_t,
                         typename index_t >
                struct at_<pack_t<type_t, types_t...>, index_t>
                {
                    using type =
                        core::eval_if_ <
                        core::equal_to_<index_t, core::unsigned_<0>>,
                        core::function_<core::idem_, type_t>,
                        at_<pack_t<types_t...>, core::dec_<index_t> >>;
                };


                /// Returns nil
                /// if pack_t is
                /// empty.
                template < template<typename...> typename pack_t,
                         typename index_t >
                struct at_<pack_t<>, index_t>
                {
                    using type =
                        core::nil;
                };
            }


            template < typename pack_t,
                     typename index_t >
            using at_ =
                type_<impl::at_<pack_t, index_t>>;


            namespace test_at
            {
                using p = pack<int, short, double>;
                static_assert(core::v_<core::is_same_<int, at_<p, unsigned_<0>>>>, "");
                static_assert(core::v_<core::is_same_<short, at_<p, unsigned_<1>>>>, "");
                static_assert(core::v_<core::is_same_<double, at_<p, unsigned_<2>>>>, "");
                static_assert(core::v_<core::is_same_<nil, at_<p, unsigned_<3>>>>, "");
                static_assert(core::v_ < core::is_same_ < nil, at_ < p, unsigned_ < -1 >>> > , "");
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


            /// Unitary test
            /// for clear_
            namespace test_clear
            {
                using pack_t = pack<int, short>;

                static_assert(v_<std::is_same<clear_<pack_t>, pack<>>>, "");
            }
        }
    }
}

#endif
