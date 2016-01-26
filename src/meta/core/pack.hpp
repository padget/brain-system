#ifndef __BRAIN_META_CORE_PACk_HPP__
# define  __BRAIN_META_CORE_PACk_HPP__

namespace brain
{
    namespace meta
    {
        namespace core
        {
            /// Main support of the
            /// parameters pack
            template<typename ... items_t>
            struct pack
            {
                using size =
                    size_t_<sizeof...(items_t)>;
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


            /// Unitary test for
            /// concat_
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


            /// Push back type_t
            /// at the end of pack_t
            template < typename pack_t,
                     typename type_t >
            using push_back_ =
                concat_<pack_t, pack<type_t>>;
                
                
            /// Push front type_t
            /// at the begin of pack_t
            template<typename pack_t, 
            typename type_t>
            using push_front_ = 
                concat_<pack<type_t>, pack_t>;
                

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


            /// Unitary test
            /// for clear_
            namespace test_clear
            {
                using pack_t = pack<int, short>;

                static_assert(v_<std::is_same<clear_<pack_t>, pack<>>>, "");
            }
            
            
            at
        }
    }
}

#endif
