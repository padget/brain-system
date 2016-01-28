#ifndef __BRAIN_META_CORE_BASE_HPP__
# define  __BRAIN_META_CORE_BASE_HPP__


/// Macro defining the
/// way to dermine if
/// a class has name
/// inner its definition

namespace meta
{
    /// ////////////// ///
    /// Basic Features ///
    /// ////////////// ///
    ///
    /// Tools, alias or
    /// type used everywhere
    /// in this library


    /// Meta function
    /// representation
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
    template<typename type_t>
    using type_ =
        typename type_t::type;


    /// Access to value
    /// member of type_t
    template<typename type_t>
    constexpr decltype(type_<type_t>::value) v_ =
        type_<type_t>::value;


    namespace impl
    {
        template < typename type_t,
                 typename =  void >
        struct has_type_member
        {
            using type =
                meta::false_ ;
        };

        template <typename type_t>
        struct has_type_member<type_t, void_<typename type_t::type>>
        {
            using type =
                meta::true_;
        };
    }


    template<typename type_t>
    using has_type_member =
        type_<impl::has_type_member<type_t>>;


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


    namespace lazy
    {
        /// Lazy signature
        /// of type_
        template<typename type_t>
        struct type_ :
                meta::function_<meta::type_, type_t> {};

        template<typename type_t>
        struct has_type_member:
                meta::function_<meta::has_type_member, type_t> {};

        /// Lazy signature
        /// of idem_
        template<typename type_t>
        struct idem_ :
                meta::function_<meta::idem_, type_t> {};

        /// Lazy signature of
        template < typename type_t,
                 typename other_t >
        struct is_same_ :
                meta::function_<meta::is_same_, type_t, other_t> {};

    }







}

#endif
