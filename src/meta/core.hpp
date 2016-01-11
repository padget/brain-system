#ifndef __BRAIN_META_CORE_HPP__
# define __BRAIN_META_CORE_HPP__

#include <type_traits>

namespace brain
{
    namespace meta
    {
        struct nil {};


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
            
        
        /// Wrapper for void
        template<typename ...>
        using void_t =
            void;


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


        /// /////////////////// ///
        /// Has Type Definition ///
        /// /////////////////// ///
        

        /// Determines if a
        /// type_t has the
        /// 'type' member
        template < typename ,
                 typename = void >
        struct has_type_t_:
                std::false_type
        {
        };


        /// Specialisation for
        /// has_type_ if type_t
        /// has 'type' member
        template<typename type_t>
        struct has_type_t_ < type_t,
                void_t<typename type_t::type> > :
                std::true_type
        {
        };


        /// Evaluates the result
        /// of t_<has_type_<type_t>>
        template<typename type_t>
        using has_type_t =
            lazy_t<has_type_t_, type_t>;
    }
}

#endif
