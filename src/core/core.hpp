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
#include "meta.hpp"
#include "pattern.hpp"
#include "property.hpp"
#include "server_ptr.hpp"
/*#define WIN32

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
*/

/// Brain - System
namespace brain
{
    /// Launch any functor
    /// and return its result
    template < typename func_t,
             typename ... args_t >
    auto launch(args_t && ... args)
    {
        return func_t()(
                   std::forward<args_t>(args)...);
    }

    /// ///////////////////////// ///
    /// Basic Concepts / Patterns ///
    /// ///////////////////////// ///


    /// Declare that an
    /// object can be
    /// transformed into
    /// a string_t
    template<typename string_t>
    struct basic_stringable
    {
        /// Default virtual destructor
        /// for polymorphic inheritance
        virtual ~basic_stringable() = default;

        /// Operator string_t() for
        /// explicit casting operation
        /// Must be override for
        /// inheritance to provide cast
        virtual operator string_t() noexcept = 0;
    };


    /// Alias for basic_stringable
    /// of std::string
    using stringable =
        basic_stringable<std::string>;


    /// Alias for basic_stringable
    /// of std::wstring
    using wstringable =
        basic_stringable<std::wstring>;


    /// Design pattern Singleton.
    /// Initiate the singleton
    /// at the first invocation
    /// and keep it all over the
    /// execution of the program
    template <typename type_t>
    struct singleton :
            pattag::singleton
    {
        /// Lazy loading of
        /// the singleton
        static type_t& single() noexcept
        {
            static type_t obj;
            return obj;
        }
    };


    /// Returns true if
    /// type_t is derived
    /// from singleton<type_t>
    template<typename type_t>
    using is_singleton =
        std::is_base_of<singleton<type_t>, type_t>;


    /// Accessor for single()
    /// member of singleton_t
    template<typename singleton_t>
    const auto& single =
        singleton_t::single();


    /// Design pattern prototype
    /// Provides a pure clone methode
    template<typename type_t>
    struct prototype:
            pattag::prototype
    {
        /// Alias for
        /// unique_ptr<type_t>
        using type_ptr =
            std::unique_ptr<type_t>;


        /// Clone method that
        /// returns a copy of
        /// the prototype object
        virtual type_ptr clone() = 0;
    };


    /// Alias for
    /// prototype pattern
    template<typename type_t>
    using cloneable =
        prototype<type_t>;


    /// Returns true if
    /// type_t inherits from
    /// cloneable<type_t>
    template<typename type_t>
    using is_clonable =
        std::is_base_of<cloneable<type_t>, type_t>;


    /// Marshalling
    /// Unmarshalling
    template < typename input_t,
             typename output_t >
    struct serializer
    {
        /// Marshalling
        /// function
        virtual void marshall(
            const input_t& in,
            output_t& out) = 0;


        /// Unmarshalling
        /// function
        virtual void unmarshall(
            const output_t& out,
            input_t& in) = 0;
    };


    /// ///////////////////////////// ///
    /// Runtime Default value feature ///
    /// ///////////////////////////// ///


    /// Defines default
    /// value for type_t
    template <typename type_t>
    struct default_value :
            pattag::flyweight
    {
        using type = default_value;
        using value_type = type_t;


        /// Default value.
        /// Must be defined
        /// for each used type_t
        /// out of this class
        static const type_t value;
    };


    /// Alias for
    /// v_<default_value<type_t>>
    template <typename type_t>
    type_t default_v =
        default_value<type_t>::value;


    /// Default value for
    /// bool type
    template<>
    const bool
    default_value<bool>::value =
        false;


    /// Default value for
    /// int type
    template<>
    const int
    default_value<int>::value =
        0;


    /// Default value for
    /// long type
    template<>
    const long
    default_value<long>::value =
        0l;


    /// Default value for
    /// long long type
    template<>
    const long long
    default_value<long long>::value =
        0ll;


    /// Default value for
    /// unsigned type
    template<>
    const unsigned
    default_value<unsigned>::value =
        0u;


    /// Default value for
    /// long unsigned type
    template<>
    const long unsigned
    default_value<long unsigned>::value =
        0ul;


    /// Default value for
    /// long long unsigned type
    template<>
    const long long unsigned
    default_value<long long unsigned>::value =
        0ull;


