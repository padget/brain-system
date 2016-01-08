#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <fstream>
#include <iostream>
#include <typeinfo>

#include "core.hpp"

#include <iostream>
#include <chrono>

namespace brain
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
            static std::unique_ptr<formatter<lvl, t>> format;

            inline static void skip_policy(Skip skip) noexcept
            { fct::assign(loggerconf::skip, skip); }

            template < typename formatter_t = formatter<lvl, t>>
            inline static void format_policy(formatter_t && f)
            { format.reset(new formatter_t(f)); }
    };

    template <Level lvl, typename t>
    std::unique_ptr<formatter<lvl, t>> loggerconf<lvl, t>::format(new formatter<lvl, t>());

    template <Level lvl, typename t>
    Skip loggerconf<lvl, t>::skip = Skip::UNDEFINED;

    template <Level lvl, typename t>
    std::map<std::ostream*, std::ostream*> loggerconf<lvl, t>::outs =
        concatmap( {&std::cout, &(std::cout << std::boolalpha)}, loggerconf<Level::ALL>::outs, loggerconf<lvl>::outs);

    template<typename enum_t, typename = std::enable_if_t<std::is_enum<enum_t>::value>>
    std::ostream & operator<<(std::ostream& out, enum_t e) noexcept
    { return out << (long) e; }

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

                for(unsigned i = 0; i < nb_try; ++i)
                    func(args...);

                t.stop("End of benchmark of ", func_name);
            }
    };

    template < Level lvl,
             typename type_t >
    class formatter
    {
        public:
            virtual std::string operator()(const std::vector<std::string>& messages) const
            {
                auto && now = timer<std::chrono::system_clock >::now();
                now.erase(now.length() - 1, 1);

                std::stringstream ss;

                append(ss, now, " : [", lvlname<lvl>(), "] (", typeid(type_t).name(), ") : ");
                fct::for_each(messages, [&ss](auto && str) {append(ss, str);});

                ss << std::endl;

                return std::forward<std::string>(ss.str());
            }
    };

    namespace logging
    {
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
                    { append(*out.second, (*loggerconf<lvl, type_t>::format)( {std::string(message)...})); });
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
    }

    template < typename type_t,
             typename clock = std::chrono::system_clock >
    class logger :
        public singleton<logger<type_t, clock>>
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
            {  logging::fatal<type_t, clock>()(message...); }
    };
}

#endif /* LOG_H_ */
