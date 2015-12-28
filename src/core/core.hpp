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
#include "serialize.hpp"
#include "meta.hpp"
#include "pattern.hpp"
#include "property.hpp"
#include "logging.hpp"
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


    /// ////// ///
    /// Object ///
    /// ////// ///


    /// Fundamental class
    /// for all class in
    /// brain-system framework
    class object:
        public serialize::serializable<char>,
        public pattag::composite
    {
            /// Static incremental ID
            static unsigned long long s_id;


        public:
            /// id of the current
            /// object. It's generated
            /// with static ID.
            property<unsigned long long> id {++s_id};


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
                    id(++s_id);

                return *this;
            }


            /// Move assignement
            object& operator=(
                object &&) = default;


        public:
            /// Serialize method
            /// to overload to
            /// have a specific
            /// feature for childs
            /// classes
            inline virtual void serialize(
                serialize::stream<char>& out) const
            {
                out << "object"
                    << serialize::fundamental<char>("id", id());
            }


        public:
            /// Overload this method
            /// to specify to the target
            /// type
            virtual bool equals(
                const object& other) const
            {
                return id() == other.id();
            }


            /// Returns the result
            /// of this->equals(other)
            bool operator ==(
                const object& other) const
            {
                return equals(other);
            }
    };


    /// The value of static ID
    /// is initialised to 0
    unsigned long long object::s_id {default_v<unsigned long long>};


   


    namespace sys
    {
        class system;


        /// An event is sended
        /// by several system
        /// type for other
        /// system. This is the
        /// way of communication
        /// between systems
        class event
        {
            public:
                /// The source of
                /// the event
                property<system*> from;


            public:
                /// Constructor with
                /// the source (mandatort)
                event(system* _from):
                    from {_from}
                {
                }


                /// Default constructor
                /// by copy
                event(
                    const event& other) = default;


                /// Default constructor
                /// by move
                event(
                    event && other) = default;


                /// Default virtual
                /// destructor
                virtual ~event() = default;


            public:
                /// Default operator=
                /// by copy
                event& operator=(
                    const event& other) = default;


                /// Default operator=
                /// by move
                event& operator=(
                    event && other) = default;
        };


        /// An handler can
        /// intercept event
        /// and react to them
        class handler
        {
                /// Private receipt
                /// function to
                /// overload in order
                /// to receipt correctly
                /// an event (cast, integrity...)
                virtual void receipt(
                    system&,
                    event&) const = 0 ;


            public:
                /// Operator that launch
                /// the reception of the
                /// event
                inline void operator()(
                    system& s,
                    event& e) const
                {
                    receipt(s, e);
                }
        };


        /// A basic_handler is
        /// an object that cast
        /// the event and the
        /// system into the right
        /// types of each.
        template < typename event_t,
                 typename system_t >
        class basic_handler:
            public handler
        {
            public:
                /// Overload this function
                /// to use the event and
                /// system for the right
                /// feature
                virtual void react(
                    system_t&,
                    event_t&) const = 0;


                /// Receipt system and
                /// event and cast them
                /// to system_t and event_t.
                /// Finally launch the
                /// overloaded react function
                virtual void receipt(
                    system& s,
                    event& e) const final
                {
                    /// If effective types
                    /// is the right types
                    /// then they can be
                    /// casted and used by
                    /// overloaded react function
                    if(typeid(e) == typeid(event_t) and
                            typeid(s) == typeid(system_t))
                    {
                        /// Cast event => event_t
                        event_t& trs_e =
                            dynamic_cast<event_t&>(e);

                        /// Cast system => system_t
                        system_t& trs_s =
                            dynamic_cast<system_t&>(s);

                        /// Launch overloaded react
                        react(trs_s, trs_e);
                    }
                }
        };


        /// A system is an
        /// object that can
        /// send and receive
        /// several types of
        /// events
        class system:
            public object
        {
            public:
                /// List of all handlers
                /// that is enabled for
                /// this system
                property<std::vector<std::unique_ptr<handler>>> handlers;


                /// True if a system is
                /// autoconnected, false
                /// else
                property<bool> autoconnected {default_v<bool>};


                /// List of all
                /// systems that
                /// can receive
                /// an event from
                /// the current
                property<std::list<system*>> to_systems;


                /// List of all
                /// system that
                /// send an event
                /// to the current
                property<std::list<system*>> from_systems;


            public:
                /// Destructor of system.
                /// Unconnects this of all
                /// systems from from_systems
                virtual ~system()
                {
                    for(auto * sys : from_systems())
                    {
                        if(sys != nullptr)
                            sys->remove_receiver(this);
                    }
                }


            public:
                /// Connect a system
                /// to the current one
                inline void add_receiver(
                    system* receiver)
                {
                    /// If the receiver exists
                    /// the receiver is added
                    /// to the to_systems list
                    /// and this is added to the
                    /// from_systems list of receiver
                    if(receiver != nullptr)
                    {
                        to_systems().push_back(receiver);
                        receiver->from_systems().push_back(this);
                    }
                }


                /// Unconnect a system
                /// to the current one
                inline void remove_receiver(
                    system* receiver)
                {
                    /// If the receiver exists
                    /// the receiver is removed
                    /// from the to_systems list
                    /// and this is removed from the
                    /// from_systems list of receiver
                    if(receiver != nullptr)
                    {
                        receiver->from_systems().remove(this);
                        to_systems().remove(receiver);
                    }
                }


            public:
                /// receive an event
                inline void receive(
                    event& e)
                {
                    /// For each handler,
                    /// it handles the
                    /// event e
                    for(const auto & rec : handlers())
                        (*rec)(*this, e);
                }


                /// Send an event
                inline void send(
                    event& e)
                {
                    /// If autoconnected
                    /// then it receives
                    /// the event itself
                    if(autoconnected())
                        receive(e);

                    /// For each connected
                    /// system, it receives
                    /// the event
                    for(auto * sys : to_systems())
                        if(sys != nullptr)
                            sys->receive(e);
                }


            public:
                /// Serialize method
                inline virtual void serialize(
                    serialize::stream<char>& out) const
                {
                    out << "system"
                        << serialize::parent<char, object>(*this);
                }
        };
    }
    
    
     /*   namespace react
       {
           class reactive;

           class operation
           {
               public:
                   virtual void operator()(
                       reactive*,
                       const std::vector<reactive*>&) = 0;
           };


           class formule
           {
               public:
                   property<reactive*> result;
                   property<operation*, managing::unique> op;
                   property<std::vector<reactive*>> args;

               public:
                   formule(
                       reactive* _result,
                       operation* _op,
                       std::vector<reactive*> && _args):
                       result {_result},
                          op {_op},
                   args {_args}
                   {
                   }


               public:
                   void compute()
                   {
                       (*op())(result(), args());
                   }

           };


           class reactive
           {
               public:
                   property<int> value;
                   property<formule*> form;
           };
       }
    */


    enum class exitcode :
    int
    {
        WELL = 0,
        CRITIC = 1
    };


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
