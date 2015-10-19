#ifndef __BRAIN_META_HPP
#define __BRAIN_META_HPP


namespace brain
{
    namespace meta
    {
        /// ////////////////////////////// ///
        /// Shortcuts for all meta library ///
        /// ////////////////////////////// ///

        /// Enable to evaluate
        /// a type in type_t.
        template<typename type_t>
        using t_ = typename type_t::type;

        /// Enable to evaluate a
        /// value in type_t::type
        template<typename type_t>
        constexpr auto v_ = type_t::type::value;

        /// Enable to evaluate
        /// type_t:type::id
        template<typename type_t>
        constexpr auto id_ = type_t::id;

        /// ///////////////////////// ///
        /// Wrapper for literal types ///
        /// ///////////////////////// ///
        namespace literal
        {
            /// A wrapper for std::size_t.
            template <std::size_t _s>
            using size_t = std::integral_constant<std::size_t, _s>;


            /// A wrapper for bool.
            template <bool _b>
            using bool_ = std::integral_constant<bool, _b>;


            /// A wrapper for int.
            template <int _i>
            using int_ = std::integral_constant<int, _i>;


            /// An wrapper for char
            template <char _c>
            using char_ = std::integral_constant<char, _c>;
        }


        /// Shortcut for literal::size_t
        template <std::size_t _s>
        using size_t = literal::size_t<_s>;


        /// Shortcut for literal::bool_
        template <bool _b>
        using bool_ = literal::bool_<_b>;


        /// Shortcut for literal::int_
        template <int _i>
        using int_ = literal::int_<_i>;


        /// Shortcut for literal::char_
        template <char _c>
        using char_ = literal::char_<_c>;
    }
}


#endif
