#ifndef __BRAIN_META_MATH_HPP__
# define __BRAIN_META_MATH_HPP__


namespace brain
{
    namespace meta
    {
        /// /////////////////////// ///
        /// Logical wrapper feature ///
        /// /////////////////////// ///


        /// Wrapper for equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using equal_to_t_ =
            bool_t_ < v_<type_t>
            == v_<other_t >>;


        /// t_ shortcut for equal_to_t_
        template < typename type_t,
                 typename other_t >
        using equal_to_t =
            lazy_t<equal_to_t_, type_t, other_t>;


        /// Wrapper for not equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using not_equal_to_t_ =
            bool_t_ < v_<type_t>
            != v_<other_t >>;


        /// t_ shortcut for not_equal_to_t_
        template < typename type_t,
                 typename other_t >
        using not_equal_to_t =
            lazy_t<not_equal_to_t_, type_t, other_t>;


        /// Wrapper for greater
        /// operator
        template < typename type_t,
                 typename other_t >
        using greater_t_ =
            bool_t_ < (v_<type_t>
                       > v_<other_t>) >;


        /// t_ shortcut for greater_t_
        template < typename type_t,
                 typename other_t >
        using greater_t =
            lazy_t<greater_t_, type_t, other_t>;


        /// Wrapper for less
        /// operator
        template < typename type_t,
                 typename other_t >
        using less_t_ =
            bool_t_ < (v_<type_t>
                       < v_<other_t>) >;


        /// t_ shortcut for less_t_
        template < typename type_t,
                 typename other_t >
        using less_t =
            lazy_t<less_t_, type_t, other_t>;


        /// Wrapper for greater equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using greater_equal_t_ =
            bool_t_ < (v_<type_t>
                       >= v_<other_t>) >;


        /// t_ shortcut for greater_equal_t_
        template < typename type_t,
                 typename other_t >
        using greater_equal_t =
            lazy_t<greater_equal_t_, type_t, other_t>;


        /// Wrapper for less equal
        /// operator
        template < typename type_t,
                 typename other_t >
        using less_equal_t_ =
            bool_t_ < (v_<type_t>
                       <= v_<other_t>) >;


        /// t_ shortcut for less_equal_t_
        template < typename type_t,
                 typename other_t >
        using less_equal_t =
            lazy_t<less_equal_t_, type_t, other_t>;


        /// Wrapper for bit and
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_and_t_ =
            bool_t_ < v_<type_t>
            & v_<other_t >>;


        /// t_ shortcut for bit_and_t_
        template < typename type_t,
                 typename other_t >
        using bit_and_t =
            lazy_t<bit_and_t_, type_t, other_t>;


        /// Wrapper for bit or
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_or_t_ =
            bool_t_ < v_<type_t>
            | v_<other_t >>;


        /// t_ shortcut for bit_or_t_
        template < typename type_t,
                 typename other_t >
        using bit_or_t =
            lazy_t<bit_or_t_, type_t, other_t>;


        /// Wrapper for bit xor
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_xor_t_ =
            bool_t_ < v_<type_t>
            ^ v_<other_t >>;


        /// t_ shortcut for bit_xor_t_
        template < typename type_t,
                 typename other_t >
        using bit_xor_t =
            lazy_t<bit_xor_t_, type_t, other_t>;


        /// Wrapper for bit not
        /// operator
        template < typename type_t,
                 typename other_t >
        using bit_not_t_ =
            bool_t_ < ~v_<type_t >>;


        /// t_ shortcut for bit_not_t_
        template < typename type_t,
                 typename other_t >
        using bit_not_t =
            lazy_t<bit_not_t_, type_t, other_t>;

    }
}

#endif
