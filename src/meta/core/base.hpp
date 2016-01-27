#ifndef __BRAIN_META_CORE_BASE_HPP__
# define  __BRAIN_META_CORE_BASE_HPP__


/// Macro defining the
/// way to dermine if
/// a class has name
/// inner its definition

#  define has_(name) \
    template < typename, \
    typename = void > \
    struct has_##name##_member : false_ \
    { \
    }; \
    \
    template <typename type_t> \
    struct has_##name##_member < type_t, \
            void_ < typename \
            type_t::name > > : true_\
    { \
    };

#  define access_(name) \
    namespace member{template<typename type_t> struct name##_{using type = typename type_t::name;};} \
    template<typename type_t> \
    using name##_ = \
                    typename member::name##_<type_t>::type;


#  define member_(name) \
    has_(name) \
    access_(name)


namespace brain
{
    namespace meta
    {
        /// ////////////// ///
        /// Basic Features ///
        /// ////////////// ///
        ///
        /// Tools, alias or
        /// type used everywhere
        /// in this library
        namespace core
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


            /// Metafunction that
            /// returns always void
            /// whatever given types
            template<typename ...>
            using void_ =
                void;


            /// Definition
            /// of paramater
            /// pack. Developped
            /// in pack.hpp
            template<typename ...>
            struct pack;


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


            /// Public exposition
            /// of the impl::function_
            template < template<typename ...> typename func_t,
                     typename ... args_t >
            struct function_
            {
                /// Only the call to
                /// type member compute
                /// its evaluation.
                using type =
                    func_t<args_t...>;
            };


            /// Unitary Test
            /// of function_
            namespace test_function
            {
                template<typename type_t>
                using idem_function =
                    function_<idem_, type_t>;

                static_assert(v_<is_same_<type_<idem_function<int>>, int>>, "");
            }
        }
    }
}

#endif
