/*
 * core.hpp
 *
 *  Created on: 25 avr. 2015
 *      Author: bmathieu
 */

#ifndef CORE_CORE_HPP_
#define CORE_CORE_HPP_
#undef __cplusplus
#define __cplusplus 201400L
#include <string>
#include <sstream>
#include <array>
#include <memory>
#include <vector>
#include <forward_list>
#include <limits>
#include <map>
#include <set>
#include <functional>
#include <type_traits>
#include <typeinfo>
#include <regex>
#include <utility>
#include <iostream>
#include <fstream>
#include <tuple>
#include <list>
#include <chrono>
#include "macro.hpp"
#include "functionnal.hpp"
#include "meta.hpp"

#define WIN32

#if defined (WIN32)
#include <winsock2.h>
typedef int socklen_t;
#elif defined (linux)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
#endif


namespace brain
{
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


        template < typename type_t,
                 typename smart_t,
                 typename ...args_t >
        inline smart_t make_ptr(args_t && ...args)
        { return smart_t(new type_t(std::forward<args_t>(args)...)); }

        template < typename type_t,
                 typename ...args_t >
        inline std::unique_ptr<type_t> unique(args_t && ... args)
        { return std::make_unique<type_t>(std::forward<args_t>(args)...); }

        template < typename type_t,
                 typename ...args_t >
        inline std::shared_ptr<type_t> shared(args_t && ... args)
        { return std::make_shared<type_t>(std::forward<args_t>(args)...); }

        template<typename type_t>
        inline type_t && mv(type_t & o)
        { return std::move(o); }

        template<typename type_t>
        inline type_t && mv(type_t && o)
        { return std::move(o); }

        template < typename left_t,
                 typename right_t >
        inline constexpr auto adds(left_t && l,
                                   right_t && r)
        { return l + r; }

        template < typename left_t,
                 typename right_t >
        inline constexpr auto substracts(left_t && l,
                                         right_t && r)
        { return l - r; }

        template < typename left_t>
        inline constexpr auto minus(left_t && l)
        { return -l; }

        template < typename left_t,
                 typename right_t >
        inline constexpr auto multiplies(left_t && l,
                                         right_t && r)
        { return l * r; }

        template < typename left_t,
                 typename right_t >
        inline constexpr auto divides(left_t && l,
                                      right_t && r)
        { return l / r; }

        template < typename left_t,
                 typename right_t >
        inline constexpr auto modulo(left_t && l,
                                     right_t && r)
        { return l % r; }

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

        template < typename left_t >
        inline auto p_inc(left_t& l)
        { return ++l; }

        template < typename left_t >
        inline auto s_inc(left_t && l)
        { return l++; }

        template < typename left_t >
        inline auto p_decr(left_t& l)
        { return --l; }

        template < typename left_t >
        inline auto s_decr(left_t && l)
        { return l--; }

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

        template < typename left_t,
                 typename right_t >
        inline auto& assign(left_t& l,
                            right_t && r)
        {
            l = r;
            return l;
        }

        template < typename left_t,
                 typename right_t >
        inline auto& assign(left_t& l,
                            right_t & r)
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

        template<typename t>
        std::string to_string(t && o)
        {
            std::stringstream ss;
            return (ss << o, ss.str());
        }

        template<typename container_t>
        inline auto begin(container_t& c)
        { return std::begin(c);}

        template<typename container_t>
        inline auto begin(const container_t& c)
        { return std::begin(c);}

        template<typename container_t>
        inline constexpr auto cbegin(const container_t& c)
        { return fct::begin(c);}

        template<typename container_t>
        inline auto end(container_t& c)
        { return std::end(c);}

        template<typename container_t>
        inline auto end(const container_t& c)
        { return std::end(c);}

        template<typename container_t>
        inline constexpr auto cend(const container_t& c)
        { return fct::end(c);}

        template < typename container_t,
                 typename contained_t >
        inline auto& push(container_t& c,
                          contained_t && value)
        { return (c.push_back(value), c); }

        template < typename container_t,
                 typename contained_t >
        inline auto& push(container_t& c,
                          contained_t* value)
        { return (c.push_back(value), c); }

        template < typename container_t>
        inline auto& push_all(container_t& c,
                              typename container_t::const_iterator && first,
                              typename container_t::const_iterator && after_last)
        { return (c.insert(c.end(), first, after_last), c); }

        template<typename container_t>
        inline auto& push_all(container_t& c, container_t& other)
        { return push_all(c, other.cbegin(), other.cend()); }

        template<typename container_t>
        inline auto& push_all(container_t& c, container_t && other)
        { return push_all(c, other.cbegin(), other.cend()); }

        template<typename container_t>
        inline constexpr auto empty(container_t && c)
        { return c.empty(); }

        template<typename container_t>
        inline constexpr auto not_empty(container_t && c)
        { return logic_not(empty(c)); }

        template< typename type_t>
        inline auto& inner(type_t && o)
        { return *o; }

        template< typename type_t>
        inline auto& inner(type_t & o)
        { return *o; }

        template<typename type_t>
        inline void delete_if_not_null(type_t* p)
        { if(fct::not_null(p)) delete p; }


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

        template < typename iter_t,
                 typename func_t >
        inline void for_each(iter_t && first, iter_t last, func_t && f)
        { std::for_each(first, last, f); }

