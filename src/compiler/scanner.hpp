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
            public sys::basic_receiptor < cpl::event<typename system_t::enum_type>, system_t>
        {
            public:
                virtual void act(system_t& s,
                                 cpl::event<typename system_t::enum_type>& e) const
                {
                    e.type(event_type::SCANNING_RETURNED);
                    e.message("Parsing wanted");
                    e.tokens(s.build_tokens(e.filename()));
                }
        };

        template < typename enum_t>
        class scanner:
            public sys::system
        {
                using scanner_def = scanner<enum_t>;
                using enum_type = enum_t;

            public:
                scanner() :
                    sys::system()
                {
                    
                };

                scanner(const scanner_def&) = default;
                scanner(scanner_def &&) = default;
                virtual ~scanner() noexcept = default;

            public:
                virtual scanner_def& operator=(const scanner_def&) noexcept = default;
                virtual scanner_def& operator=(scanner_def &&) noexcept = default;

            public:

                template<typename token_maker_t>
                static void build_tokens(const std::string& filename,
                                         typename token_maker_t::tokens_type& tokens)
                {
                    token_maker_t maker;
                    maker(filename, tokens);
                }
        };
    }
}
#endif // SCANNER_HPP_INCLUDED
