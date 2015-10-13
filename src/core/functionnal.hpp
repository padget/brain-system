#ifndef __BRAIN_FUNCTIONNAL_HPP
#define __BRAIN_FUNCTIONNAL_HPP

#include "core.hpp"
#include <functional>
#include <type_traits>
#include <sstream>

namespace brain
{

    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//



    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//

   



    /*template<typename functor_t>
    class single_functor:
        public singleton<single_functor<functor_t>>
    {
            static const functor_t func;

        public:
            using functor_type = functor_t;

            template <typename ... args_t>
            auto operator()(args_t && ...args) const
            { return func(std::forward<args_t>(args)...); }

            template <typename ... args_t>
            auto operator()(arguments<args_t...> && args) const
            { return brain::expand(func, std::forward<arguments<args_t...>>(args)); }
    };

    template<typename functor_t>
    const functor_t single_functor<functor_t>::func;

    template<typename ... sfunctor_t>
    class _apply_on
    {
    };

    template<typename ... sfunctor_t>
    using apply_on = single_functor<_apply_on<sfunctor_t...>>;

    template<typename sfunctor_t, typename ... last_sfunctor_t>
    class _apply_on <sfunctor_t, last_sfunctor_t...>
    {
        public:
            template<typename ... args_t>
            inline auto operator()(args_t && ... args) const
            {
                return apply_on<last_sfunctor_t...>::single()
                       (sfunctor_t::single()(std::forward<args_t>(args)...));
            }
    };

    template<typename sfunctor_t>
    class _apply_on <sfunctor_t>
    {
        public:
            template<typename ... args_t>
            inline auto operator()(args_t && ... args) const
            { return sfunctor_t::single()(std::forward<args_t>(args)...); }
    };

    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//

    template<typename = void>
    class _nothing
    {
        public:
            inline void operator()() const
            {}
    };

    using nothing = single_functor<_nothing<>>;
    const auto& nothing_single = nothing::single();

    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//


    class _allocates
    {
        public:
            template<typename left_t, typename right_t>
            inline auto& operator()(left_t& left, right_t && right) const
            { return left = right; }
    };

    using allocates = brain::single_functor<_allocates>;
    const auto& allocates_single = allocates::single();

    class _equals
    {
        public:
            template<typename left_t, typename right_t>
            inline bool operator()(left_t && left, right_t && right) const
            { return left == right; }
    };

    using equals = brain::single_functor<_equals>;
    const auto& equals_single = equals::single();


    class _not
    {
        public:
            template<typename right_t>
            inline auto operator()(right_t && right) const
            { return !right; }
    };

    using not_t = brain::single_functor<_not>;
    const auto& not_single = not_t::single();

    using not_equals = apply_on<equals, not_t>;
    const auto& not_equals_single = not_equals::single();

    template<typename bool_sfunctor_t, typename ... sfunctor_t>
    class _multi_bool
    {
    };

    template<typename bool_sfunctor_t, typename ... sfunctor_t>
    using multi_bool = single_functor<_multi_bool<bool_sfunctor_t, sfunctor_t...>>;

    template<typename bool_sfunctor_t, typename sfunctor1_t, typename sfunctor2_t, typename ... sfunctor_t>
    class _multi_bool<bool_sfunctor_t, sfunctor1_t, sfunctor2_t, sfunctor_t...>
    {
        public:
            template<typename ... args_t>
            inline auto operator()(args_t && ... args) const
            {
                const auto& bool_sfunctor = bool_sfunctor_t::single();
                const auto& sfunctor1 = sfunctor1_t::single();
                const auto& sfunctor2 = sfunctor2_t::single();

                return bool_sfunctor(bool_sfunctor(sfunctor1(std::forward<args_t>(args)...),
                                                   sfunctor2(std::forward<args_t>(args)...)),
                                     multi_bool<bool_sfunctor_t, sfunctor1_t>::single()(std::forward<args_t>(args)...));
            }
    };

    template<typename bool_sfunctor_t, typename sfunctor_t>
    class _multi_bool<bool_sfunctor_t, sfunctor_t>
    {
        public:
            template<typename ... args_t>
            inline auto operator()(args_t && ... args) const
            {
                const auto& sfunctor = sfunctor_t::single();

                return sfunctor(std::forward<args_t>(args)...);
            }
    };

    class _and
    {
        public:
            template<typename left_t, typename right_t>
            inline auto operator()(left_t && left, right_t && right) const
            { return left && right;}
    };

    using and_t = single_functor<_and>;
    const auto& and_single = and_t::single();

    template<typename ... sfunctor_t>
    using _multi_and = multi_bool<and_t, sfunctor_t...>;

    template<typename ... sfunctor_t>
    using multi_and = single_functor<_multi_and<sfunctor_t...>>;

    class _or
    {
        public:
            template<typename left_t, typename right_t>
            inline auto operator()(left_t && left, right_t && right) const
            { return left || right;}
    };

    using or_t = single_functor<_or>;
    const auto& or_single = or_t::single();

    template<typename ... sfunctor_t>
    using _multi_or = multi_bool<or_t, sfunctor_t...>;

    template<typename ... sfunctor_t>
    using multi_or = single_functor<_multi_or<sfunctor_t...>>;

    class _superiors
    {
        public:
            template<typename left_t, typename right_t>
            inline auto operator()(left_t && left, right_t && right) const
            { return left > right;}
    };

    using superiors = single_functor<_superiors>;
    using sup = superiors;
    const auto& sup_single = sup::single();

    class _inferiors
    {
        public:
            template<typename left_t, typename right_t>
            inline auto operator()(left_t && left, right_t && right) const
            { return left < right;}
    };

    using inferiors = single_functor<_inferiors>;
    using inf = inferiors;
    const auto& inf_single = inf::single();

    using inferiors_or_equals = multi_or<equals, inferiors>;
    using superiors_or_equals = multi_or<equals, superiors>;

    using sup_eq = superiors_or_equals;
    using inf_eq = inferiors_or_equals;

    const auto& inf_eq_single = inf_eq::single();
    const auto& sup_eq_single = sup_eq::single();


    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//

    template<typename sfunctor_test_t, typename sfunctor_then_t>
    class _if
    {
            sfunctor_test_t test_func;
            sfunctor_then_t then_func;

        public:
            template<typename ... test_args_t, typename ... then_args_t>
            inline bool operator()(arguments<test_args_t...> && test_args, arguments<then_args_t...> && then_args) const
            {
                const auto& single_test = sfunctor_test_t::single();
                const auto& single_then = sfunctor_then_t::single();

                if(expand(single_test, std::forward<arguments<test_args_t...>>(test_args)))
                {
                    expand(single_then, std::forward<arguments<then_args_t...>>(then_args));
                    return true;
                }

                else return false;
            }
    };

    template<typename sfunctor_test_t, typename sfunctor_then_t>
    using if_t = single_functor<_if<sfunctor_test_t, sfunctor_then_t>>;


    template < typename sfunctor_test_t,
             typename sfunctor_then_t,
             typename sfunctor_else_t >
    class _if_else
    {
            sfunctor_test_t test_func;
            sfunctor_then_t then_func;
            sfunctor_else_t else_func;

        public:
            template < typename ... test_args_t,
                     typename ... then_args_t,
                     typename ... else_args_t
                     >
            inline bool operator()(arguments<test_args_t...> && test_args,
                                   arguments<then_args_t...> && then_args,
                                   arguments<else_args_t...> && else_args) const
            {
                const auto& single_test = sfunctor_test_t::single();
                const auto& single_then = sfunctor_then_t::single();
                const auto& single_else = sfunctor_else_t::single();

                if(expand(single_test, std::forward<arguments<test_args_t...>>(test_args)))
                    expand(single_then, std::forward<arguments<then_args_t...>>(then_args));

                else
                    expand(single_else, std::forward<arguments<else_args_t...>>(else_args));

                return true;
            }
    };

    template<typename sfunctor_test_t, typename sfunctor_then_t, typename sfunctor_else_t>
    using if_else_t = single_functor<_if_else<sfunctor_test_t, sfunctor_then_t, sfunctor_else_t>>;

    template<typename first_pair_sfunctor_t, typename ... pair_sfunctor_t>
    class _if_else_if;

    template<typename ... pair_sfunctor_t>
    using if_else_if_t = brain::single_functor<_if_else_if<pair_sfunctor_t...>>;

    template<typename first_pair_sfunctor_t, typename ... pair_sfunctor_t>
    class _if_else_if
    {
        public:
            template<typename if_args_t, typename then_args_t, typename... args_t>
            inline bool operator()(if_args_t && if_args, then_args_t && then_args, args_t && ... args) const
            {
                const auto& if_single = first_pair_sfunctor_t::first_type::single();
                const auto& then_single = first_pair_sfunctor_t::second_type::single();

                if(expand(if_single, if_args))
                {
                    expand(then_single, then_args);
                    return true;
                }

                else
                    return if_else_if_t<pair_sfunctor_t...>::single()(args...);
            }
    };

    template<typename first_pair_sfunctor_t>
    class _if_else_if<first_pair_sfunctor_t>
    {
        public:
            template<typename if_args_t, typename then_args_t>
            bool operator()(if_args_t && if_args, then_args_t && then_args) const
            {

                if(expand(first_pair_sfunctor_t::first_type::single(), if_args))
                {
                    expand(first_pair_sfunctor_t::second_type::single(), then_args);
                    return true;
                }

                else
                    return false;
            }
    };

    template <typename test_sfunctor_t>
    class _ternaire
    {
        public:
            template < typename var_t,
                     typename ... test_args_t,
                     typename true_var_t,
                     typename false_var_t >
            inline auto && operator()(var_t && var,
                                      arguments<test_args_t...> && test_args,
                                      true_var_t && true_var,
                                      false_var_t && false_var) const
            {
                if_else_t<test_sfunctor_t, allocates, allocates>::single()(
                    std::forward<arguments<test_args_t...>>(test_args),
                    std::forward_as_tuple(var, true_var),
                    std::forward_as_tuple(var, false_var)
                );

                return var;
            }
    };

    template < typename test_sfunctor_t>
    using ternaire = single_functor<_ternaire<test_sfunctor_t>>;

    template<typename test_sfunctor_t>
    const auto& ternaire_single = ternaire<test_sfunctor_t>::single();

    template<typename test_sfunctor_t, typename while_sfunctor_t>
    class _while
    {
        public:
            template<typename...test_args_t, typename ...while_args_t>
            inline void operator()(arguments<test_args_t...> && test_args,
                                   arguments<while_args_t...> && while_args)
            {
                const auto& test_single = test_sfunctor_t::single();
                const auto& while_single = while_sfunctor_t::single();

                while(expand(test_single, std::forward(test_args)))
                    expand(while_single, std::forward(while_args));
            }
    };

    template<typename test_sfunctor_t, typename while_sfunctor_t>
    using while_t = single_functor<_while<test_sfunctor_t, while_sfunctor_t>>;

    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//

    template<typename single_functor_t>
    class binary_arithmetic_on_list
    {
        public:

            template<typename type_t, typename ... types_t>
            auto operator()(type_t && t, types_t && ... ts) const
            {
                const auto& single = single_functor_t::single();
                auto && right = this->operator()(std::forward<types_t>(ts)...);

                return single(std::forward<type_t>(t), std::forward<type_t>(right));
            }

            template<typename type1_t, typename type2_t>
            auto operator()(type1_t && t, type2_t && t2) const
            {
                const auto& single = single_functor_t::single();
                return single(std::forward<type1_t>(t), std::forward<type2_t>(t2));
            }

            template<typename type_t>
            auto operator()(type_t && t) const
            { return t; }
    };


    template<typename type_t>
    using plus = single_functor<std::plus<type_t>>;
    template<typename type_t>
    using minus = single_functor<std::minus<type_t>>;
    template<typename type_t>
    using divides = single_functor<std::divides<type_t>>;
    template<typename type_t>
    using multiplies = single_functor<std::multiplies<type_t>>;

    template<typename res_t>
    using plus_list = binary_arithmetic_on_list<brain::plus<res_t>>;
    template<typename res_t>
    using minus_list = binary_arithmetic_on_list<brain::minus<res_t>>;
    template<typename res_t>
    using multiplies_list = binary_arithmetic_on_list<brain::multiplies<res_t>>;
    template<typename res_t>
    using divides_list = binary_arithmetic_on_list<brain::divides<res_t>>;

    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
    //--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//

    class _concatenates
    {
        public:
            template<typename string_t,  typename ... strings_t>
            inline auto operator()(string_t str, strings_t && ... strs) const
            { return concat(str) + concat(strs...); }

            template<typename string_t>
            inline auto operator()(string_t && str)
            {
                std::stringstream stream;
                stream << str;
                return stream.str();
            }
    };

    using concatenates = single_functor<_concatenates>;*/
}


#endif
