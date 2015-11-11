#ifndef __SERVER_PTR_HPP__
#define __SERVER_PTR_HPP__

namespace brain
{
    namespace ptr
    {

        template<typename type_t>
        class client_ptr;


        /// Class defined for
        /// dynamic cast features.
        struct server_pointer_base
        {
            BRAIN_ALL_DEFAULT(server_pointer_base)
        };


        /// A server_ptr allows
        /// to define a smart
        /// pointer that's the
        /// owner of a resource.
        /// This resource can be
        /// distributed into
        /// several client_ptr.
        template<typename type_t>
        class server_ptr:
            public server_pointer_base
        {
            public:
                using type = type_t;
                using pointer = type*;
                using ureference = type &&;
                using reference = type&;
                using client = client_ptr<type>;


            public:
                pointer m_owned {nullptr};
                std::list<client*> m_clients;

            public:
                /// Build an empty
                /// server_ptr
                server_ptr() = default;


                /// Build an server_ptr
                /// with owned
                server_ptr(pointer owned):
                    server_pointer_base(),
                    m_owned(owned) {}


                /// Polymorphic builder.
                template < typename other_t,
                         typename = std::_Require < std::is_polymorphic<other_t>,
                         std::is_base_of<type, other_t> >>
                server_ptr(other_t* owned):
                    server_pointer_base(),
                    m_owned(owned) {}


                /// Copy a server_ptr
                /// is forbidden.
                server_ptr(const server_ptr&) = delete;


                /// Move constructor
                server_ptr(server_ptr && other) :
                    server_pointer_base(),
                    m_owned(other.release()),
                    m_clients(std::move(other.clients()))
                {
                    for(auto * client : m_clients)
                        client->switch_server(this);

                    other.m_clients.clear();
                }


                /// Destructor. Delete owned
                /// pointer and unsubscribe
                /// all clients
                virtual ~server_ptr()
                {
                    if(m_owned != nullptr)
                        delete m_owned;

                    for(auto * client : m_clients)
                        client->switch_server();
                }

            public:
                /// Copy operator= deleted
                server_ptr& operator= (const server_ptr &) = delete;


                /// Move operator=
                server_ptr& operator= (server_ptr && other)
                {
                    reset(other.release());

                    m_clients =
                        std::move(other.m_clients);

                    for(auto * client : m_clients)
                        (*client).switch_server(this);

                    other.m_clients.clear();

                    return *this;
                }

            public:
                /// Replaces the pointer
                /// m_owned by p and deletes
                /// old m_owned
                void reset(pointer p = nullptr)
                {
                    std::swap(m_owned, p);

                    if(p != nullptr)
                        delete p;
                }


                ///
                pointer release()
                {
                    pointer p {get()};
                    m_owned = nullptr;
                    return p;
                }


                ///
                pointer get()
                { return m_owned; }


                ///
                const pointer get() const
                { return m_owned; }


                ///
                auto& clients()
                { return m_clients; }


                ///
                const auto& clients() const
                { return m_clients; }

            public:
                ///
                void subscribe(client_ptr<type>* subscriber)
                { m_clients.push_front(subscriber); }


                ///
                void unsubscribe(client_ptr<type>* subscriber)
                {
                    m_clients.remove_if([subscriber](auto * client)
                    { return subscriber == client; });
                }

            public:
                ///
                pointer operator->()
                { return m_owned; }


                ///
                const pointer operator->() const
                { return m_owned; }


                ///
                reference operator*()
                { return *m_owned; }


                ///
                const reference operator*() const
                { return *m_owned; }


                ///
                operator bool() const
                { return m_owned != nullptr; }


            public:
                ///
                auto make_client()
                { return client_ptr<type> {*this}; }
        };


        ///
        template < typename type_t,
                 typename base_t,
                 typename ... args_t >
        auto make_server(args_t && ... args)
        { return server_ptr<base_t>(new type_t(std::forward<args_t>(args)...)); }


        ///
        template<typename type_t>
        class client_ptr
        {
            public:
                using type = type_t;
                using pointer = type*;
                using reference = type&;

            public:
                server_pointer_base* m_server = nullptr;

            public:
                ///
                client_ptr() = default;


                ///
                client_ptr(server_ptr<type>& server = nullptr) :
                    m_server {&server}
                { subscribe(); }


                ///
                client_ptr(const client_ptr& other):
                    m_server {other.m_server}
                { subscribe(); }


                ///
                client_ptr(client_ptr && other):
                    m_server {other.m_server}
                {
                    if(other.m_server != nullptr)
                        other.unsubscribe();

                    subscribe();
                }


                ///
                virtual ~client_ptr()
                { unsubscribe(); }


            public:
                ///
                client_ptr& operator=(const client_ptr& other)
                {
                    if(this != &other)
                    {
                        unsubscribe();
                        m_server = other.m_server;
                        subscribe();
                    }

                    return *this;
                }


                ///
                client_ptr& operator=(client_ptr && other) = delete;


                ///
                template<typename other_t>
                client_ptr<type>& operator=(const client_ptr<other_t>& other)
                {
                    if(this != &other)
                    {
                        unsubscribe();
                        m_server = other.m_server;
                        subscribe();
                    }

                    return *this;
                }


            public:
                ///
                inline void unsubscribe()
                {
                    if(m_server != nullptr)
                    {
                        cast_server()->unsubscribe(this);
                        m_server = nullptr;
                    }
                }


                ///
                void subscribe()
                {
                    if(m_server != nullptr)
                        cast_server()->subscribe(this);
                }

            public:
                ///
                pointer operator->()
                { return cast_server()->get(); }


                ///
                const pointer operator->() const
                { return cast_server()->get(); }


                ///
                pointer get()
                { return cast_server()->get(); }


                ///
                const pointer get() const
                { return cast_server()->get(); }


                ///
                reference operator*()
                { return **cast_server(); }


                ///
                const reference operator*() const
                { return **cast_server(); }


                ///
                operator bool() const
                {
                    return m_server != nullptr
                           and static_cast<bool>(*(this->cast_server()));
                }


                ///
                void switch_server(server_ptr<type>* s = nullptr)
                { m_server = s; }


                ///
                const server_ptr<type>* cast_server() const
                { return dynamic_cast<const server_ptr<type>*>(m_server); }


                ///
                server_ptr<type>* cast_server()
                { return dynamic_cast<server_ptr<type>*>(m_server); }
        };
    }
}

#endif
