#ifndef __BRAIN_TEMPLATE_HPP
#define  __BRAIN_TEMPLATE_HPP

#include <string>
#include <sstream>
#include <array>
#include <memory>
#include <vector>
#include <limits>
#include <map>
#include <set>
#include <functional>
#include <type_traits>
#include <typeinfo>
#include <regex>
#include <utility>
#include <iostream>
#include <tuple>
#include <list>
#include "functionnal.hpp"
namespace brain
{
//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//

    template <typename t>
    using rem_cv_t = std::remove_cv_t<t>;

    template <typename t>
    using rem_ref_t = std::remove_reference_t<t>;

    template <typename t>
    using rem_ref_cv_t = brain::rem_cv_t<brain::rem_ref_t<t>>;

    template <typename t, typename t2>
    using enable_if_is_same_t = std::enable_if_t<std::is_same<t, t2>::value>;

    template <typename t, typename t2>
    using enable_if_is_abssame_t = std::enable_if_t<std::is_same<brain::rem_ref_cv_t<t>, brain::rem_ref_cv_t<t2>>::value>;

    template <typename t, typename t2>
    using enable_if_is_baseof_t = std::enable_if_t<std::is_base_of<brain::rem_ref_cv_t<t>, brain::rem_ref_cv_t<t2>>::value>;

    template <typename sptr>
    using enable_if_shared_ptr_t = std::enable_if_t<std::is_same<std::shared_ptr<typename std::pointer_traits<rem_ref_cv_t<sptr>>::element_type>, rem_ref_cv_t<sptr>>::value>;

    template <typename uptr>
    using enable_if_unique_ptr_t = std::enable_if_t<std::is_same<std::unique_ptr<typename std::pointer_traits<rem_ref_cv_t<uptr>>::element_type>, rem_ref_cv_t<uptr>>::value>;

    template <typename wptr>
    using enable_if_weak_ptr_t = std::enable_if_t<std::is_same<std::unique_ptr<typename std::pointer_traits<rem_ref_cv_t<wptr>>::element_type>, rem_ref_cv_t<wptr>>::value>;

    template <typename pointer>
    using enable_if_pointer_t = std::enable_if_t<std::is_pointer<pointer>::value>;

    template <typename ref>
    using enable_if_reference_t = std::enable_if_t<std::is_reference<ref>::value>;

    template <typename lref>
    using enable_if_lvalue_t = std::enable_if_t<std::is_lvalue_reference<lref>::value>;

    template <typename rref>
    using enable_if_rvalue_t = std::enable_if_t<std::is_rvalue_reference<rref>::value>;

    template <typename t>
    using enable_if_stringable_t = std::enable_if_t<std::is_convertible<t, std::string>::value>;

    template <typename sptr, typename specific>
    using enable_if_specific_shared_ptr_t = std::enable_if_t<std::is_same<std::shared_ptr<typename std::pointer_traits<brain::rem_ref_cv_t<sptr>>::element_type>, brain::rem_ref_cv_t<specific>>::value>;

    template <typename vec>
    using enable_if_vetor_t = std::enable_if_t<std::is_same<std::vector<typename vec::value_type>, vec>::value>;

    template <typename vec, typename specific>
    using enable_if_specific_vetor_t = std::enable_if_t<std::is_same<std::vector<typename brain::rem_ref_cv_t<vec>::value_type>, std::vector<brain::rem_ref_cv_t<specific>>>::value>;

    namespace fct
    {
        template<typename ... types_t>
        using arguments = std::tuple<types_t...>;

        template<typename sfunctor1_t, typename sfunctor2_t>
        using pair_sfunctor = std::pair<sfunctor1_t, sfunctor2_t>;

        template<typename tuple_t>
        using expand_index_sequence = std::make_index_sequence<std::tuple_size<std::decay_t<tuple_t>>::value>;

        template<typename func_t, typename tuple_t, size_t ... idx>
        inline auto expand(func_t && f, tuple_t && t, std::index_sequence<idx...> && index)
        { return std::forward<func_t>(f)(std::get<idx>(std::forward<tuple_t>(t))...); }

        template<typename func_t, typename tuple_t>
        inline auto expand(func_t && f, tuple_t && t)
        {
            return expand(std::forward<func_t>(f),
                          std::forward<tuple_t>(t),
                          expand_index_sequence<tuple_t>());
        }

        template < typename left_t,
                 typename right_t >
        inline constexpr auto equals(left_t && l,
                                     right_t && r)
        { return l == r; }

        template < typename left_t,
                 typename right_t >
        inline constexpr auto not_equals(left_t && l,
                                         right_t && r)
        { return not equals(l, r); }

