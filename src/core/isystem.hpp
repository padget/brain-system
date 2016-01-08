#ifndef ISYSTEM_H_
#define ISYSTEM_H_

#include <vector>
#include <string>
#include "log.hpp"
#include <map>
#include <memory>
#include <thread>
#include "functionnal.hpp"

namespace brain
{
    class system;

    class event;
    using event_sptr = std::shared_ptr<event>;

    class event
    {
        protected:
            system* m_source;

        public:
            inline event(system* source) :
                m_source(source)
            {}

            event(const event&) noexcept = default;
            event(event &&) noexcept = default;
            virtual ~event() noexcept = default;

        public:
            event& operator=(const event&) noexcept = default;
            event& operator=(event &&) noexcept = default;

        public:
            inline const system& source() const noexcept
            { return fct::inner(m_source); }
    };

    WITH_T(instanceName)
    WITH_T(className)
    WITH_T_DEFAULTED(autoconnected)
    WITH_T(systems)
    WITH_T(subsystems)

    using bind_functor = std::function<void(system&, event&)>;

    class system:
        public core::object,
        public cloneable<system>,
        public with_instanceName<std::string>,
        public with_className<std::string>,
        public with_subsystems<std::vector<system*> >,
        public with_autoconnected<bool, false>,
        public with_systems<std::vector<system*> >

    {
            std::vector<std::string> m_args;
            std::map<std::string, bind_functor> m_binds;

        public:
            system() = default;
            system(const system&) = default;
            system(system &&) = default;
            virtual ~system() = default;

        public:
            virtual system& operator=(const system&) = default;
            virtual system& operator=(system &&) = default;

        public:
            inline virtual void init(const std::vector<std::string>& args = {})
            { fct::assign(m_args, args); }

            inline void addReceiver(system* receiver)
            {
                if(fct::not_null(receiver))
                    systems().push_back(receiver);
            }

            inline void addSubsystem(system& subsys)
            {
                subsystems().push_back(&subsys);
            }

            inline const std::vector<std::string>& args() const
            { return m_args; }

        public:
            template < typename event_t,
                     typename = brain::enable_if_is_baseof_t<event, event_t >>
            void receive(event_t && e)
            {
                for(auto & bind : m_binds)
                    if(fct::equals(bind.first,
                                   std::string(typeid(e).name())))
                        bind.second(*this, e);
            }


            template < typename event_t,
                     typename = brain::enable_if_is_baseof_t<event, event_t >>
            void send(event_t && e)
            {
                if(autoconnected())
                    this->receive(e);

                for(auto * system : systems())
                    if(fct::not_null(system))
                        system->receive(e);
            }

            template < typename event_t,
                     typename = brain::enable_if_is_baseof_t<event, event_t >>
            void subsend(event_t && e)
            {
                for(auto * subsys : subsystems())
                    if(fct::not_null(subsys))
                        subsys->receive(e);
            }

        public:
            inline void binds(const std::map<std::string, bind_functor>& binds)
            { fct::assign(m_binds, binds); }

        protected:
            inline void bind(const std::type_info& type, bind_functor f)
            { fct::assign(m_binds[std::string(type.name())], f); }

        public:
            void bilink(std::vector<system*> && systems)
            {
                for(const auto & system : systems)
                {
                    this->addReceiver(system);
                    system->addReceiver(this);
                }
            }

            void subbilink(std::vector<system*> && systems)
            {
                for(const auto & system : systems)
                {
                    this->subsystems().push_back(system);
                    system->addReceiver(this);
                }
            }
    };
}
#endif /* ISYSTEM_H_ */
