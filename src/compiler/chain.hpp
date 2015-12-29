#ifndef CHAIN_HPP_INCLUDED
#define CHAIN_HPP_INCLUDED

#include "compiler.hpp"
#include "parser.hpp"
#include "scanner.hpp"
#include "supports.hpp"
#include "event.hpp"

namespace brain
{
    namespace cpl
    {
        template < typename enum_t,
                 typename sconverter_t >
        class chain :
            public sys::system
        {
                typename sconverter_t::res_type m_result;

                using chain_def = chain<enum_t, sconverter_t>;

            public:
                chain() :
                    system()
                {
                    autoconnected(true);

                    /*bind_functor compiler_event_cb([](system & s, brain::event & e)
                    {
                        auto& ce = dynamic_cast<cpl::event<enum_t>&>(e);
                        auto& ch = dynamic_cast<chain_def&>(s);

                        if(fct::equals(ce.type(),
                                       event_type::SCANNING_WANTED))
                            s.subsend(e);

                        if(fct::equals(ce.type(),
                                       event_type::SCANNING_RETURNED))
                        {
                            ce.type(event_type::PARSING_WANTED);
                            s.subsend(e);
                        }

                        if(fct::equals(ce.type(),
                                       event_type::PARSING_RETURNED))
                        {
                            ce.type(event_type::EXECUTING_WANTED);
                            s.subsend(e);
                        }

                        using arg_type = typename sconverter_t::arg_type;

                        if(fct::equals(ce.type(),
                                       event_type::EXECUTING_RETURNED)
                                and fct::not_null(ce.object()))
                            ch.result(sconverter_t()(shared_conv<arg_type>(ce.object())));

                        if(fct::equals(ce.type(),
                                       event_type::ERROR))
                            logger<chain_def>::error(ce.message());

                        if(fct::equals(ce.type(),
                                       event_type::WARNING))
                            logger<chain_def>::warn(ce.message());

                    });

                    bind(typeid(cpl::event<enum_t>), compiler_event_cb);*/
                }

                chain(const chain_def&) = default;
                chain(chain_def &&) = default;
                virtual ~chain() noexcept = default;

            public:
                virtual chain_def& operator=(const chain_def&) noexcept = default;
                virtual chain_def& operator=(chain_def &&) noexcept = default;

            public:
                virtual std::unique_ptr<system> clone() override
                { return std::make_unique<chain_def>(*this); }

            public:
                void compile()
                {
                    cpl::event<enum_t> e(this, event_type::SCANNING_WANTED);
                    /// e.filename(args()[0]);
                    send(e);
                }

            public:
                const auto& result() const
                { return m_result; }

                void result(typename sconverter_t::res_type && res)
                { m_result = res; }
        };
    }
}

#endif  // CHAIN_HPP_INCLUDED
