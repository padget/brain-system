#ifndef COMPILER_EVENT_HPP_INCLUDED
#define COMPILER_EVENT_HPP_INCLUDED

#include "supports.hpp"

namespace brain
{
    namespace cpl
    {
        enum class event_type
        {
            SCANNING_WANTED,
            SCANNING_BEGIN,
            SCANNING_END,
            SCANNING_RETURNED,

            PARSING_WANTED,
            PARSING_BEGIN,
            PARSING_END,
            PARSING_RETURNED,

            EXECUTING_WANTED,
            EXECUTING_BEGIN,
            EXECUTING_END,
            EXECUTING_RETURNED,
            ERROR,
            WARNING
        };

        template<typename enum_t>
        class event :
            public sys::event
        {
                property<std::string> filename;
                property<std::vector<token<enum_t>>> tokens;
                property<std::tuple<bool, node<enum_t>>> node;
                //nat::property<semobject_sptr> object;
                property<event_type> type;
                property<std::string> message;

            public:
                inline event(sys::system& source, event_type t) :
                    sys::event(source),
                    type(t)
                {}

                inline event(sys::system& source,
                             event_type t,
                             const std::string& m) :
                    sys::event(source),
                    type(t),
                    message(m)
                {}

                event(const event<enum_t>&) noexcept = default;
                event(event<enum_t> &&) noexcept = default;
                virtual ~event() noexcept = default;

            public:
                event<enum_t>& operator=(const event<enum_t>&) noexcept = default;
                event<enum_t>& operator=(event<enum_t> &&) noexcept = default;
        };
    }
}


#endif // COMPILER_EVENT_HPP_INCLUDED