        template< typename left_t>
        inline constexpr auto not_null(left_t && l)
        { return not_equals(l, nullptr); }

        template < typename left_t,
                 typename right_t >
        inline constexpr auto less(left_t && l,
                                   right_t && r)
        { return l < r; }

        template < typename left_t,
                 typename right_t >
        inline constexpr auto less_equal(left_t && l,
                                         right_t && r)
        { return l <= r; }

        template < typename left_t,
                 typename right_t >
        inline constexpr auto greater(left_t && l,
                                      right_t && r)
        { return l > r; }

        template < typename left_t,
                 typename right_t >
        inline constexpr auto greater_equal(left_t && l,
                                            right_t && r)
        { return l >= r; }

        template<typename container_t>
        inline constexpr auto empty(container_t && c)
        { return c.empty(); }

        template<typename container_t>
        inline constexpr auto not_empty(container_t && c)
        { return not empty(c); }

        template < typename left_t,
                 typename right_t >
        inline auto& assign(left_t && l,
                            right_t && r)
        { return l = r; }

        template < typename left_t >
        inline auto && assign(left_t && l,
                              left_t && r)
        { return l = r; }


        template <typename t>
        inline std::ostream& append(std::ostream& out, t && o) noexcept
        { return out << o; }

        template <typename t, typename ... T>
        inline std::ostream& append(std::ostream& out, t && o, T && ... os) noexcept
        {
            out << o;
            return append(out, os...);
        }

        template < typename container_t,
                 typename contained_t >
        auto& append(container_t& c,
                     contained_t && value)
        {
            c.push_back(value);
            return c;
        }

        template < typename container_t>
        auto& append_all(container_t& c,
                         typename container_t::const_iterator && first,
                         typename container_t::const_iterator && after_last)
        {
            c.insert(c.end(), first, after_last);
            return c;
        }

        template<typename container_t>
        auto& append_all(container_t& c, container_t& other)
        {
            append_all(c, other.cbegin(), other.cend());
            return c;
        }

        template<typename container_t>
        auto& append_all(container_t& c, container_t && other)
        {
            append_all(c, other.cbegin(), other.cend());
            return c;
        }

        template<typename type_t>
        inline std::string to_string(type_t && val)
        {
            return static_cast<std::string>(val);
        }

        template < typename left_t >
        inline auto p_inc(left_t& l)
        { return ++l; }

        template < typename left_t >
        inline auto s_inc(left_t && l)
        { return l++; }

        template < typename left_t,
                 typename right_t >
        inline constexpr auto logic_and(left_t && l,
                                        right_t && r)
        { return l and r; }

        template < typename left_t,
                 typename right_t >
        inline constexpr auto logic_or(left_t && l,
                                       right_t && r)
        { return l or r; }

        template< typename type_t>
        inline constexpr auto logic_not(type_t && r)
        { return not r; }

        template< typename type_t>
        inline auto && inner(type_t && o)
        { return *o; }

        template<typename type_t>
        inline auto && mv(type_t && o)
        { return std::move(o); }

        template < typename left_t,
                 typename right_t >
        inline auto adds(left_t && l,
                         right_t && r)
        { return l + r; }

        template < typename left_t,
                 typename right_t >
        inline auto substracts(left_t && l,
                               right_t && r)
        { return l - r; }

        template < typename arg_test_t,
                 typename predicate_t,
                 typename ... arg_then_t,
                 typename then_t >
        inline void do_if(predicate_t& predicate,
                          arg_test_t && arg_test,
                          then_t& then,
                          arg_then_t && ... arg_then)
        {
            if(predicate(std::forward<arg_test_t>(arg_test)))
                then(std::forward<arg_then_t>(arg_then)...);
        }

        template < typename ... arg_then_t,
                 typename then_t >
        inline void do_ifb(bool predicate,
                           then_t& then,
                           arg_then_t && ... arg_then)
        {
            if(predicate)
                then(std::forward(arg_then...));
        }

        template < typename container_t,
                 typename func_t >
        inline void for_each(container_t && c, func_t && f)
        { std::for_each(c.begin(), c.end(), f); }

        template<typename ... test_args_t, typename res_t, typename ... then_args_t>
        inline auto _if(std::function<bool(test_args_t...)>& test,
                        arguments<test_args_t...> && test_args,
                        std::function<res_t(then_args_t...)>& then,
                        arguments<then_args_t...> && then_args)
        {
            if(expand(test, test_args))
            {
                expand(then, then_args);
                return true;
            }

            return false;
        }
    }

