#ifndef __BRAIN_META_RUNTIME_HPP__
# define __BRAIN_META_RUNTIME_HPP__

#include "list.hpp"

namespace brain
{
    namespace meta
    {

        /// //////////////// ///
        /// Runtime features ///
        /// //////////////// ///


        /// Execute the same
        /// algorithm func_t
        /// foreach types_t
        /// and can accumulate
        /// results with accum_t
        template < typename types_t,
                 template<typename> typename func_t,
                 typename accum_t = void >
        struct foreach_type;


        /// Specialization for
        /// void accum_t. The
        /// accum_t is not used.
        template < typename first_t,
                 typename next_t,
                 typename ... types_t,
                 template<typename> typename func_t >
        struct foreach_type<list<first_t, next_t, types_t...>, func_t, void>
        {
            /// Operator () for
            /// functor using
            template<typename ... args_t>
            constexpr void operator()(
                args_t && ... args)
            {
                func_t<first_t>()(args...);
                foreach_type<list<next_t, types_t...>, func_t, void>()(args...);
            }
        };


        /// Specialization for
        /// void accum_t. The
        /// accum_t is not used.
        template < typename last_t,
                 template<typename> typename func_t >
        struct foreach_type<list<last_t>, func_t, void>
        {
            /// Operator () for
            /// functor using
            template<typename ... args_t>
            constexpr void operator()(
                args_t && ... args)
            {
                func_t<last_t>()(args...);
            }
        };


        /// Specialization for an
        /// active accum_t. The func_t
        /// is executed for first_t
        /// and is prepared for next_t.
        /// The results are accumulates
        /// with accum_t
        template < typename first_t,
                 typename next_t,
                 typename ... types_t,
                 template<typename> typename func_t ,
                 typename accum_t >
        struct foreach_type<list<first_t, next_t, types_t...>, func_t, accum_t>
        {
            /// Operator () for
            /// functor using
            template<typename ... args_t>
            constexpr auto operator()(
                args_t && ... args)
            {
                /// Accumulates the results
                /// between first_t and next_t
                return accum_t()(func_t<first_t>()(args...),
                                 foreach_type<list<next_t, types_t...>, func_t, accum_t>()(args...));
            }
        };


        /// Specialization for an
        /// active accum_t. The func_t
        /// is executed for last_t
        template < typename last_t,
                 template<typename> typename func_t,
                 typename accum_t >
        struct foreach_type<list<last_t>, func_t, accum_t>
        {
            /// Operator () for
            /// functor using
            template<typename ... args_t>
            constexpr auto operator()(
                args_t && ... args)
            {
                /// Returns only the
                /// the results of last_t,
                /// there is no need of
                /// accum_t
                return func_t<last_t>()(args...);
            }
        };
    }
}

#endif
