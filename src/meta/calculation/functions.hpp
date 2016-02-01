#ifndef __BRAIN_META_CALCULATION_FUNCTION_HPP__
# define  __BRAIN_META_CALCULATION_FUNCTION_HPP__

namespace meta
{
    /// Mathematical object
    /// that represents a
    /// fraction between
    /// two integers
    template < typename numerator_t,
             typename denominator_t >
    struct fraction
    {
        using num =
            numerator_t;

        using denom =
            denominator_t;

        using type =
            fraction;

        static decltype(v_<meta::divides_<num, denom>>) value = v_<meta::divides_<num, denom>>;
    };


    /// Accessor to
    /// num member
    template<typename fraction_t>
    using num_ =
        typename fraction_t::num;


    namespace impl
    {
        template < typename frac_t,
                 typename = void >
        struct has_num_member
        {
            using type =
                meta::false_;
        };

        template<typename frac_t>
        struct has_num_member<frac_t, meta::void_<typename frac_t::num>>
        {
            using type =
                meta::true_;
        };
    }

    template<typename frac_t>
    using has_num_member =
        type_<impl::has_num_member<frac_t>>;


    /// Accessor to
    /// denom member
    template<typename fraction_t>
    using denom_ =
        typename fraction_t::denom;


    namespace impl
    {
        template < typename frac_t,
                 typename = void >
        struct has_denom_member
        {
            using type =
                meta::false_;
        };

        template<typename frac_t>
        struct has_denom_member <
                frac_t,
                meta::void_<typename frac_t::denom> >
        {
            using type =
                meta::true_;
        };
    }


    template<typename frac_t>
    using has_denom_member =
        type_<impl::has_denom_member<frac_t>>;


    /// Accessor to
    /// res member
    template<typename fraction_t>
    using res_ =
        typename fraction_t::res;


    template<typename frac_t>
    using is_fraction_ =
        meta::and_ <
        has_num_member<frac_t>,
        has_denom_member<frac_t> >;


    namespace impl
    {
        template < typename igral_t,
                 typename exponent_t >
        struct pow_
        {
            using type =
                meta::eval_if_ < 
                    meta::is_fraction_<igral_t>,
                    meta::fraction<
                        pow_<meta::num_<igral_t>, exponent_t>, 
                        pow_<meta::denom_<igral_t>, exponent_t>>,
                    meta::multiplies_<igral_t, meta::type_<pow_<igral_t, meta::dec_<exponent_t>>> >>;
        };


        template < typename igral_t,
                 typename integral_t,
                 template <typename integral_t, integral_t> typename type_t >
        struct pow_<igral_t, type_t<integral_t, 1>>
        {
            using type = igral_t;
        };


        template < typename igral_t,
                 typename integral_t,
                 template<typename integral_t, integral_t> typename type_t >
        struct pow_<igral_t, type_t<integral_t, 0>>
        {
            using type = type_t<integral_t, 1>;
        };
    }


    template < typename igral_t,
             typename exponent_t >
    using pow_ =
        type_<impl::pow_<igral_t, exponent_t>>;


    namespace lazy
    {
        template < typename igral_t,
                 typename exponent_t >
        struct pow_ :
                meta::function_<meta::pow_, igral_t, exponent_t> {};
    }
}

#endif
