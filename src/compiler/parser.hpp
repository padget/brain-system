#ifndef PARSER_HPP_INCLUDED
#define PARSER_HPP_INCLUDED

#include "event.hpp"
#ifndef COMPILER_DEBUG
//#define COMPILER_DEBUG
#endif

namespace brain
{
    namespace cpl
    {
        template <typename grammar_t>
        class parser:
            public sys::system
        {
                using parser_def =
                    parser<grammar_t>;

                using config_type =
                    config_<grammar_t>;

            public:
                parser()
                {
                    /*bind_functor compiler_event_cb([](system & s, brain::event & e)
                    {
                        auto& ce = dynamic_cast<cpl::event<enum_t>&>(e);

                        if(fct::equals(ce.type(),
                                       cpl::event_type::PARSING_WANTED))
                        {
                            ce.type(event_type::PARSING_RETURNED);
                            ce.message("Parser returned");
                            ce.node(dynamic_cast<parser_def&>(s).analyse_tokens(ce.tokens()));
                        }
                    });

                    bind(typeid(cpl::event<enum_t>), compiler_event_cb);*/
                }

                parser(
                    const parser_def&) = default;
                parser(
                    parser_def &&) = default;
                virtual ~parser() noexcept = default;

            public:
                virtual parser_def& operator=(
                    const parser_def&) noexcept = default;
                virtual parser_def& operator=(
                    parser_def &&) noexcept = default;

            public:

                template<typename node_maker_t>
                static void build_node(
                    typename node_maker_t::tokens_type& tokens,
                    typename node_maker_t::node_type& node)
                {
                    node_maker_t()(tokens, node);
                }
        };
    }
}
#endif // PARSER_HPP_INCLUDED