        template < typename container_t,
                 typename func_t >
        inline void for_each(container_t && c, func_t && f)
        { std::for_each(c.begin(), c.end(), f); }
    }

    namespace tpl
    {

    }



    namespace pattern
    {
        /**
         * @class stringable
         * @author bmathieu
         * @date 18/09/2015
         * @file pattern.hpp
         * @brief Enable to a class to be convertible to std::string
         */
        template<typename string_t>
        class stringable
        {
            public:
                virtual ~stringable() {};
                virtual operator string_t() noexcept = 0;
        };

        template <typename t>
        inline std::ostream& append(std::ostream& out, t && o) noexcept
        { return out << o; }

        template <typename t, typename ... T>
        inline std::ostream& append(std::ostream& out, t && o, T && ... os) noexcept
        {
            out << o;
            return append(out, os...);
        }

        template <typename str>
        std::string concat(str && ch1)
        {
            std::stringstream stream;
            return (stream << ch1, stream.str());
        }

        template <typename str1, typename ... str2>
        std::string concat(str1 && ch1, str2 && ... ch2)
        { return fct::adds(concat(ch1), concat(ch2...)); }

        /**
         * @class singleton
         * @author bmathieu
         * @date 18/09/2015
         * @file pattern.hpp
         * @brief Enable to generate a singleton.
         *
         * Warning : Don't forbidden to instanciate
         * other than the singleton.
         */
        template <typename T>
        class singleton
        {
            public:
                static T& single() noexcept
                {
                    static T obj;
                    return obj;
                }
        };

        template<typename type_t>
        class is_singleton :
            public std::integral_constant < bool,
            std::is_base_of<pattern::singleton<type_t>, type_t>::value >
        {
        };

        template<typename single_t>
        const auto& single = single_t::single();

        /**
         * @class cloneable
         * @author bmathieu
         * @date 18/09/2015
         * @file pattern.hpp
         * @brief Enable the clone method for a class
         */
        template<typename type_t>
        class cloneable
        {
                using type_ptr = std::unique_ptr<type_t>;
            public:
                virtual type_ptr clone() = 0;
        };

        template<typename type_t>
        using prototype = cloneable<type_t>;

        template<typename type_t>
        class is_clonable :
            public std::integral_constant < bool,
            std::is_base_of<pattern::cloneable<type_t>, type_t>::value >
        {
        };
    }

    namespace ptr
    {

        template<typename type_t>
        class client_ptr;

        /**
         * @class server_pointer_base
         * @author Benjamin
         * @date 01/10/2015
         * @file core.hpp
         * @brief Class defined for dynamic cast features.
         */
        class server_pointer_base
        {
            public:
                BRAIN_ALL_DEFAULT(server_pointer_base)
        };

        /**
         * @class server_ptr
         * @author bmathieu
         * @date 29/09/2015
         * @file core.hpp
         * @brief A server_ptr allows to define a smart pointer that's
         * the owner of a resource. This resource can be distributed
         * into several client_ptr.
         */
        template<typename type_t>
        class server_ptr:
            public server_pointer_base
        {
            public:
                using type = type_t;
                using pointer = type*;
                using ureference = type &&;
                using reference = type&;
                using client = client_ptr<type>;

            public:
                pointer m_owned {nullptr};
                std::list<client*> m_clients;

            public:
                /**
                 * @brief Build an empty server_ptr (bool(*this) is false)
                 */
                server_ptr() : server_pointer_base() {}

                /**
                 * @brief Build an server_ptr with owned
                 * @param owned pointer that will be owned by server_ptr
                 */
                server_ptr(pointer owned):
                    server_pointer_base(),
                    m_owned(owned) {}

                /**
                 * @brief Polymorphic builder.
                 * @param owned pointer of type or one of these deriveds.
                 */
                template < typename other_t,
                         typename = std::_Require < std::is_polymorphic<other_t>,
                         std::is_base_of<type, other_t> >>
                server_ptr(other_t* owned):
                    server_pointer_base(),
                    m_owned(owned) {}

                /**
                 * @brief Copy a server_ptr is forbidden.
                 */
                server_ptr(const server_ptr<type>&) = delete;

                /**
                 * @brief Move constructor
                 */
                server_ptr(server_ptr<type> && other) :
                    server_pointer_base(),
                    m_owned(other.release()),
                    m_clients(fct::mv(other.clients()))
                {
                    fct::for_each(m_clients, [&](auto * client)
                    { client->switch_server(this); });

                    other.m_clients.clear();
                }

                /**
                 * @brief Destructor. Delete owned pointer and
                 * unsubscribe all clients
                 */
                virtual ~server_ptr()
                {
                    std::cout << "delete server " << std::endl;
                    fct::delete_if_not_null(m_owned);
                    fct::for_each(m_clients, [&](auto * client)
                    { client->switch_server(); });
                }

            public:
                server_ptr<type>& operator=(const server_ptr<type> &) = delete;

                server_ptr<type>& operator=(server_ptr<type> && other)
                {
                    reset(other.release());

                    fct::assign(m_clients, fct::mv(other.m_clients));
                    fct::for_each(m_clients, [&](auto * client)
                    { (*client).switch_server(this); });
                    other.m_clients.clear();


                    return *this;
                }

            public:
                void reset(pointer p = nullptr)
                {
                    std::swap(m_owned, p);
                    fct::delete_if_not_null(p);
                }

                pointer release()
                {
                    pointer p = get();
                    fct::assign(m_owned, nullptr);
                    return p;
                }

                pointer get()
                { return m_owned; }

                const pointer get() const
                { return m_owned; }

                auto& clients()
                { return m_clients; }

                const auto& clients() const
                { return m_clients; }

            public:
                void subscribe(client_ptr<type>* subscriber)
                { m_clients.push_front(subscriber); }

                void unsubscribe(client_ptr<type>* subscriber)
                {
                    m_clients.remove_if([subscriber](auto * client)
                    { return fct::equals(subscriber, client); });
                }

            public:
                pointer operator->()
                { return m_owned; }

                const pointer operator->() const
                { return m_owned; }

                reference operator*()
                { return *m_owned; }

                const reference operator*() const
                { return *m_owned; }

                operator bool() const
                { return fct::not_null(m_owned); }

            public:
                auto make_client()
                { return client_ptr<type> {*this}; }
        };

        template < typename type_t,
                 typename base_t,
                 typename ... args_t >
        auto make_server(args_t && ... args)
        { return server_ptr<base_t>(new type_t(std::forward<args_t>(args)...)); }


        template<typename type_t>
        class client_ptr
        {
            public:
                using type = type_t;
                using pointer = type*;
                using reference = type&;

            public:
                server_pointer_base* m_server = nullptr;

            public:
                client_ptr() {}

                client_ptr(server_ptr<type>& server = nullptr) :
                    m_server {&server}
                { subscribe(); }

                client_ptr(const client_ptr<type>& other):
                    m_server {other.m_server}
                { subscribe(); }

                client_ptr(client_ptr<type> && other):
                    m_server {other.m_server}
                {
                    if(fct::not_null(other.m_server))
                        other.unsubscribe();

                    subscribe();
                }

                ~client_ptr()
                { unsubscribe(); }

            public:
                client_ptr<type>& operator=(const client_ptr<type>& other)
                {
                    if(fct::not_equals(this, &other))
                    {
                        unsubscribe();
                        fct::assign(m_server, other.m_server);
                        subscribe();
                    }

                    return fct::inner(this);
                }

                client_ptr<type>& operator=(client_ptr<type> && other) = delete;

                template<typename other_t>
                client_ptr<type>& operator=(const client_ptr<other_t>& other)
                {
                    if(fct::not_equals(this, &other))
                    {
                        unsubscribe();
                        fct::assign(m_server, other.m_server);
                        subscribe();
                    }

                    return fct::inner(this);
                }

            public:
                inline void unsubscribe()
                {
                    if(fct::not_null(m_server))
                    {
                        cast_server()->unsubscribe(this);
                        fct::assign(m_server, nullptr);
                    }
                }

                void subscribe()
                {
                    if(fct::not_null(m_server))
                        cast_server()->subscribe(this);
                }

            public:
                pointer operator->()
                {return cast_server()->get(); }

                const pointer operator->() const
                {return cast_server()->get(); }

                pointer get()
                {return cast_server()->get(); }

                const pointer get() const
                {return cast_server()->get(); }

                reference operator*()
                { return **cast_server(); }

                const reference operator*() const
                { return **cast_server(); }

                operator bool() const
                {
                    return fct::not_null(m_server)
                           and static_cast<bool>(fct::inner(this->cast_server()));
                }

                void switch_server(server_ptr<type>* s = nullptr)
                { fct::assign(m_server, s); }

                const server_ptr<type>* cast_server() const
                { return dynamic_cast<const server_ptr<type>*>(m_server); }

                server_ptr<type>* cast_server()
                { return dynamic_cast<server_ptr<type>*>(m_server); }
        };



    }

    namespace nat
    {
        /**
         * @class property
         * @author Benjamin
         * @date 23/09/2015
         * @file core.hpp
         * @brief
         */
        template < typename type_t>
        class property
        {
            public:
                using type = type_t;

            private:
                type m_prop;

            public:
                constexpr property()
                    : m_prop(type()) {}

                property(const type& value)
                    : m_prop(value) {}

                property(type && value)
                    : m_prop(value) {}

                template<typename other_t>
                property(other_t && value)
                    : m_prop(value) {}

                template<typename other_t>
                property(property<other_t> && value)
                    : m_prop(fct::mv(*value)) {}

                template<typename other_t>
                property(const property<other_t>& value)
                    : m_prop(*value) {}

            public:
                property& operator=(const type& value)
                {
                    fct::assign(m_prop, value);
                    return fct::inner(this);
                }

                property& operator=(type && value)
                {
                    fct::assign(m_prop, value);
                    return fct::inner(this);
                }

                template<typename other_t>
                property& operator=(other_t && value)
                {
                    fct::assign(m_prop, value);
                    return fct::inner(this);
                }

                template<typename other_t>
                property& operator=(property<other_t> && value)
                {
                    fct::assign(m_prop, fct::mv(*value));
                    return fct::inner(this);
                }

                template<typename other_t>
                property& operator=(const property<other_t>& value)
                {
                    fct::assign(m_prop, *value);
                    return fct::inner(this);
                }

            public:
                operator type&()
                { return m_prop; }

                operator const type&() const
                { return m_prop; }

            public:
                const auto* operator->() const
                { return m_prop.operator->(); }

                auto* operator->()
                { return m_prop.operator->(); }

            public:
                type& operator()() {return m_prop;}
                const type& operator()() const {return m_prop;}

                void operator()(const type& value) { fct::assign(m_prop, value); }
                void operator()(type && value) { fct::assign(m_prop, value); }
        };

        template <class type_t>
        std::ostream& operator<<(std::ostream& os, const property<type_t>& p)
        { return os << static_cast<const type_t&>(p); }

        template<typename type_t>
        using client_property = property<ptr::client_ptr<type_t>>;

        template<typename type_t>
        using server_property = property<ptr::server_ptr<type_t>>;


        /**
        * @class plmproperty
        * @author Benjamin
        * @date 23/09/2015
        * @file core.hpp
        * @brief Enable to encapsulate an class into a property
        * mainly for class/struct composition.
        */
        template < typename type_t,
                 typename plm_policy = std::unique_ptr<type_t >>
        class plmproperty
        {
            public:
                using type = type_t;
                using plmproperty_def = plmproperty<type_t>;

            private:
                plm_policy m_prop;

            public:
                constexpr plmproperty()
                    : m_prop(fct::make_ptr<type_t, plm_policy>()) {}

                plmproperty(const type& value)
                    : m_prop(fct::make_ptr<type_t, plm_policy>(value)) {}

                plmproperty(type && value)
                    : m_prop(fct::make_ptr<type_t, plm_policy>(value)) {}

                template<typename other_t>
                plmproperty(other_t && value)
                    : m_prop(fct::make_ptr<type_t, plm_policy>(value)) {}

                template<typename other_t>
                plmproperty(plmproperty<other_t> && value)
                    : m_prop(fct::make_ptr<type_t, plm_policy>(value)) {}

                template<typename other_t>
                plmproperty(const plmproperty<other_t> & value)
                    : m_prop(fct::make_ptr<type_t, plm_policy>(value)) {}

                plmproperty(plmproperty_def && value)
                    : m_prop(fct::make_ptr<type_t, plm_policy>(*value)) {}

                plmproperty(const plmproperty_def & value)
                    : m_prop(fct::make_ptr<type_t, plm_policy>(*value)) {}

            public:
                plmproperty_def& operator=(const type& value)
                {
                    fct::assign(*m_prop, value);
                    return fct::inner(this);
                }

                template<typename other_t>
                plmproperty_def& operator=(const plmproperty<other_t>& other)
                {
                    fct::assign(*m_prop, *other);
                    return fct::inner(this);
                }

                plmproperty_def& operator=(const plmproperty_def& other)
                {
                    fct::assign(*m_prop, *other);
                    return fct::inner(this);
                }

                plmproperty_def& operator=(type && value)
                {
                    fct::assign(*m_prop, *value);
                    return fct::inner(this);
                }

            public:
                operator type&()
                { return *m_prop; }

                operator const type&() const
                { return *m_prop; }

                template<typename other_t>
                operator other_t&()
                { return static_cast<other_t&>(*m_prop); }

                template<typename other_t>
                operator const other_t&() const
                { return static_cast<const other_t&>(*m_prop); }

            public:
                const type& operator*() const
                { return *m_prop; }

                type& operator*()
                { return *m_prop; }

            public:
                const auto* operator->() const
                { return m_prop.operator->(); }

                auto* operator->()
                { return m_prop.operator->(); }

            public:
                type& operator()() {return *m_prop;}
                const type& operator()() const {return *m_prop;}

                void operator()(const type& value) { fct::assign(*m_prop, value); }
                void operator()(type && value) { fct::assign(*m_prop, value); }
        };

        template <class type_t>
        std::ostream& operator<<(std::ostream& os, const plmproperty<type_t>& p)
        { return os << static_cast<const type_t&>(p); }

        template < typename type_t,
                 typename plm_policy = std::unique_ptr<type_t >>
        using plm = plmproperty<type_t, plm_policy>;

        /**
         * @class object
         * @author Benjamin
         * @date 21/09/2015
         * @file core.hpp
         * @brief Basic class of all hierarchal class tree.
         */
        class object
        {
            public:
                BRAIN_ALL_DEFAULT(object)
        };

        /**
         * @class default_value
         * @author Benjamin
         * @date 21/09/2015
         * @file core.hpp
         * @brief Enable to defined default value for any type.
         */
        template<typename type_t>
        struct default_value
        { static const type_t value; };

        template<>
        const bool default_value<bool>::value = false;
        template<>
        const int default_value<int>::value = 0;
        template<>
        const long default_value<long>::value = 0l;
        template<>
        const long long default_value<long long>::value = 0ll;
        template<>
        const unsigned default_value<unsigned>::value = 0u;
        template<>
        const long unsigned default_value<long unsigned>::value = 0ul;
        template<>
        const long long unsigned default_value<long long unsigned>::value = 0ull;
        template<>
        const float default_value<float>::value = 0.;
        template<>
        const double default_value<double>::value = 0.;
        template<>
        const long double default_value<long double>::value = 0.;
        /*
                template<typename inner_t>
                struct encapsulator_delegated
                {
                    virtual const inner_t& inner() const = 0;
                    virtual inner_t& inner() = 0;
                };

                struct nothing_delegated {};

                template < typename inner_t,
                         typename delegated_t = nothing_delegated >
                class encapsulator:
                    public nat::object,
                    public delegated_t
                {
                        friend delegated_t;

                    public:
                        using type = inner_t;

                    private:
                        type m_inner;

                    public:
                        const type& inner() const
                        { return m_inner; }

                        type& inner()
                        { return m_inner; }

                        void inner(const type& in)
                        { fct::assign(m_inner, in); }

                        void inner(type && in)
                        { fct::assign(m_inner, in); }

                    public:
                        encapsulator() : nat::object() {}

                        encapsulator(const encapsulator<type>& other):
                            nat::object(other),
                            m_inner(other.m_inner) {}

                        encapsulator(encapsulator<type> && other):
                            nat::object(other),
                            m_inner(fct::mv(other.m_inner)) {}

                        encapsulator(const type& in):
                            nat::object(),
                            m_inner(in) {}

                        encapsulator(type && in):
                            nat::object(),
                            m_inner(in) {}

                        template<typename other_t>
                        encapsulator(other_t && in):
                            nat::object(),
                            m_inner(static_cast<type>(in)) {}


                        virtual ~encapsulator() {}

                    public:
                        encapsulator<type>& operator=(const type& in)
                        {
                            fct::assign(m_inner, in);
                            return fct::inner(this);
                        }

                        encapsulator<type>& operator=(type && in)
                        {
                            fct::assign(m_inner, in);
                            return fct::inner(this);
                        }

                        template<typename other_t>
                        encapsulator<type> operator=(other_t && in)
                        {
                            fct::assign(m_inner, in);
                            return fct::inner(this);
                        }

                    public:
                        inline operator type() const
                        { return m_inner; }

                        operator type&()
                        { return m_inner; }

                    public:
                        template<typename other_t>
                        encapsulator<bool> operator==(encapsulator<other_t> && other) const
                        { return fct::equals(m_inner, other.m_inner); }

                        template<typename other_t>
                        encapsulator<bool> operator==(const encapsulator<other_t>& other) const
                        { return fct::equals(m_inner, other.m_inner); }

                        encapsulator<bool> operator==(const type& other) const
                        { return fct::equals(m_inner, other); }

                        encapsulator<bool> operator==(type && other) const
                        { return fct::equals(m_inner, other); }

                    public:
                        template<typename other_t>
                        encapsulator<bool> operator!=(encapsulator<other_t> && other) const
                        { return fct::not_equals(m_inner, other.m_inner); }

                        template<typename other_t>
                        encapsulator<bool> operator!=(const encapsulator<other_t>& other) const
                        { return fct::not_equals(m_inner, other.m_inner); }

                        encapsulator<bool> operator!=(const type& other) const
                        { return fct::not_equals(m_inner, other); }

                        encapsulator<bool> operator!=(type && other) const
                        { return fct::not_equals(m_inner, other); }

                    public:
                        encapsulator<bool> operator and (const encapsulator<bool>& other)
                        { return encapsulator<bool>(fct::logic_and(m_inner, other.m_inner)); }

                        encapsulator<bool> operator and (encapsulator<bool> && other)
                        { return encapsulator<bool>(fct::logic_and(m_inner, other.m_inner)); }

                        encapsulator<bool> operator and (const type& other)
                        { return encapsulator<bool>(fct::logic_and(m_inner, other)); }

                        encapsulator<bool> operator and (type && other)
                        { return encapsulator<bool>(fct::logic_and(m_inner, other)); }

                    public:
                        encapsulator<bool> operator or (const encapsulator<bool>& other)
                        { return encapsulator<bool>(fct::logic_or(m_inner, other.m_inner)); }

                        encapsulator<bool> operator or (encapsulator<bool> && other)
                        { return encapsulator<bool>(fct::logic_or(m_inner, other.m_inner)); }

                        encapsulator<bool> operator or (const type& other)
                        { return encapsulator<bool>(fct::logic_or(m_inner, other)); }

                        encapsulator<bool> operator or (type && other)
                        { return encapsulator<bool>(fct::logic_or(m_inner, other)); }

                    public :
                        encapsulator<bool> operator !()
                        { return encapsulator<bool>(fct::logic_not(m_inner)); }

                    public:
                        template<typename other_t>
                        encapsulator<type> operator+(encapsulator<other_t> && other) const
                        { return fct::adds(m_inner, other.m_inner); }

                        template<typename other_t>
                        encapsulator<type> operator+(const encapsulator<other_t>& other)  const
                        { return fct::adds(m_inner, other.m_inner); }

                        encapsulator<type> operator+(const type& other)  const
                        { return fct::adds(m_inner, other); }

                        encapsulator<type> operator+(type && other)  const
                        { return fct::adds(m_inner, other); }

                    public:
                        template<typename other_t>
                        encapsulator<type> operator-(encapsulator<other_t> && other) const
                        { return fct::substracts(m_inner, other.m_inner); }

                        template<typename other_t>
                        encapsulator<type> operator-(const encapsulator<other_t>& other)  const
                        { return fct::substracts(m_inner, other.m_inner); }

                        encapsulator<type> operator-(const type& other)  const
                        { return fct::substracts(m_inner, other); }

                        encapsulator<type> operator-(type && other)  const
                        { return fct::substracts(m_inner, other); }

                        encapsulator<type> operator-() const
                        { return fct::minus(m_inner); }

                    public:
                        template<typename other_t>
                        encapsulator<type> operator*(encapsulator<other_t> && other) const
                        { return fct::multiplies(m_inner, other.m_inner); }

                        template<typename other_t>
                        encapsulator<type> operator*(const encapsulator<other_t>& other)  const
                        { return fct::multiplies(m_inner, other.m_inner); }

                        encapsulator<type> operator*(const type& other)  const
                        { return fct::multiplies(m_inner, other); }

                        encapsulator<type> operator*(type && other)  const
                        { return fct::multiplies(m_inner, other); }

                    public:
                        template<typename other_t>
                        encapsulator<type> operator/(encapsulator<other_t> && other) const
                        { return fct::divides(m_inner, other.m_inner); }

                        template<typename other_t>
                        encapsulator<type> operator/(const encapsulator<other_t>& other)  const
                        { return fct::divides(m_inner, other.m_inner); }

                        encapsulator<type> operator/(const type& other)  const
                        { return fct::divides(m_inner, other); }

                        encapsulator<type> operator/(type && other)  const
                        { return fct::divides(m_inner, other); }

                    public:
                        template<typename other_t>
                        encapsulator<type> operator%(encapsulator<other_t> && other) const
                        { return fct::modulo(m_inner, other.m_inner); }

                        template<typename other_t>
                        encapsulator<type> operator%(const encapsulator<other_t>& other)  const
                        { return fct::modulo(m_inner, other.m_inner); }

                        encapsulator<type> operator%(const type& other)  const
                        { return fct::modulo(m_inner, other); }

                        encapsulator<type> operator%(type && other)  const
                        { return fct::modulo(m_inner, other); }

                    public:
                        template<typename other_t>
                        encapsulator<bool> operator>(encapsulator<other_t> && other) const
                        { return fct::greater(m_inner, other.m_inner); }

                        template<typename other_t>
                        encapsulator<bool> operator>(const encapsulator<other_t>& other)  const
                        { return fct::greater(m_inner, other.m_inner); }

                        encapsulator<bool> operator>(const type& other)  const
                        { return fct::greater(m_inner, other); }

                        encapsulator<bool> operator>(type && other)  const
                        { return fct::greater(m_inner, other); }

                    public:
                        template<typename other_t>
                        encapsulator<bool> operator<(encapsulator<other_t> && other) const
                        { return fct::less(m_inner, other.m_inner); }

                        template<typename other_t>
                        encapsulator<bool> operator<(const encapsulator<other_t>& other)  const
                        { return fct::less(m_inner, other.m_inner); }

                        encapsulator<bool> operator<(const type& other)  const
                        { return fct::less(m_inner, other); }

                        encapsulator<bool> operator<(type && other)  const
                        { return fct::less(m_inner, other); }
                    public:
                        template<typename other_t>
                        encapsulator<bool> operator>=(encapsulator<other_t> && other) const
                        { return fct::greater_equal(m_inner, other.m_inner); }

                        template<typename other_t>
                        encapsulator<bool> operator>=(const encapsulator<other_t>& other)  const
                        { return fct::greater_equal(m_inner, other.m_inner); }

                        encapsulator<bool> operator>=(const type& other)  const
                        { return fct::greater_equal(m_inner, other); }

                        encapsulator<bool> operator>=(type && other)  const
                        { return fct::greater_equal(m_inner, other); }

                    public:
                        template<typename other_t>
                        encapsulator<bool> operator<=(encapsulator<other_t> && other) const
                        { return fct::less_equal(m_inner, other.m_inner); }

                        template<typename other_t>
                        encapsulator<bool> operator<=(const encapsulator<other_t>& other)  const
                        { return fct::less_equal(m_inner, other.m_inner); }

                        encapsulator<bool> operator<=(const type& other)  const
                        { return fct::less_equal(m_inner, other); }

                        encapsulator<bool> operator<=(type && other)  const
                        { return fct::less_equal(m_inner, other); }

                    public:
                        auto& operator++()
                        {
                            fct::assign(m_inner, fct::adds(m_inner, 1));
                            return fct::inner(this);
                        }

                        auto operator++(int)
                        {
                            auto old = fct::inner(this);
                            fct::inner(this)++;
                            return old;
                        }

                        auto& operator--()
                        {
                            fct::assign(m_inner, fct::substracts(m_inner, 1));
                            return fct::inner(this);
                        }

                        auto operator--(int)
                        {
                            auto old = fct::inner(this);
                            fct::inner(this)--;
                            return old;
                        }
                };

                using boolean = encapsulator<bool>;

                using integer = encapsulator<int>;
                using linteger = encapsulator<long>;
                using llinteger = encapsulator<long long>;

                using sizeinteger = encapsulator<size_t>;

                using uinteger = encapsulator<unsigned>;
                using ulinteger = encapsulator<unsigned long>;
                using ullinteger = encapsulator<unsigned long long>;

                using floating = encapsulator<float>;
                using dfloating = encapsulator<double>;
                using ldfloating = encapsulator<long double>;

                template<typename container_t>
                struct container_delegated:
                    public encapsulator_delegated<container_t>
                {
                    boolean empty() const
                    { return fct::inner(this).inner().empty(); }

                    sizeinteger length() const
                    { return fct::inner(this).inner().length(); }
                };

                using string = encapsulator<std::string, container_delegated<std::string>>;

                template<typename type_t>
                inline std::ostream& operator<<(std::ostream& o, encapsulator<type_t> && enc)
                { return o << enc.inner(); }

                template<typename type_t>
                inline std::ostream& operator<<(std::ostream& o, const encapsulator<type_t> & enc)
                { return o << enc.inner(); }
        */
        /**
         * @class enum_iterator
         * @author Benjamin
         * @date 21/09/2015
         * @file core.hpp
         * @brief Enum iterator
         */
        /*template<typename enum_t, enum_t ... args >
         class enum_iterator:
             public nat::object,
             public std::iterator<std::input_iterator_tag, enum_t, ptrdiff_t, const enum_t*, const enum_t&>
         {
                 nat::uinteger m_pos;

             public:
                 static constexpr std::size_t size = sizeof...(args);
                 static constexpr std::array<enum_t, size> values = {args...};

             public:
                 constexpr enum_iterator() : m_pos(size) {}
                 constexpr enum_iterator(const enum_t val) : m_pos(std::distance(&values[0], std::find(&values[0], &values[size], val))) {}

             public:
                 const enum_t& operator*() const
                 { return values[m_pos]; }

                 enum_iterator& operator++()
                 { ++m_pos; return *this; }

                 enum_iterator operator++(int)
                 {
                     enum_iterator r(*this);
                     this->operator++();
                     return r;
                 }

             public:
                 constexpr nat::boolean operator==(enum_iterator const& rhs) const
                 {return fct::equals(m_pos, rhs.m_pos);}

                 constexpr nat::boolean operator!=(enum_iterator const& rhs) const
                 {return fct::not_equals(m_pos, rhs.m_pos);}

                 constexpr nat::boolean empty()
                 { return fct::equals(size, 0u); }

             public:
                 constexpr auto begin()
                 {
                     return fct::logic_not(fct::empty(*this)) ?
                            enum_iterator(values[0]) :
                            end();
                 }

                 constexpr auto end()
                 { return enum_iterator(); }
         };

         template<typename enum_t, enum_t... args>
         constexpr std::size_t enum_iterator<enum_t, args...>::size;

         template<typename enum_t, enum_t... args>
         constexpr std::array<enum_t,  enum_iterator<enum_t, args...>::size> enum_iterator<enum_t, args...>::values;*/
    }


    namespace logging
    {
        struct ROOT {};

        enum class Level
        { TRACE, DEBUG, INFO, WARN, ERROR, FATAL, ALL };

        template<Level lvl>
        inline auto& lvlname()
        { static std::string name = "UNDEFINED"; return name; }

        template<>
        inline auto& lvlname<Level::INFO>()
        { static std::string name = "INFO "; return name; }

        template<>
        inline auto& lvlname<Level::DEBUG>()
        { static std::string name = "DEBUG"; return name; }

        template<>
        inline auto& lvlname<Level::TRACE>()
        { static std::string name = "TRACE"; return name; }

        template<>
        inline auto& lvlname<Level::WARN>()
        { static std::string name = "WARN "; return name; }

        template<>
        inline auto& lvlname<Level::ERROR>()
        { static std::string name = "ERROR"; return name; }

        template<>
        inline auto& lvlname<Level::FATAL>()
        { static std::string name = "FATAL"; return name; }

        enum class Skip
        { UNDEFINED, DONT_SKIP, SKIP };


        template<typename key, typename value>
        std::map<key, value> concatmap(std::pair<key, value> && p, const std::map<key, value>& m, const std::map<key, value>& m3)
        {
            std::map<key, value> res(m);
            res[p.first] = p.second;
            res.insert(std::begin(m3), std::end(m3));

            return res;
        }

        template < Level lvl ,
                 typename type_t >
        class formatter;

        template < Level lvl,
                 typename t = void >
        class loggerconf
        {
            public:
                static Skip skip;
                static std::map<std::ostream*, std::ostream*> outs;
                static nat::plmproperty<formatter<lvl, t>> format;

                inline static void skip_policy(Skip skip) noexcept
                { fct::assign(loggerconf::skip, skip); }

                template < typename formatter_t = formatter<lvl, t>>
                inline static void format_policy(formatter_t && f)
                { format(formatter_t(f)); }
        };

        template <Level lvl, typename t>
        nat::plmproperty<formatter<lvl, t>> loggerconf<lvl, t>::format;

        template <Level lvl, typename t>
        Skip loggerconf<lvl, t>::skip = Skip::UNDEFINED;

        template <Level lvl, typename t>
        std::map<std::ostream*, std::ostream*> loggerconf<lvl, t>::outs =
            concatmap( {&std::cout, &(std::cout << std::boolalpha)}, loggerconf<Level::ALL>::outs, loggerconf<lvl>::outs);

        template < typename Type,
                 typename clock >
        class logger;

        template < typename T,
                 typename clock = std::chrono::system_clock >
        class timer
        {
                typename clock::time_point t0 = clock::now();


            public:

                static std::string now() noexcept
                {
                    auto time = clock::to_time_t(clock::now());
                    return std::string(ctime(&time));
                }

                template <typename ... t>
                void start(t && ... message) noexcept
                {
                    fct::assign(t0, clock::now());
                    logger<T, clock>::info(message...);
                }

                template <typename ... t>
                void step(t && ... message) noexcept
                {
                    logger<T, clock>::info(message..., " : ",
                    std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - t0).count(),
                    " ms");
                    fct::assign(t0, clock::now());
                }

                template <typename ... t>
                void stop(t && ... message) noexcept
                {
                    logger<T, clock>::info(message..., " : ",
                    std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - t0).count(),
                    " ms");
                    fct::assign(t0, clock::now());
                }

                template<typename func_t, typename ... args_t>
                static void bench(const std::string& func_name, func_t& func, args_t ... args)
                {
                    timer<T> t;
                    t.start("Start of benchmark of ", func_name);
                    func(args...);
                    t.stop("End of benchmark of ", func_name);
                }

                template<typename func_t, typename ... args_t>
                static void bench(const std::string& func_name, unsigned nb_try, func_t& func, args_t ... args)
                {
                    timer<T> t;
                    t.start("Start of benchmark of ", func_name);

                    for(unsigned u = 0; fct::less(u, nb_try); fct::p_inc(u))
                        func(args...);

                    t.stop("End of benchmark of ", func_name);
                }
        };

        template < Level lvl,
                 typename type_t >
        class formatter
        {
            public:
                template<typename ... args_t>
                void operator()(std::ostream& out, args_t && ... messages) const
                {
                    auto && now = timer<std::chrono::system_clock>::now();
                    now.erase(now.length() - 1, 1);
                    out << std::boolalpha;
                    fct::append(out, now, " : [", lvlname<lvl>(), "] (", typeid(type_t).name(), ") : ", messages...);
                    out << std::endl;
                }
        };


        template < Level lvl,
                 typename type_t,
                 typename clock = std::chrono::system_clock >
        struct log
        {
            template <typename ... t>
            void operator()(t && ... message) const
            {
                if((fct::equals(loggerconf<lvl>::skip, Skip::SKIP)
                        and fct::equals(loggerconf<lvl, type_t>::skip, Skip::DONT_SKIP))
                        or (fct::not_equals(loggerconf<lvl>::skip, Skip::SKIP)
                            and fct::not_equals(loggerconf<lvl, type_t>::skip, Skip::SKIP)))
                {
                    fct::for_each(loggerconf<lvl, type_t>::outs, [&](auto && out)
                    { (*loggerconf<lvl, type_t>::format)(*out.second, message...); });
                }
            }
        };

        template < typename type_t,
                 typename clock = std::chrono::system_clock >
        using debug = log<Level::DEBUG, type_t, clock>;

        template < typename type_t,
                 typename clock = std::chrono::system_clock >
        using trace = log<Level::TRACE, type_t, clock>;

        template < typename type_t,
                 typename clock = std::chrono::system_clock >
        using warn = log<Level::WARN, type_t, clock>;

        template < typename type_t,
                 typename clock = std::chrono::system_clock >
        using info = log<Level::INFO, type_t, clock>;

        template < typename type_t,
                 typename clock = std::chrono::system_clock >
        using error = log<Level::ERROR, type_t, clock>;

        template < typename type_t,
                 typename clock = std::chrono::system_clock >
        using fatal = log<Level::FATAL, type_t, clock>;

        template < typename type_t,
                 typename clock = std::chrono::system_clock >
        class logger :
            public pattern::singleton<logger<type_t, clock>>
        {
            public:
                template <typename ... t>
                inline static void info(t && ... message) noexcept
                { logging::info<type_t, clock>()(message...); }

                template <typename ... t>
                inline static void trace(t && ... message) noexcept
                {  logging::trace<type_t, clock>()(message...); }

                template <typename ... t>
                inline static void debug(t && ... message) noexcept
                {  logging::debug<type_t, clock>()(message...); }

                template <typename ... t>
                inline static void warn(t && ... message) noexcept
                {  logging::warn<type_t, clock>()(message...); }

                template <typename ... t>
                inline static void error(t && ... message) noexcept
                {  logging::error<type_t, clock>()(message...); }

                template <typename ... t>
                inline static void fatal(t && ... message) noexcept
                {  logging::fatal<type_t, clock>()(message  ...); }
        };
    }

    template<typename type_t>
    using logger = logging::logger<type_t>;

    template<typename type_t>
    using timer = logging::timer<type_t>;

    using ROOT = logging::ROOT;


    /**
    * Le namespace sys permet de mettre en place
    * la paradigme de programmation par system.
    *
    * Il s'agit de déclarer un system et d'un ensemble
    * de receiptor potentiels. On reliera le système à
    * un sous ensemble de receiptors. Ces receiptors
    * permettent de prendre en compte les évenements
    * reçus par le système.
    *
    * Un système peut être relié à d'autres système par
    * une sémantique d'émetteur -> recepteur.
    *
    * Il faut explicitement faire la liaison dans chacun
    * des sens. La liaison ne se fait que dans un seul
    * sens à la fois.
    */
    namespace sys
    {
        class system;
        class event;

        /**
         * @class event
         * @author Benjamin
         * @date 27/09/2015
         * @file core.hpp
         * @brief An event enable to transport information
         * from a system (emetor) to another system (more
         * precisly to an event_receiptor).
         */
        class event
        {
            public:
                nat::client_property<system> source;

            public:
                inline event(ptr::client_ptr<system> src) :
                    source(src)
                {}

                event(const event&) noexcept = default;
                event(event &&) noexcept = default;
                virtual ~event() noexcept = default;

            public:
                event& operator=(const event&) noexcept = default;
                event& operator=(event &&) noexcept = default;
        };

        /**
         * @class event_receiptor
         * @author Benjamin
         * @date 27/09/2015
         * @file core.hpp
         * @brief Functor that receives the events from systems
         */
        class event_receiptor
        {
                virtual void receipt(system&, event&) const = 0 ;

            public:
                virtual void operator()(system& s, event& e) const
                { receipt(s, e); }
        };

        using event_receiptor_u = std::unique_ptr<event_receiptor> ;

        /**
         * @class basic_receiptor
         * @author Benjamin
         * @date 27/09/2015
         * @file core.hpp
         * @brief With an event_t and a system_t, defines a
         * receiptor that's specific to the event_t and to
         * system_t.
         */
        template < typename event_t,
                 typename system_t >
        class basic_receiptor:
            public event_receiptor
        {
            public:
                virtual void act(system_t&, event_t&) const = 0;

                virtual void receipt(system& s, event& e) const
                {
                    if(fct::logic_and(fct::equals(typeid(e),
                                                  typeid(event_t)),
                                      fct::equals(typeid(s),
                                                  typeid(system_t))))
                    {
                        event_t& trs_e = dynamic_cast<event_t&>(e);
                        system_t& trs_s = dynamic_cast<system_t&>(s);
                        act(trs_s, trs_e);
                    }
                }
        };

        /**
         * @class system
         * @author Benjamin
         * @date 27/09/2015
         * @file core.hpp
         * @brief A system is a component that can receive
         * and send events.
         */
        class system:
            public nat::object
        {
                using system_clt = ptr::client_ptr<system>;
                using systems_clt = std::vector<system_clt>;
                using event_receiptors_u = std::vector<event_receiptor_u>;

            public:
                nat::property<bool> autoconnected {nat::default_value<bool>::value};
                nat::property<event_receiptors_u> receiptors;
                nat::property<systems_clt> systems;

            public:
                BRAIN_ALL_DEFAULT(system)

            public:
                inline void addReceiver(const system_clt& receiver)
                {
                    if(receiver)
                        systems().push_back(receiver);
                }

                inline void addReceiver(system_clt && receiver)
                {
                    if(receiver)
                        systems().push_back(receiver);
                }

            public:
                inline void receive(event& e)
                {
                    fct::for_each(receiptors(), [&](auto & receiptor)
                    { (*receiptor)(*this, e); });
                }

                inline void send(event& e)
                {
                    if(autoconnected) this->receive(e);

                    fct::for_each(systems(), [&e](auto & system)
                    { if(system) system->receive(e); });
                }

            public:
                /*inline void bilink(std::initializer_list<system_clt> && _systems)
                {
                    fct::for_each(_systems, [this](auto & system)
                    {
                        this->addReceiver(system);
                        system->addReceiver(this);
                    });
                }*/
        };

        /**
         * @class system_with_receiptors
         * @author Benjamin
         * @date 27/09/2015
         * @file core.hpp
         * @brief Enable to generate a system_t with
         * receiptors_t as receiptors.
         */
        template < typename system_t,
                 typename ... receiptors_t >
        struct system_with_receiptors
        {
            auto operator()()
            {
                ptr::server_ptr<sys::system> s(new system_t());
                receiptors_builder<receiptors_t...>()(s->receiptors());
                return s;
            };

            template<typename ... receips_t>
            struct receiptors_builder;

            template < typename receiptor_t,
                     typename next_t,
                     typename ... other_t >
            struct receiptors_builder<receiptor_t, next_t, other_t...>
            {
                void operator()(std::vector<event_receiptor_u>& receiptors)
                {
                    receiptors.push_back(fct::unique<receiptor_t>());
                    receiptors_builder<next_t, other_t...>()(receiptors);
                }
            };

            template < typename receiptor_t>
            struct receiptors_builder<receiptor_t>
            {
                void operator()(std::vector<event_receiptor_u>& receiptors)
                { receiptors.push_back(fct::unique<receiptor_t>()); }
            };

        };

        /**
         * @class compound_system
         * @author Benjamin
         * @date 27/09/2015
         * @file core.hpp
         * @brief A compound_system is a component that can receive
         * and send events to subsystems.
         */
        class compound_system :
            public system
        {
                using system_clt = ptr::client_ptr<system>;
                using systems_clt = std::vector<system_clt>;

            public:
                nat::property<systems_clt> sub_systems;

            public:
                BRAIN_ALL_DEFAULT(compound_system)

            public:
                void subsend(event& e)
                {
                    fct::for_each(sub_systems(), [&e](auto & system)
                    { if(system) system->receive(e); });
                }

                /* void subbilink(std::initializer_list<system*> && systems)
                 {
                     fct::for_each(systems, [this](auto * system)
                     {
                         fct::push(sub_systems(), system);
                         system->addReceiver(this);
                     });
                 }*/
        };
    }


    enum class exitcode
    : int
    { WELL = 0, ERROR = 1 };

    /**
     *
     *
     *
     */
    namespace test
    {
        struct basic_test
        {
            nat::property<std::string> name;

            auto operator()()
            { return test(); }

            virtual bool test() = 0;
        };

        template <typename ... test_t>
        class test_suite;

        template <typename test_t>
        class test_suite<test_t>
        {
            public:
                inline void operator()()
                {
                    timer<test_t> t;

                    auto && test = test_t();
                    t.start("Start of ", test.name());

                    if(fct::logic_not(test()))
                        logger<test_t>::error(test.name(), " ... :(");

                    else
                        logger<test_t>::info(test.name(), " ... :)");

                    t.stop(" >> End of ", test.name());
                }
        };

        template < typename test_t,
                 typename next_t,
                 typename ... other_t >
        class test_suite<test_t, next_t, other_t...>
        {
            public:
                inline void operator()()
                {
                    auto && test = test_t();
                    timer<test_t> t;
                    t.start("Start of ", test.name());

                    if(fct::logic_not(test()))
                        logger<test_t>::error(test.name(), " ... :(");

                    else
                        logger<test_t>::info(test.name(), " ... :)");

                    t.stop(" >> End of ", test.name());

                    test_suite<next_t, other_t...>()();
                }
        };
    }




    namespace time
    {
        /*
                   template <typename integral>
                   inline bool isWilcarded(integral val)
                   { return fct::equals(std::numeric_limits<integral>::min(), val); }

                   template <typename year_type>
                   class date :
                       public object
                   {
                           using year_type_t = year_type;
                           using inner_year_type = typename year_type::type;

                           year_type m_year = std::numeric_limits<inner_year_type::type>::min();
                           int m_month      = std::numeric_limits<decltype(m_month)>::min();
                           int m_day        = std::numeric_limits<decltype(m_day)>::min();
                           int m_hour       = std::numeric_limits<decltype(m_hour)>::min();
                           int m_minute     = std::numeric_limits<decltype(m_minute)>::min();
                           int m_second     = std::numeric_limits<decltype(m_second)>::min();
                           int m_millis     = std::numeric_limits<decltype(m_millis)>::min();

                       public:

                           struct gregorian
                           {
                               static constexpr int ms_per_sec        = 1000;
                               static constexpr int sec_per_min       = 60;
                               static constexpr int min_per_hour      = 60;
                               static constexpr int hour_per_day      = 24;
                               static constexpr int month_per_year    = 12;
                               static constexpr int max_day_per_month = 31;
                               static const std::array<int, 12> day_per_month_nb;
                               static const std::array<int, 12> day_per_month_b;
                           };

                           static constexpr decltype(m_year) y_wilcard     = std::numeric_limits<decltype(m_year)>::min();
                           static constexpr decltype(m_month) m_wilcard    = std::numeric_limits<decltype(m_month)>::min();
                           static constexpr decltype(m_day) d_wilcard      = std::numeric_limits<decltype(m_day)>::min();
                           static constexpr decltype(m_hour) h_wilcard     = std::numeric_limits<decltype(m_hour)>::min();
                           static constexpr decltype(m_minute) min_wilcard = std::numeric_limits<decltype(m_minute)>::min();
                           static constexpr decltype(m_second) s_wilcard   = std::numeric_limits<decltype(m_second)>::min();
                           static constexpr decltype(m_millis) ms_wilcard  = std::numeric_limits<decltype(m_millis)>::min();

                       public:
                           date() = default;

                           date(decltype(m_year) y, decltype(m_month) m, decltype(m_day) d) :
                               m_hour(std::numeric_limits<decltype(m_hour)>::min()),
                               m_minute(std::numeric_limits<decltype(m_minute)>::min()),
                               m_second(std::numeric_limits<decltype(m_second)>::min()),
                               m_millis(std::numeric_limits<decltype(m_millis)>::min()) { }

                           date(
                               decltype(m_year) y,
                               decltype(m_month) m,
                               decltype(m_day) d,
                               decltype(m_hour) h,
                               decltype(m_minute) min,
                               decltype(m_second) s,
                               decltype(m_millis) ms) :
                               m_year(y),
                               m_month(m),
                               m_day(d),
                               m_hour(h),
                               m_minute(min),
                               m_second(s),
                               m_millis(ms) { }

                           date(
                               decltype(m_hour) h,
                               decltype(m_minute) min,
                               decltype(m_second) s,
                               decltype(m_millis) ms) :
                               m_hour(h),
                               m_minute(min),
                               m_second(s),
                               m_millis(ms) { }

                           date(const date<year_type_t>& other) :
                               m_year(other.m_year),
                               m_month(other.m_month),
                               m_day(other.m_day),
                               m_hour(other.m_hour),
                               m_minute(other.m_minute),
                               m_second(other.m_second),
                               m_millis(other.m_millis) { }

                           date(date<year_type_t> && other) :
                               m_year(std::move(other.m_year)),
                               m_month(std::move(other.m_month)),
                               m_day(std::move(other.m_day)),
                               m_hour(std::move(other.m_hour)),
                               m_minute(std::move(other.m_minute)),
                               m_second(std::move(other.m_second)),
                               m_millis(std::move(other.m_millis)) { }

                           ~date() { }

                       public:

                           date<year_type_t>& operator=(const date<year_type_t>& other)
                           {
                               if(fct::not_equals(this, &other))
                               {
                                   m_year = other.m_year;
                                   m_month = other.m_month;
                                   m_day = other.m_day;
                                   m_hour = other.m_hour;
                                   m_minute = other.m_minute;
                                   m_second = other.m_second;
                                   m_millis = other.m_millis;
                               }

                               return *this;
                           }

                           date<year_type_t>& operator=(date<year_type_t> && other)
                           {
                               if(fct::not_equals(this, &other))
                               {
                                   m_year = std::move(other.m_year);
                                   m_month = std::move(other.m_month);
                                   m_day = std::move(other.m_day);
                                   m_hour = std::move(other.m_hour);
                                   m_minute = std::move(other.m_minute);
                                   m_second = std::move(other.m_second);
                                   m_millis = std::move(other.m_millis);
                               }

                               return *this;
                           }

                       public:

                           void
                           check()
                           {
                               if(not isWilcarded(m_month))
                               {
                                   if(m_month < 1)
                                   { m_month = 1; }

                                   else if(m_month > gregorian::month_per_year)
                                   { m_month = gregorian::month_per_year; }
                               }

                               if(not isWilcarded(m_day))
                               {
                                   if(m_day < 1) { m_day = 1; }

                                   else if(not isWilcarded(m_month))
                                   {
                                       if(not isbissextile(m_year) and m_day > gregorian::day_per_month_nb[m_month])
                                       { m_day = gregorian::day_per_month_nb[m_month]; }

                                       else if(isbissextile(m_year) and m_day > gregorian::day_per_month_b[m_month])
                                       { m_day = gregorian::day_per_month_nb[m_month]; }
                                   }

                                   else if(m_day > gregorian::max_day_per_month)
                                   {m_day = gregorian::max_day_per_month;}
                               }

                               if(not isWilcarded(m_hour))
                               {
                                   if(m_hour < 0) { m_hour = 0; }

                                   else if(m_hour > gregorian::hour_per_day - 1)
                                   { m_hour = gregorian::hour_per_day - 1; }
                               }

                               if(not isWilcarded(m_minute))
                               {
                                   if(m_minute < 0) { m_minute = 0; }

                                   else if(m_minute > gregorian::min_per_hour - 1)
                                   { m_minute = gregorian::min_per_hour - 1; }
                               }

                               if(not isWilcarded(m_second))
                               {
                                   if(m_second < 0)
                                   { m_second = 0; }

                                   else if(m_second > gregorian::sec_per_min - 1)
                                   { m_second = gregorian::sec_per_min - 1; }
                               }

                               if(not isWilcarded(m_millis))
                               {
                                   if(m_millis < 0)
                                   { m_millis = 0; }

                                   else if(m_millis > gregorian::ms_per_sec - 1)
                                   { m_millis = gregorian::ms_per_sec - 1; }
                               }
                           }

                           static constexpr bool isbissextile(decltype(date::m_year) year)
                           {
                               return (fct::equals(year % 4, 0)
                                       and fct::not_equals(year % 100, 0))
                                      || fct::equals(year % 400, 0);
                           }

                           virtual operator std::string() noexcept
                           {
                               return concat("D:", (!isWilcarded(m_year) ? to_string(m_year) : "*"),
                               ":", (!isWilcarded(m_month) ? to_string(m_month) : "*"),
                               ":", (!isWilcarded(m_day) ? to_string(m_day) : "*"),
                               "_", (!isWilcarded(m_hour) ? to_string(m_hour) : "*"),
                               ":", (!isWilcarded(m_minute) ? to_string(m_minute) : "*"),
                               ":", (!isWilcarded(m_second) ? to_string(m_second) : "*"),
                               ".", (!isWilcarded(m_millis) ? to_string(m_millis) : "*"));
                           }

                       public:
                           BRAIN_GETTER_SETTER(year, decltype(m_year))
                           BRAIN_GETTER_SETTER(month, decltype(m_month))
                           BRAIN_GETTER_SETTER(day, decltype(m_day))
                           BRAIN_GETTER_SETTER(hour, decltype(m_hour))
                           BRAIN_GETTER_SETTER(minute, decltype(m_minute))
                           BRAIN_GETTER_SETTER(second, decltype(m_second))
                           BRAIN_GETTER_SETTER(millis, decltype(m_millis))
                   };

                   template < typename d1, typename d2,
                            typename = typename std::enable_if <
                            std::is_same<date<typename d1::year_type_t>, brain::rem_ref_cv_t<d1>>::value && std::is_same <
                            date<typename d2::year_type_t>, brain::rem_ref_cv_t<d2 >>::value >>
                   bool operator==(d1 && ldate, d2 && rdate)
                   {
                       bool res = true;

                       if(not isWilcarded(ldate.year())
                               and not isWilcarded(rdate.year()))
                           res &= fct::equals(ldate.year(), rdate.year());

                       if(!isWilcarded(ldate.month())
                               and not isWilcarded(rdate.month()))
                           res &= fct::equals(ldate.month(), rdate.month());

                       if(!isWilcarded(ldate.day())
                               and not isWilcarded(rdate.day()))
                           res &= fct::equals(ldate.day(), rdate.day());

                       if(!isWilcarded(ldate.hour())
                               and not isWilcarded(rdate.hour()))
                           res &= fct::equals(ldate.hour(), rdate .hour());

                       if(!isWilcarded(ldate.minute())
                               and not isWilcarded(rdate.minute()))
                           res &= fct::equals(ldate.minute(), rdate.minute());

                       if(!isWilcarded(ldate.second())
                               and not isWilcarded(rdate.second()))
                           res &= fct::equals(ldate.second(), rdate.second());

                       if(!isWilcarded(ldate.millis())
                               and not isWilcarded(rdate.millis()))
                           res &= fct::equals(ldate.millis(), rdate.millis());

                       return res;
                   }

                   template < typename d1,
                            typename d2,
                            typename = typename std::enable_if <
                            std::is_same<date<typename d1::year_type_t>, brain::rem_ref_cv_t<d1>>::value && std::is_same <
                            date<typename d2::year_type_t>, brain::rem_ref_cv_t<d2 >>::value >>
                   bool operator!=(d1 && ldate, d2 && rdate)
                   {
                       return not fct::equals(ldate, rdate);
                   }

                   template < typename d1, typename d2,
                            typename = typename std::enable_if <
                            std::is_same<date<typename d1::year_type_t>, brain::rem_ref_cv_t<d1>>::value && std::is_same <
                            date<typename d2::year_type_t>, brain::rem_ref_cv_t<d2 >>::value >>
                   bool operator<=(d1 && ldate, d2 && rdate)
                   {
                       return ldate < rdate
                              or fct::equals(ldate, rdate);
                   }

                   template < typename d1, typename d2,
                            typename = typename std::enable_if <
                            std::is_same<date<typename d1::year_type_t>, brain::rem_ref_cv_t<d1>>::value && std::is_same <
                            date<typename d2::year_type_t>, brain::rem_ref_cv_t<d2 >>::value >>
                   bool operator>=(d1 && ldate, d2 && rdate)
                   {
                       return ldate > rdate
                              or fct::equals(ldate, rdate);
                   }

                   template < typename d1, typename d2,
                            typename = typename std::enable_if <
                            std::is_same<date<typename d1::year_type_t>, brain::rem_ref_cv_t<d1>>::value && std::is_same <
                            date<typename d2::year_type_t>, brain::rem_ref_cv_t<d2 >>::value >>
                   bool operator<(d1 && ldate, d2 && rdate)
                   {
                       if(fct::not_equals(ldate, rdate))
                           if(not isWilcarded(ldate.year())
                                   and not isWilcarded(rdate.year()))
                               if(ldate.year() < rdate.year())
                                   return true;

                               else
                                   return false;

                           else if(not isWilcarded(ldate.month())
                                   and not isWilcarded(rdate.month()))
                               if(ldate.month() < rdate.month())
                                   return true;

                               else
                                   return false;

                           else if(not isWilcarded(ldate.day())
                                   and not isWilcarded(rdate.day()))
                               if(ldate.day() < rdate.day())
                                   return true;

                               else
                                   return false;

                           else if(not isWilcarded(ldate.hour())
                                   and not isWilcarded(rdate.hour()))
                               if(ldate.hour() < rdate.hour())
                                   return true;

                               else
                                   return false;

                           else if(not isWilcarded(ldate.minute())
                                   and not isWilcarded(rdate.minute()))
                               if(ldate.minute() < rdate.minute())
                                   return true;

                               else
                                   return false;

                           else if(not isWilcarded(ldate.second())
                                   and not isWilcarded(rdate.second()))
                               if(ldate.second() < rdate.second())
                                   return true;

                               else
                                   return false;

                           else if(not isWilcarded(ldate.millis())
                                   and not isWilcarded(rdate.millis()))
                               if(ldate.millis() < rdate.millis())
                                   return true;

                               else
                                   return false;

                           else
                               return false;

                       else
                           return false;
                   }

                   template < typename d1,
                            typename d2,
                            typename = typename std::enable_if < std::is_same < date<typename d1::year_type_t>,
                            brain::rem_ref_cv_t<d1 >>::value && std::is_same <
                            date<typename d2::year_type_t>, brain::rem_ref_cv_t<d2 >>::value >>
                   bool operator>(d1 && ldate, d2 && rdate)
                   {
                       return !(ldate <= rdate);
                   }
        */
    }



    template <typename T>
    std::string vec2str(const std::vector<T>& vec)
    {
        std::stringstream ss;

        for(const T & el : vec)
            ss << el;

        return ss.str();
    }

    template <typename T>
    std::string vec2str(std::vector<T> && vec)
    {
        std::stringstream ss;

        for(const T & el : vec)
            ss << el;

        return ss.str();
    }


    template<typename T>
    std::ostream& operator<< (std::ostream& out, const std::vector<T>& vec)
    {
        for(const auto & t : vec)
            out << t;

        return out;
    }

    template<typename t, typename ... args>
    std::shared_ptr<t> sptr(args... a)
    { return std::make_shared<t>(a...); }

    template<typename string_t>
    inline string_t ifstream_to(const std::ifstream& in)
    {
        if(in.fail())
            return string_t();

        return string_t(std::istreambuf_iterator<char>(in.rdbuf()),
                        std::istreambuf_iterator<char>());
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

    namespace net
    {
        template<unsigned _port>
        class socket
        {
                SOCKET server_sock = 0;
                SOCKET client_sock = 0;
                bool isServer = true;
                int domain = ;
#if defined (WIN32)
                static WSADATA wsadata;
#endif
            public:
                socket();
                socket(int domain, int type, bool isServer, int protocol = 0);
                socket(const Socket& other);
                virtual ~socket();
                socket& operator=(const socket& other);
                void srvBind(unsigned short port, unsigned long type = INADDR_ANY) throw(BindException);
                void srvListening(int backlog = 1) throw(ListenException);
                void srvAccept() throw(AcceptException);
                void cltConnect(std::string& addr, unsigned short port) throw(ConnectException);
                void bthSend(const char* buffer, unsigned bufferSize);
                void bthRecv(char* buffer, unsigned bufferSize);
                void bthShutdown(int how);
                int bthClose();
                static int initSystem();
                static int cleanSystem();
                SOCKET  getSocket();
        };
    }
}

#endif /* CORE_CORE_HPP_ */
