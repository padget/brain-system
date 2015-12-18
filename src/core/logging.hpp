#ifndef __HPP_LOGGING_BRAIN_
#define  __HPP_LOGGING_BRAIN_

#include "pattern.hpp"

namespace brain
{
    /// //////////////// ///
    /// Logging Features ///
    /// //////////////// ///
    namespace logging
    {
        /// ROOT is used to specify
        /// a default value for logger
        struct ROOT
        {
        };


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
        const std::string lvlstr =
            "UNDEFINED";


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
        struct loggerconf
        {

            static std::map<std::ostream*, std::ostream*> outs;
            static property<Skip> skip;
            static property<formatter<lvl, t>*, managing::unique> format;


            inline static void skip_policy(
                Skip skip) noexcept
            {
                loggerconf::skip = skip;
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
        property<formatter<lvl, t>*, managing::unique> loggerconf<lvl, t>::format;


        template < Level lvl,
                 typename t >
        property<Skip> loggerconf<lvl, t>::skip {Skip::UNDEFINED};


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
                using time_point =
                    typename clock::time_point;

                using ms =
                    std::chrono::milliseconds;


            public:
                property<time_point> t0 {clock::now()};


            public:
                ///
                static std::string now() noexcept
                {
                    auto time = clock::to_time_t(clock::now());
                    return std::string(ctime(&time));
                }


                ///
                template <typename ... t>
                void start(
                    t && ... message) noexcept
                {
                    brain::set(t0, clock::now());
                    logger<T, clock>::info(message...);
                }


                ///
                template <typename ... t>
                void step(
                    t && ... message) noexcept
                {
                    auto && duration =
                    std::chrono::duration_cast<ms>(clock::now() - t0()).count();

                    logger<T, clock>::info(message...,
                    " : ",
                    duration,
                    " ms");
                    t0(clock::now());
                }


                ///
                template <typename ... t>
                void stop(
                    t && ... message) noexcept
                {
                    auto && duration =
                    std::chrono::duration_cast<ms>(clock::now() - t0()).count();

                    logger<T, clock>::info(message...,
                    " : ",
                    duration,
                    " ms");
                    t0(clock::now());
                }


                ///
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


                ///
                template<typename func_t, typename ... args_t>
                static void bench(
                    const std::string& func_name,
                    unsigned nb_try,
                    func_t& func,
                    args_t ... args)
                {
                    timer<T> t;
                    t.start("Start of benchmark of ", func_name);

                    for(unsigned u = 0;  u < nb_try; u++)
                        func(args...);

                    t.stop("End of benchmark of ", func_name);
                }
        };



        struct stream_appender
        {
            template <typename t>
            inline static std::ostream& append(
                std::ostream& out,
                t && o) noexcept
            {
                return out << o;
            }


            template < typename t,
                     typename ... T >
            inline static std::ostream& append(
                std::ostream& out,
                t && o,
                T && ... os) noexcept
            {
                out << o;
                return append(out, os...);
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
                    auto && now =
                        timer<std::chrono::system_clock>::now();
                    now.erase(now.length() - 1, 1);
                    out << std::boolalpha;
                    stream_appender::append(out,
                                            now,
                                            " : [",
                                            lvlstr<lvl>,
                                            "] (",
                                            typeid(type_t).name(),
                                            ") : ",
                                            messages...);
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
                if((loggerconf<lvl>::skip() == Skip::SKIP and
                        loggerconf<lvl, type_t>::skip() == Skip::DONT_SKIP)
                        or (loggerconf<lvl>::skip() != Skip::SKIP and
                            loggerconf<lvl, type_t>::skip() != Skip::SKIP))
                    for(auto & out : loggerconf<lvl, type_t>::outs)
                        (*loggerconf<lvl, type_t>::format())(*out.second, message...);
            }
        };


        template < typename type_t,
                 typename clock = std::chrono::system_clock >
        using debug =
            log<Level::DEBUG, type_t, clock>;


        template < typename type_t,
                 typename clock = std::chrono::system_clock >
        using trace =
            log<Level::TRACE, type_t, clock>;


        template < typename type_t,
                 typename clock = std::chrono::system_clock >
        using warn =
            log<Level::WARN, type_t, clock>;


        template < typename type_t,
                 typename clock = std::chrono::system_clock >
        using info =
            log<Level::INFO, type_t, clock>;


        template < typename type_t,
                 typename clock = std::chrono::system_clock >
        using error =
            log<Level::ERROR, type_t, clock>;


        template < typename type_t,
                 typename clock = std::chrono::system_clock >
        using fatal =
            log<Level::FATAL, type_t, clock>;


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

}


#endif