    namespace tpl
    {
        struct no_type {};
        /**
         * @class if_else
         * @author bmathieu
         * @date 12/09/2015
         * @file template.hpp
         * @brief if_else enable to select a type if a condition is true or false.
         *
         * If 'test' is true so the return type is 'true_t', else the type 'false_t' is return.
         */
        template < bool test,
                 typename true_t,
                 typename false_t >
        struct if_else;

        /**
         * @brief Partial specialisation of if_else template for case 'true'.
         *        So the return 'type' is 'true_t'.
         */
        template < typename true_t,
                 typename false_t >
        struct if_else<true, true_t, false_t>
        {
            using type = true_t;
        };

        /**
         * @brief Partial specialisation of if_else template for case 'false'.
         *        So the return 'type' is 'false_t'.
         */
        template < typename true_t,
                 typename false_t >
        struct if_else<false, true_t, false_t>
        {
            using type = false_t;
        };

        /**
         * @brief Shortcut to access to 'type' of template if_else.
         */
        template < bool test,
                 typename true_t,
                 typename false_t >
        using if_else_t = typename if_else<test, true_t, false_t>::type;

        /**
         * @class type_list
         * @author bmathieu
         * @date 12/09/2015
         * @file template.hpp
         * @brief type_list is a template that represents a type list !
         *
         * @member 'type_support' : internal type that support the list.
         * @member 'last_idx' : sizeof...(types_t) - 1.
         */
        template <typename... types_t>
        struct type_list
        {
            using types_support = std::tuple<types_t...>;
            static constexpr size_t last_idx = std::tuple_size<types_support>::value - 1;
        };

        template<typename ... types_t>
        constexpr size_t type_list<types_t...>::last_idx;

        /**
         * @class type_by_idx
         * @author bmathieu
         * @date 12/09/2015
         * @file template.hpp
         * @brief Retrieve a type from a type_list by its index in the list.
         */
        template < std::size_t idx,
                 typename type_list_t/*,
                 typename = std::enable_if_t<fct::less_equal(idx, type_list_t::last_idx) >*/ >
        using type_by_idx = typename std::tuple_element<idx, typename type_list_t::types_support>::type;

        /**
         * @class type_by_idx
         * @author bmathieu
         * @date 12/09/2015
         * @file template.hpp
         * @brief Retrieve a type from a type_list by its index in the list.
         */
        template < std::size_t idx,
                 typename type_list_t/*,
                 typename = std::enable_if_t<fct::less_equal(idx, type_list_t::last_idx) >*/ >
        using type_by_reverse_idx = typename std::tuple_element < type_list_t::last_idx - idx,
              typename type_list_t::types_support >::type;

        /**
         * @class id_type
         * @author bmathieu
         * @date 12/09/2015
         * @file template.hpp
         * @brief Used to give a type and its value to other class
         */
        template < typename enum_t,
                 enum_t _id >
        struct id_type
        {
            using enum_type = enum_t;
            static constexpr enum_type id {_id};
        };

        template < typename enum_t,
                 enum_t _id >
        constexpr enum_t id_type<enum_t, _id>::id;


        /**
         * @class type_by_id
         * @author bmathieu
         * @date 12/09/2015
         * @file template.hpp
         * @brief Retrieve a type by an 'id' from a type list.
         */
        template < typename id_type,
                 id_type _id,
                 typename type_list_t,
                 size_t idx = type_list_t::last_idx >
        struct type_by_id
        {
            using type = tpl::if_else_t < fct::equals(_id, type_by_idx<idx, type_list_t>::id),
                  type_by_idx<idx, type_list_t>,
                  typename type_by_id < id_type, _id, type_list_t, idx - 1 >::type >;
        };

        /**
         * @brief Partial specialisation of type_by_id for the case 'idx' = 0.
         */
        template < typename id_type,
                 id_type _id,
                 typename type_list_t >
        struct type_by_id<id_type, _id, type_list_t , 0>
        {
            using type = tpl::if_else_t < fct::equals(_id, type_by_idx<0, type_list_t>::id),
                  type_by_idx<0, type_list_t>, no_type >;
        };

        /**
         * @class in_type_list
         * @author bmathieu
         * @date 14/09/2015
         * @file template.hpp
         * @brief Determines if 'type_t' is in the type list 'type_list_t'.
         */
        template < typename type_t,
                 typename type_list_t,
                 size_t _idx = type_list_t::last_idx >
        struct in_type_list
        {
            static constexpr bool value = fct::logic_or(std::is_same<type_by_reverse_idx<_idx, type_list_t>, type_t>::value,
                                          in_type_list < type_t, type_list_t, _idx - 1 >::value);
        };

