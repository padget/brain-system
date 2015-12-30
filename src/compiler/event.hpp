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

        template <typename config_t>
        class event :
            public sys::event
        {
                property<std::string> filename;
                property<std::vector<token<config_t>>> tokens;
                property<std::tuple<bool, node<config_t>>> node;
                property<event_type> type;
                property<std::string> message;

            public:
                inline event(
                    sys::system& source,
                    event_type t) :
                    sys::event(source),
                    type(t)
                {
                }

                inline event(
                    sys::system& source,
                    event_type t,
                    const std::string& m) :
                    sys::event(source),
                    type(t),
                    message(m)
                {
                }

                event(const event&) noexcept = default;
                event(event &&) noexcept = default;
                virtual ~event() noexcept = default;

            public:
                event& operator=(
                    const event&) noexcept = default;
                event& operator=(
                    event &&) noexcept = default;
        };
    }
}


#endif // COMPILER_EVENT_HPP_INCLUDED