    /// Default value for
    /// float type
    template<>
    const float
    default_value<float>::value =
        0.;


    /// Default value for
    /// double type
    template<>
    const double
    default_value<double>::value =
        0.;


    /// Default value for
    /// long double type
    template<>
    const long double
    default_value<long double>::value =
        0.;


    /// Default value for
    /// std::string type
    template<>
    const std::string
    default_value<std::string>::value =
        "";


    /// //////////////// ///
    /// Pattern Observer ///
    /// //////////////// ///


    /// TODO Doc
    template<typename type_t>
    struct observer
    {
        virtual void update(
            const type_t& observed) = 0;
    };


    /// ////// ///
    /// Object ///
    /// ////// ///


    /// Fundamental class
    /// for all class in
    /// brain-system framework
    class object
    {
            /// Static incremental ID
            static unsigned long long s_id;


        public:
            /// id of the current
            /// object. It's generated
            /// with static ID.
            monomorphe<unsigned long long> id {++s_id};


            /// Default constructor
            /// Increment s_id;
            object() = default;


            /// Copy constructor
            /// Increments s_id.
            object(
                const object& other):
                id(++s_id)
            {
            }


            /// Move constructor
            object(
                object &&) = default;


            /// Default destructor
            ~object() = default;


        public:
            /// Copy assignement
            /// Increments s_id
            object& operator=(
                const object& other)
            {
                if(this != &other)
                    id = ++s_id;

                return *this;
            }


            /// Move assignement
            object& operator=(
                object &&) = default;
    };


    /// The value of static ID
    /// is initialised to 0
    unsigned long long object::s_id {default_v<unsigned long long>};


    /// //////////////////////////// ///
    /// Unsorted // TODO : Sort Them ///
    /// //////////////////////////// ///
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

        template <typename left_t>
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

        template<typename left_t>
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

        template <typename left_t>
        inline auto p_inc(left_t& l)
        { return ++l; }

        template <typename left_t>
        inline auto s_inc(left_t && l)
        { return l++; }

        template <typename left_t>
        inline auto p_decr(left_t& l)
        { return --l; }

        template <typename left_t>
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

        template<typename type_t>
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

        template <typename container_t>
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

        template<typename type_t>
        inline auto& inner(type_t && o)
        { return *o; }

        template<typename type_t>
        inline auto& inner(type_t & o)
        { return *o; }

        template<typename type_t>
        inline void delete_if_not_null(type_t* p)
        {
            if(fct::not_null(p))
            { delete p; p = nullptr; }
        }


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

    namespace cops
    {
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
            std::wstringstream stream;
            return (stream << ch1, stream.str());
        }

