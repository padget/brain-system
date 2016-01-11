#ifndef __BRAIN_META_KEYWORDS_HPP__
# define __BRAIN_META_KEYWORDS_HPP__

#include "fundamental.hpp"

namespace brain
{
    namespace meta
    {
        /// ////////////////////////////// ///
        /// Wrapper for constness keywords ///
        /// ////////////////////////////// ///


        /// Wrapper for sizeof
        template<typename type_t>
        using sizeof_t_ =
            size_t_<sizeof(type_t)>;


        /// t_ shortcut for sizeof_t_
        template<typename type_t>
        using sizeof_t =
            lazy_t<sizeof_t_, type_t>;


        /// Wrapper for sizeof...
        template<typename ... types_t>
        using sizeof_pack_t_ =
            size_t_<sizeof...(types_t)>;


        /// t_ shortcut for sizeof_pack_t_
        template<typename ... types_t>
        using sizeof_pack_t =
            lazy_t<sizeof_pack_t_, types_t...>;


        /// Wrapper for alignof
        template<typename type_t>
        using alignof_t_ =
            size_t_<alignof(type_t)>;


        /// t_ shortcut for alignof_t_
        template<typename type_t>
        using alignof_t =
            lazy_t<alignof_t_, type_t>;


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
    }
}


#endif
