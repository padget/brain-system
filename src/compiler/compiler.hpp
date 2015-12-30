#ifndef COMPILER_COMPILER_HPP_
#define COMPILER_COMPILER_HPP_

#include "../core.h"
#include <list>
#include "supports.hpp"
#include "event.hpp"

namespace brain
{
    namespace cpl
    {
//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//
//--//--//--// Déclaration des systèmes de compilation      //
//--//--//--//--//--//--//--//--//--//--//--//--//--//--//--//

        template < typename grammar_t,
                 typename binds_t >
        class executer :
            public sys::system
        {
                using config_type =
                    config_<grammar_t>;

            public:
                executer() noexcept
                {
                    /*bind_functor compiler_event_cb([](system & s, brain::event & e)
                    {
                        auto& ce = dynamic_cast<cpl::event<enum_t>&>(e);

                        if(fct::equals(ce.type(), cpl::event_type::EXECUTING_WANTED))
                            if(std::get<0>(ce.node()))
                            {
                                ce.type(cpl::event_type::EXECUTING_RETURNED);
                                ce.message("Executer returned");
                                ce.object(binds_t::cover_node(std::get<1>(ce.node())));
                            }
                    });

                    bind(typeid(cpl::event<enum_t>), compiler_event_cb);*/
                }

                executer(
                    const executer&) = default;
                executer(
                    executer &&) = default;
                virtual ~executer() noexcept = default;

            public:
                virtual executer& operator=(
                    const executer&) noexcept = default;
                virtual executer& operator=(
                    executer &&) noexcept = default;
        };
    }
}
#endif /* COMPILER_COMPILER_HPP_ */