        template < typename type_t,
                 typename type_list_t,
                 size_t _idx >
        constexpr bool in_type_list<type_t, type_list_t, _idx>::value;

        /**
         * @brief Partial specialisation for the case 0.
         */
        template < typename type_t,
                 typename type_list_t >
        struct in_type_list<type_t, type_list_t, 0>
        {
            static constexpr bool value = std::is_same<type_by_reverse_idx<0, type_list_t>, type_t>::value;
        };

        template < typename type_t,
                 typename type_list_t >
        constexpr bool in_type_list<type_t, type_list_t, 0>::value;





        /**
        * @class in_type_list
        * @author bmathieu
        * @date 14/09/2015
        * @file template.hpp
        * @brief Determines if 'type_t::id' is in the type list 'type_list_t'.
        */
        template < typename type_t,
                 typename type_list_t,
                 size_t _idx = type_list_t::last_idx >
        struct in_type_list_by_id
        {
            static constexpr bool value = fct::logic_or(fct::equals(type_by_reverse_idx<_idx, type_list_t>::id, type_t::id),
                                          in_type_list < type_t, type_list_t, _idx - 1 >::value);
        };

        template < typename type_t,
                 typename type_list_t,
                 size_t _idx >
        constexpr bool in_type_list_by_id<type_t, type_list_t, _idx>::value;

        /**
         * @brief Partial specialisation for the case 0.
         */
        template < typename type_t,
                 typename type_list_t >
        struct in_type_list_by_id<type_t, type_list_t, 0>
        {
            static constexpr bool value = fct::equals(type_by_reverse_idx<0, type_list_t>::id, type_t::id);
        };

        template < typename type_t,
                 typename type_list_t >
        constexpr bool in_type_list_by_id<type_t, type_list_t, 0>::value;
    }

    namespace asp
    {
        template<typename func_t>
        struct aspect
        {
            using func_type = func_t;

            template< typename ... args_t>
            auto operator()(args_t && ... args) const
            { return func_type()(std::forward<args_t>(args)...); }
        };

        template < typename aspect_t,
                 typename func_t >
        struct before
        {
                using aspect_type = aspect_t;

                template<typename ... args_t>
                auto operator()(args_t && ... args) const
                {
                    return exec < std::result_of_t < aspect_type(args_t && ...) > , args_t... > ()(std::forward<args_t>(args)...);
                }

            private:
                template < typename res_t,
                         typename ... args_t >
                struct exec
                {
                    res_t operator()(args_t && ...args)
                    {
                        func_t()();
                        auto && res = aspect_t()(std::forward<args_t>(args)...);
                        return res;
                    }
                };

                template < typename ... args_t >
                struct exec<void, args_t...>
                {
                    void operator()(args_t && ...args)
                    {
                        func_t()();
                        aspect_t()(std::forward<args_t>(args)...);
                    }
                };
        };

        template < typename aspect_t,
                 typename func_t >
        struct after
        {
                using aspect_type = aspect_t;

                template<typename ... args_t>
                auto operator()(args_t && ... args) const
                {
                    return exec < std::result_of_t < aspect_type(args_t && ...) > , args_t... > ()(std::forward<args_t>(args)...);
                }

            private:
                template < typename res_t,
                         typename ... args_t >
                struct exec
                {
                    res_t operator()(args_t && ...args)
                    {
                        auto && res = aspect_t()(std::forward<args_t>(args)...);
                        func_t()();
                        return res;
                    }
                };

                template < typename ... args_t >
                struct exec<void, args_t...>
                {
                    void operator()(args_t && ...args)
                    {
                        aspect_t()(std::forward<args_t>(args)...);
                        func_t()();
                    }
                };
        };



        template < typename aspect_t,
                 typename before_t,
                 typename after_t >
        struct around
        {
                using aspect_type = aspect_t;

                template<typename ... args_t>
                auto operator()(args_t && ... args) const
                { return exec < std::result_of_t < aspect_type(args_t && ...) > , args_t... > ()(std::forward<args_t>(args)...); }

            private:
                template < typename res_t,
                         typename ... args_t >
                struct exec
                {
                    res_t operator()(args_t && ...args)
                    {
                        before_t()();
                        auto && res = aspect_t()(std::forward<args_t>(args)...);
                        after_t()();
                        return res;
                    }
                };

                template < typename ... args_t >
                struct exec<void, args_t...>
                {
                    void operator()(args_t && ...args)
                    {
                        before_t()();
                        aspect_t()(std::forward<args_t>(args)...);
                        after_t()();
                    }
                };
        };
    }
}

#endif
