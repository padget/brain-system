#ifndef __BRAIN_META_CORE_SELECT_HPP__
# define  __BRAIN_META_CORE_SELECT_HPP__

#include "base.hpp"

namespace brain
{
    namespace meta
    {
        namespace core
        {
            namespace impl
            {
                /// Type selector based
                /// on bool value _test.
                /// If true, then_t is
                /// returned, else else_t
                /// is returned
                template < bool _test,
                         typename then_t,
                         typename else_t >
                struct if_c_;


                /// Specialization that
                /// returns then_t thanks
                /// to true value
                template < typename then_t,
                         typename else_t >
                struct if_c_<true, then_t, else_t>
                {
                    using type =
                        then_t;
                };


                /// Specialization that
                /// returns else_t thanks
                /// to false value
                template < typename then_t,
                         typename else_t >
                struct if_c_<false, then_t, else_t>
                {
                    using type =
                        else_t;
                };

                /// Type selector
                /// specialisation that
                /// returns then_t
                /// if_t is true
                /// else else_t
                template < typename test_t,
                         typename then_t,
                         typename else_t >
                struct if_
                {
                    using type =
                        type_<if_c_<v_<test_t>, then_t, else_t>> ;
                };


                /// Evaluates the lazy
                /// type corresponding
                /// of the test_t. Evaluates
                /// only one type. The other
                /// lazy type is not
                /// evaluated/instianted
                template < typename test_t,
                         typename lthen_t,
                         typename lelse_t >
                struct eval_if_
                {
                    using type =
                        type_<type_<if_<test_t, lthen_t, lelse_t>>>;
                };
            }


            /// type_ shorcut
            /// for if_
            template < typename test_t,
                     typename then_t,
                     typename else_t >
            using if_ =
                type_<impl::if_<test_t, then_t, else_t>>;


            /// type_ shortcut
            /// for eval_if_
            template < typename test_t,
                     typename lthen_t,
                     typename lelse_t >
            using eval_if_ =
                type_<impl::eval_if_<test_t, lthen_t, lelse_t>>;
        }
    }
}

#endif