        template <typename str1, typename ... str2>
        std::string concat(str1 && ch1, str2 && ... ch2)
        { return fct::adds(concat(ch1), concat(ch2...)); }

    }


    /// //////////////// ///
    /// Logging Features ///
    /// //////////////// ///
    namespace logging
    {
        struct ROOT {};

        enum class Level
        {
            TRACE,
            DEBUG,
            INFO,
            WARN,
            ERROR,
            FATAL,
            ALL
        };


        template<Level lvl>
        const std::string lvlstr = "UNDEFINED";

        template<>
        const std::string lvlstr<Level::TRACE> =
            "TRACE";


        template<>
        const std::string lvlstr<Level::DEBUG> =
            "DEBUG";


        template<>
        const std::string lvlstr<Level::INFO> =
            "INFO ";


        template<>
        const std::string lvlstr<Level::WARN> =
            "WARN ";


        template<>
        const std::string lvlstr<Level::ERROR> =
            "ERROR";


        template<>
        const std::string lvlstr<Level::FATAL> =
            "FATAL";


        enum class Skip
        {
            UNDEFINED,
            DONT_SKIP,
            SKIP
        };


        template < typename key,
                 typename value >
        std::map<key, value> concatmap(
            std::pair<key, value> && p,
            const std::map<key, value>& m,
            const std::map<key, value>& m2)
        {
            std::map<key, value> res(m);
            res[p.first] = p.second;

            res.insert(std::begin(m2),
                       std::end(m2));

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
                static component<formatter<lvl, t>> format;


                inline static void skip_policy(
                    Skip skip) noexcept
                {
                    fct::assign(loggerconf::skip, skip);
                }


                template <typename formatter_t = formatter<lvl, t>>
                inline static void format_policy(
                    formatter_t && f)
                {
                    format(formatter_t(f));
                }
        };


        template < Level lvl,
                 typename t >
        component<formatter<lvl, t>> loggerconf<lvl, t>::format;


        template < Level lvl,
                 typename t >
        Skip loggerconf<lvl, t>::skip = Skip::UNDEFINED;


        template < Level lvl,
                 typename t >
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
                void start(
                    t && ... message) noexcept
                {
                    fct::assign(t0, clock::now());
                    logger<T, clock>::info(message...);
                }

                template <typename ... t>
                void step(
                    t && ... message) noexcept
                {
                    logger<T, clock>::info(message..., " : ",
                    std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - t0).count(),
                    " ms");
                    fct::assign(t0, clock::now());
                }

                template <typename ... t>
                void stop(
                    t && ... message) noexcept
                {
                    logger<T, clock>::info(message..., " : ",
                    std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - t0).count(),
                    " ms");
                    fct::assign(t0, clock::now());
                }

                template<typename func_t, typename ... args_t>
                static void bench(
                    const std::string& func_name,
                    func_t& func,
                    args_t ... args)
                {
                    timer<T> t;
                    t.start("Start of benchmark of ", func_name);
                    func(args...);
                    t.stop("End of benchmark of ", func_name);
                }

                template<typename func_t, typename ... args_t>
                static void bench(
                    const std::string& func_name,
                    unsigned nb_try,
                    func_t& func,
                    args_t ... args)
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
                void operator()(
                    std::ostream& out,
                    args_t && ... messages) const
                {
                    auto && now = timer<std::chrono::system_clock>::now();
                    now.erase(now.length() - 1, 1);
                    out << std::boolalpha;
                    fct::append(out, now, " : [", lvlstr<lvl>, "] (", typeid(type_t).name(), ") : ", messages...);
                    out << std::endl;
                }
        };


        template < Level lvl,
                 typename type_t,
                 typename clock = std::chrono::system_clock >
        struct log
        {
            template <typename ... t>
            void operator()(
                t && ... message) const
            {
                if((fct::equals(loggerconf<lvl>::skip, Skip::SKIP)
                        and fct::equals(loggerconf<lvl, type_t>::skip, Skip::DONT_SKIP))
                        or (fct::not_equals(loggerconf<lvl>::skip, Skip::SKIP)
                            and fct::not_equals(loggerconf<lvl, type_t>::skip, Skip::SKIP)))
                {
                    for(auto & out : loggerconf<lvl, type_t>::outs)
                    {
                        brain::get(loggerconf<lvl, type_t>::format)(*out.second, message...);
                    }
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
            public singleton<logger<type_t, clock>>
        {
            public:
                template <typename ... t>
                inline static void info(
                    t && ... message) noexcept
                {
                    logging::info<type_t, clock>()(message...);
                }


                template <typename ... t>
                inline static void trace(
                    t && ... message) noexcept
                {
                    logging::trace<type_t, clock>()(message...);
                }


                template <typename ... t>
                inline static void debug(
                    t && ... message) noexcept
                {
                    logging::debug<type_t, clock>()(message...);
                }


                template <typename ... t>
                inline static void warn(
                    t && ... message) noexcept
                {
                    logging::warn<type_t, clock>()(message...);
                }


                template <typename ... t>
                inline static void error(
                    t && ... message) noexcept
                {
                    logging::error<type_t, clock>()(message...);
                }


                template <typename ... t>
                inline static void fatal(
                    t && ... message) noexcept
                {
                    logging::fatal<type_t, clock>()(message  ...);
                }
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
        /*class event
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
        };*/

        /**
         * @class event_receiptor
         * @author Benjamin
         * @date 27/09/2015
         * @file core.hpp
         * @brief Functor that receives the events from systems
         */
        /* class event_receiptor
         {
                 virtual void receipt(system&, event&) const = 0 ;

             public:
                 virtual void operator()(system& s, event& e) const
                 { receipt(s, e); }
         };

         using event_receiptor_u = std::unique_ptr<event_receiptor> ;*/

        /**
         * @class basic_receiptor
         * @author Benjamin
         * @date 27/09/2015
         * @file core.hpp
         * @brief With an event_t and a system_t, defines a
         * receiptor that's specific to the event_t and to
         * system_t.
         */
        /*     template < typename event_t,
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
             };*/

        /**
         * @class system
         * @author Benjamin
         * @date 27/09/2015
         * @file core.hpp
         * @brief A system is a component that can receive
         * and send events.
         */
        /*    class system:
                public object
            {
                    using system_clt = ptr::client_ptr<system>;
                    using systems_clt = std::vector<system_clt>;
                    using event_receiptors_u = std::vector<event_receiptor_u>;

                public:
                    property<bool> autoconnected {default_v<bool>};
                    property<event_receiptors_u> receiptors;
                    property<systems_clt> systems;

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
        /* };*/

        /**
         * @class system_with_receiptors
         * @author Benjamin
         * @date 27/09/2015
         * @file core.hpp
         * @brief Enable to generate a system_t with
         * receiptors_t as receiptors.
         */
        /*   template < typename system_t,
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

               template <typename receiptor_t>
               struct receiptors_builder<receiptor_t>
               {
                   void operator()(std::vector<event_receiptor_u>& receiptors)
                   { receiptors.push_back(fct::unique<receiptor_t>()); }
               };

           };*/

        /**
         * @class compound_system
         * @author Benjamin
         * @date 27/09/2015
         * @file core.hpp
         * @brief A compound_system is a component that can receive
         * and send events to subsystems.
         */
        /*class compound_system :
            public system
        {
                using system_clt = ptr::client_ptr<system>;
                using systems_clt = std::vector<system_clt>;

            public:
                property<systems_clt> sub_systems;

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
        /*};*/
    }


    enum class exitcode
    : int
    { WELL = 0, CRITIC = 1 };


    namespace test
    {
        class basic_test
        {
                /// List of test steps
                std::list<std::pair<bool, std::string>> m_steps;


                /// More length
                /// description
                /// between all
                /// steps
                size_t m_lengther_description {default_v<size_t>};

            public:
                /// Return the name
                /// of the test
                const std::string name() const
                {
                    return typeid(*this).name();
                };


                /// Getter on 
                /// m_lengther_description
                const size_t lengthest() const
                {
                    return m_lengther_description;
                }
                

                /// Add a step to the test
                void add_step(
                    bool expr,
                    const std::string description)
                {
                    if(description.length() > m_lengther_description)
                        m_lengther_description = description.length();

                    m_steps.push_back(std::make_pair(expr, description));
                }


                const auto& steps() const
                {
                    return m_steps;
                }


                /// Override to build
                /// the test steps.
                virtual void test() = 0;
        };

        template <typename ... test_t>
        class test_suite;

        template <typename test_t>
        struct test_suite<test_t>
        {
            inline std::string complete_line(
                const std::string& str,
                size_t line_size,
                char completor)
            {
                return str + (str.size() < line_size ?
                              std::string(line_size - str.size() - 2 ,
                                          completor)
                              : "");
            }

            inline void operator()()
            {
                timer<test_t> t;

                auto && test = test_t();
                test.test();
                bool res {true};
                unsigned nb_steps_passed {0};

                static const std::string tab_border {"== "};

                logger<test_t>::info("==============================");
                t.start("==      START == ");
                logger<test_t>::info(tab_border);
                logger<test_t>::info(tab_border);

                static const std::string step_ok =
                    " | Ok !";
                static const std::string step_ko =
                    " | Ko /!\\";


                for(const auto & step : test.steps())
                    if((res &= step.first, step.first))
                    {
                        /// The step is Ok
                        nb_steps_passed++;

                        logger<test_t>::info(tab_border,
                                             '|',
                                             std::string(test.lengthest() + 3, '-'),
                                             '|',
                                             std::string(step_ko.size() + 1,
                                                         '-'),
                                             '|');

                        logger<test_t>::info(tab_border,
                                             "| ",
                                             complete_line(step.second,
                                                           test.lengthest() + 3,
                                                           ' '),
                                             step_ok, "     |");
                    }

                    else
                    {
                        logger<test_t>::info(tab_border,
                                             "| ",
                                             std::string(test.lengthest() + 3, '-'),
                                             '|',
                                             std::string(step_ko.size() + 1,
                                                         '-'),
                                             '|');

                        logger<test_t>::info(tab_border,
                                             '|',
                                             complete_line(step.second,
                                                           test.lengthest() + 3,
                                                           ' '),
                                             step_ko, "     |");
                    }

                logger<test_t>::info(tab_border,
                                     '|',
                                     std::string(test.lengthest() + 3, '-'),
                                     '|',
                                     std::string(step_ko.size() + 1,
                                                 '-'),
                                     '|');

                logger<test_t>::info(tab_border,
                                     "     Result : passed ",
                                     nb_steps_passed,
                                     "/",
                                     test.steps().size());

                t.stop("==        END == ");
                logger<test_t>::info("==============================");
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
                    test_suite<test_t>()();

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

            template<typename ... args_t>
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

                template <typename ... args_t>
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

                template <typename ... args_t>
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

                template <typename ... args_t>
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

    /*namespace net
    {
        template < unsigned _port,
                 int _domain,
                 bool _is_server,
                 int _protocol >
        class socket
        {
                SOCKET server_sock = 0;
                SOCKET client_sock = 0;
                unsigned port = _port;
                bool is_server = _is_server;
                int domain = _domain;
                int protocol = _protocol;
    #if defined (WIN32)
                static WSADATA wsadata;
    #endif

            public:
                socket() = default;
                socket(const socket& other) = default;
                socket(socket && other) = default;
                virtual ~socket() = default;

            public:
                socket& operator=(const socket& other) = default;
                socket& operator=(socket && other) = default;

            public:

                void srvBind(unsigned short port,
                             unsigned long type = INADDR_ANY) throw(BindException)
                {
                    if(is_server)
                    {
                        SOCKADDR_IN sin;

                        sin.sin_addr.s_addr = htonl(type);
                        sin.sin_family = domain;
                        sin.sin_port = htons(port);
                        auto bind_res = bind(this->sock, (SOCKADDR*)&sin, sizeof(sin));

                        /// if(bind_res)
                        ///    throw BindException();
                    }
                }

                void srvListening(int backlog = 1) throw(ListenException)
                {
                    if(this->is_server)
                    {
                        auto listen_res = listen(this->sock, backlog);

                        /// if(listen_res != 0)
                        ///    throw ListenException();
                    }
                }

                void srvAccept() throw(AcceptException)
                {
                    if(this->is_server)
                    {
                        SOCKADDR_IN csin;
                        socklen_t taille = sizeof(csin);
                        this->csock = accept(this->sock, (SOCKADDR*)&csin, &taille);
                    }
                }

                void cltConnect(std::string& addr, unsigned short port) throw(ConnectException)
                {
                    if(!this->is_server)
                    {
                        SOCKADDR_IN sin;

                        sin.sin_addr.s_addr = inet_addr(addr.c_str());
                        sin.sin_family = this->domain;
                        sin.sin_port = htons(port);

                        if(connect(this->sock, (SOCKADDR*)&sin, sizeof(sin)) != 0)
                        {
                            throw ConnectException();
                        }
                    }
                }

                void bthSend(const char* buffer, unsigned bufferSize)
                {
                    if(this->is_server)
                    {
                        send(this->csock, buffer, bufferSize, 0);
                    }

                    else
                    {
                        send(this->sock, buffer, bufferSize, 0);
                    }
                }

                void bthRecv(char* buffer, unsigned bufferSize)
                {
                    if(this->is_server)
                    {
                        recv(this->csock, buffer, bufferSize, 0);
                    }

                    else
                    {
                        recv(this->sock, buffer, bufferSize, 0);
                    }
                }

                void bthShutdown(int how)
                {
                    shutdown(this->sock, how);
                }

                int bthClose()
                {
                    return closesocket(sock);
                }

                static int initSystem()
                {
    #if defined (WIN32)
                    WSADATA WSAData;
                    return WSAStartup(MAKEWORD(2, 2), &WSAData);
    #else
                    return 0;
    #endif
                }

                static int cleanSystem();
                {
    #if defined (WIN32)
                    return WSACleanup();
    #else
                    return 0;
    #endif
                }

                SOCKET getSocket()
                {
                    return this->sock;
                }

        };
    }
    //*/
}

#endif /* CORE_CORE_HPP_ */
