#ifndef __BRAIN_META_CORE_HPP__
# define __BRAIN_META_CORE_HPP__

#include <type_traits>

namespace brain
{
    namespace meta
    {
        /// //////////////////// ///
        /// Most common shortcut ///
        /// //////////////////// ///


        /// Access to type member
        /// of type_t
        template<typename type_t>
        using t_ =
            typename type_t::type;


        /// Access to value member
        /// of type_t
        template<typename type_t>
        constexpr decltype(t_<type_t>::value) v_ =
            t_<type_t>::value;


        /// ////////////////////////// ///
        /// Lazy instanciation of type ///
        /// ////////////////////////// ///


        /// Defers the instation of
        /// a template
        template < template<typename ...> typename func_t,
                 typename ... args_t >
        struct lazy_t_
        {
            using type =
                func_t<args_t...>;
        };


        /// t_ shortcut for defer_t_
        template < template<typename ...> typename func_t,
                 typename ... args_t >
        using lazy_t =
            t_<t_<lazy_t_<func_t, args_t...>>>;
            
            
        
    }
}

#endif
