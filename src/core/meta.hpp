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
            using t_ = typename type_t::type;


            /// Access to value member
            /// of type_t
            template<typename type_t>
            constexpr auto v_ = t_<type_t>::value;


            /// Access to value_type member
            /// of type_t
            template<typename type_t>
            using vt_ = typename t_<type_t>::value_type;


            /// Access to size member
            /// of type_t
            template<typename type_t>
            constexpr auto size_ = t_<type_t>::size;
        }


        /// Shortcut for member::t_
        template<typename type_t>
        using t_ = member::t_<type_t>;


        /// Shortcut for member::v_
        template<typename type_t>
        constexpr auto v_ = member::v_<type_t>;


        /// Shortcut for member::vt_
        template<typename type_t>
        using vt_ = member::vt_<type_t>;


        /// Shortcut for member::size_
        template<typename type_t>
        constexpr auto size_ = member::size_<type_t>;


        /// ///////////////////////// ///
        /// Wrapper for literal types ///
        /// ///////////////////////// ///
        namespace literal
        {
            /// Shortcut for
            /// std::integral_constant
            template < typename literal_t,
                     literal_t _l >
            using igral = std::integral_constant<literal_t, _l>;


            /// Wrapper for bool
            template<bool _b>
            using bool_ = igral<bool, _b>;


            /// Wrapper for short
            template<short _s>
            using short_ = igral<short, _s>;


            /// Wrapper for unsigned short
            template<unsigned short _us>
            using ushort_ = igral<unsigned short, _us>;


            /// Wrapper for char
            template<char _c>
            using char_ = igral<char, _c>;


            /// Wrapper for int
            template<int _i>
            using int_ = igral<int, _i>;


            /// Wrapper for long
            template<long _l>
            using long_ = igral<long, _l>;


            /// Wrapper for long long
            template<long long _ll>
            using longlong_ = igral<long long, _ll>;


            /// Wrapper for unsigned
            template<unsigned _u>
            using unsigned_ = igral<unsigned, _u>;


            /// Wrapper for unsigned long
            template<unsigned long _ul>
            using unsignedl_ = igral<unsigned long, _ul>;


            /// Wrapper for unsigned long long
            template<unsigned long long _ull>
            using unsignedll_ = igral<unsigned long long, _ull>;


            /// Wrapper for size_t
            template<std::size_t _s>
            using size_t_ = igral<std::size_t, _s>;
        }


        /// Shortcut for
        /// literal::bool_
        template<bool _b>
        using bool_ = literal::bool_<_b>;


        /// Shortcut for
        /// literal::short_
        template<short _s>
        using short_ = literal::short_<_s>;


        /// Shortcut for
        /// literal::ushort_
        template<unsigned short _us>
        using ushort_ = literal::ushort_<_us>;


        /// Shortcut for
        /// literal::char_
        template<char _c>
        using char_ = literal::char_<_c>;


        /// Shortcut for
        /// literal::int_
        template<int _i>
        using int_ = literal::int_<_i>;


        /// Shortcut for
        /// literal::long_
        template<long _l>
        using long_ = literal::long_<_l>;


        /// Shortcut for
        /// literal::longlong_
        template<long long _ll>
        using longlong_ = literal::longlong_<_ll>;


        /// Shortcut for
        /// literal::unsigned_
        template<unsigned _u>
        using unsigned_ = literal::unsigned_<_u>;


        /// Shortcut for
        /// literal::unsignedl_
        template<unsigned long _ul>
        using unsignedl_ = literal::unsignedl_<_ul>;


        /// Shortcut for
        /// literal::unsignedll_
        template<unsigned long long _ull>
        using unsignedll_ = literal::unsignedll_<_ull>;


        /// Shortcut for
        /// literal::size_t_
        template<std::size_t _s>
        using size_t_ = literal::size_t_<_s>;


        /// ////////////////////////////// ///
        /// Wrapper for constness keywords ///
        /// ////////////////////////////// ///
        namespace constkw
        {
            /// Wrapper for sizeof
            template<typename type_t>
            using sizeof_ = size_t_<sizeof(type_t)>;


            /// Wrapper for sizeof...
            template<typename ... types_t>
            using sizeof_pack_ = size_t_<sizeof...(types_t)>;


            /// Wrapper for alignof
            template<typename type_t>
            using alignof_ = size_t_<alignof(type_t)>;
        }


        /// Shortcut for
        /// constkw::sizeof_
        template<typename type_t>
        using sizeof_ = constkw::sizeof_<type_t>;


        /// Shortcut for
        /// constkw::sizeof_pack_
        template<typename ... types_t>
        using sizeof_pack_ = constkw::sizeof_pack_<types_t...>;


        /// Shortcut for
        /// constkw::alignof_
        template<typename type_t>
        using alignof_ = constkw::alignof_<type_t>;


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
                static constexpr auto size = v_<sizeof_pack_<types_t...>>;
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
            using front = t_<front_<list_t>>;


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
            using back = t_<back_<list_t>>;
        }


        /// Shortuct for pack::list
        template<typename ... types_t>
        using list = pack::list<types_t...>;
    }
}

#endif
