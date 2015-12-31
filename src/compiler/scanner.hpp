#ifndef SCANNER_HPP_INCLUDED
#define SCANNER_HPP_INCLUDED

#include "supports.hpp"
#include "event.hpp"

namespace brain
{
    namespace cpl
    {
        template<typename system_t>
        struct scanning_receiptor :
            public sys::basic_handler <cpl::event<config_<system_t>>, system_t>
        {
            public:
                virtual void act(
                    system_t& s,
                    cpl::event<config_<system_t>>& e) const
                {
                    e.type(event_type::SCANNING_RETURNED);
                    e.message("Parsing wanted");
                    e.tokens(s.build_tokens(e.filename()));
                }
        };

        template < typename config_t >
        class scanner:
            public sys::system
        {
                using config_type =
                    config_t;

            public:

                template<typename token_maker_t>
                static void build_tokens(
                    const std::string& filename,
                    std::vector<token<config_t>>& tokens)
                {
                    token_maker_t maker;
                    maker(filename, tokens);
                }
        };
    }
}
#endif // SCANNER_HPP_INCLUDED
