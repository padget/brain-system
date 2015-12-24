#ifndef __PROPERTY_HPP__BRAIN__
#define  __PROPERTY_HPP__BRAIN__

#include "pattern.hpp"
#include "meta.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <list>

namespace brain
{
    /// //////// ///
    /// Property ///
    /// //////// ///


    /// Enum that helps
    /// to determinate
    /// the managing
    /// system
    enum class managing
    {
        /// If the managing
        /// of the embedded
        /// value can't be
        /// shared
        unique,


        /// If the managing
        /// of the embedded
        /// value can be shared
        shared,


        /// If the embedded
        /// value is managed
        /// as a value
        none
    };


    /// Generic property
    template < typename type_t,   /// Embedded type
             managing _manage = managing::none > /// Flag on life cycle on embedded value
    class property;


    /// Forbid the use
    /// of type_t&
    template < typename type_t,
             managing _manage  >
    class property<type_t&, _manage>;


    /// Forbid the use
    /// of const type_t&
    template < typename type_t,
             managing _manage >
    class property<const type_t&, _manage>;


    /// Forbid the use
    /// of type_t&&
    template < typename type_t,
             managing _manage >
    class property < type_t && , _manage >;


    ///
    template<typename type_t>
    void on_change_cref(const type_t& _value) {}


    ///
    template<typename type_t>
    void on_change_ptr(const type_t* _value) {}




    /// Implementation for
    /// type_t that's not
    /// pointer.
    template<typename type_t>
    class property<type_t, managing::none> final
    {
            /// Embedded value
            type_t m_value;


            using on_change_type =
                std::function<void(const type_t&)>;


            /// On change function
            /// embedded
            on_change_type on_change {on_change_cref<type_t>};


        public:
            /// Default constructor
            property(
                const on_change_type& _on_change = on_change_cref<type_t>):
                on_change {_on_change}
            {
            }


            /// Constructor by cref
            property(
                const type_t& _value,
                const on_change_type& _on_change = on_change_cref<type_t>):
                m_value(_value),
                on_change(_on_change)
            {
            }


            /// Constructor by uref
            property(
                type_t && _value,
                const on_change_type& _on_change = on_change_cref<type_t>):
                m_value(_value),
                on_change(_on_change)
            {
            }


            /// Constructor by copy cref
            property(
                const property& other):
                m_value(other.m_value),
                on_change(other.on_change)
            {
            }


            /// Constructor by copy cref
            property(
                property && other):
                m_value(std::move(other.m_value)),
                on_change(std::move(other.on_change))
            {
            }


            /// Default destructor
            ~property() = default;


        public:
            /// Getter on ref
            type_t& operator()()
            {
                return m_value;
            }


            /// Getter on cref
            const type_t& operator()() const
            {
                return m_value;
            }


            /// Setter on cref
            void operator()(
                const type_t& _value)
            {
                m_value = _value;
                on_change(m_value);
            }


            /// Setter on uref
            void operator()(
                type_t && _value)
            {
                m_value = _value;
                on_change(m_value);
            }


        public:
            /// Getter on cref
            const type_t& get() const
            {
                return m_value;
            }


            /// Getter on ref
            type_t& get()
            {
                return m_value;
            }


            /// Setter on cref
            void set(
                const type_t& _value)
            {
                m_value = _value;
                on_change(m_value);
            }


            /// Setter on uref
            void set(
                type_t && _value)
            {
                m_value = _value;
                on_change(m_value);
            }
    };



    /// Implementation for
    /// type_t that's not
    /// pointer and const.
    template<typename type_t>
    class property<const type_t, managing::none> final
    {
            /// Embedded value
            type_t m_value;

        public:
            /// Default constructor
            property() = default;


            /// Constructor by cref
            property(
                const type_t& _value):
                m_value(_value)
            {
            }


            /// Constructor by uref
            property(
                type_t && _value):
                m_value(_value)
            {
            }


            /// Constructor by copy cref
            property(
                const property& other):
                m_value(other.m_value)
            {
            }


            /// Constructor by move uref
            property(
                property && other):
                m_value(std::move(other.m_value))
            {
            }


            /// Default destructor
            ~property() = default;


        public:
            /// Getter on cref
            const type_t& operator()() const
            {
                return m_value;
            }


        public:
            /// Getter on cref
            const type_t& get() const
            {
                return m_value;
            }
    };


    /// Implementation for
    /// type that is pointer
    /// and that considered
    /// as component
    template<typename type_t>
    class property<type_t*, managing::unique> final
    {
            /// Embedded value
            std::unique_ptr<type_t> m_value;


            using on_change_type =
                std::function<void(const type_t*)>;


            /// On change function
            /// embedded
            on_change_type on_change {on_change_ptr<type_t>};


        public:
            /// Constructor by pointer
            property(
                const on_change_type& _on_change = on_change_ptr<type_t>):
                on_change(_on_change)
            {
            }


            /// Constructor by pointer
            property(
                type_t* _value,
                const on_change_type& _on_change = on_change_ptr<type_t>):
                m_value(_value),
                on_change(_on_change)
            {
            }


            /// Constructor by
            /// smart pointer
            property(
                std::unique_ptr<type_t> && _value,
                const on_change_type& _on_change = on_change_ptr<type_t>):
                m_value(_value),
                on_change(_on_change)
            {
            }


            /// Constructor by
            /// smart pointer
            /// from another
            /// type
            template<typename other_t>
            property(
                std::unique_ptr<other_t> && _value,
                const on_change_type& _on_change = on_change_ptr<type_t>):
                m_value(_value),
                on_change(_on_change)
            {
            }


            /// Deleted constructor
            /// by copy
            property(
                const property&) = delete;


            /// Move semantic constructor
            property(
                property &&) = default;


            /// Default constructor
            ~property() = default;


        public:
            /// Getter by ref
            type_t* operator()()
            {
                return m_value.get();
            }


            /// Getter by cref
            const type_t* operator()() const
            {
                return m_value.get();
            }


            /// Setter by pointer
            /// The pointer must not
            /// managed by any other
            /// agent
            void operator()(
                type_t* _value)
            {
                if(_value != m_value.get())
                {
                    m_value.reset(_value);
                    on_change(m_value);
                }
            }


            void operator()(
                std::unique_ptr<type_t> && _value)
            {
                m_value = _value;
                on_change(m_value);
            }


            template<typename other_t>
            void operator()(
                std::unique_ptr<other_t> && _value)
            {
                m_value = _value;
                on_change(m_value);
            }


        public:
            /// Getter by cref
            const type_t* get() const
            {
                return m_value.get();
            }


            /// Getter by ref
            type_t* get()
            {
                return m_value.get();
            }


            /// Returns the embedded
            /// pointer
            const type_t* ptr() const
            {
                return m_value.get();
            }


            /// Setter by pointer
            /// The pointer must not
            /// managed by any other
            /// agent
            void set(
                type_t* _value = nullptr)
            {
                if(_value != m_value.get())
                {
                    m_value.reset(_value);
                    on_change(m_value);
                }
            }


            void set(
                std::unique_ptr<type_t> && _value)
            {
                m_value = _value;
                on_change(m_value);
            }


            template<typename other_t>
            void set(
                std::unique_ptr<other_t> && _value)
            {
                m_value = _value;
                on_change(m_value);
            }
    };


    /// Implementation for
    /// type that is pointer
    /// and that considered
    /// as reference
    template<typename type_t>
    class property<type_t*, managing::shared> final
    {
            /// Embedded pointer value
            std::shared_ptr<type_t> m_value;


            using on_change_type =
                std::function<void(const type_t*)>;


            /// On change function
            /// embedded
            on_change_type on_change {on_change_ptr<type_t>};


        public:
            /// Constructor by pointer
            property(
                const on_change_type& _on_change = on_change_ptr<type_t>):
                on_change(_on_change)
            {
            }


            /// Basic constructor
            /// based on pointer
            property(
                type_t * _value,
                const on_change_type& _on_change = on_change_ptr<type_t>):
                m_value(_value),
                on_change(_on_change)
            {
            }


            property(
                const std::shared_ptr<type_t>& _value,
                const on_change_type& _on_change = on_change_ptr<type_t>):
                m_value {_value},
                    on_change(_on_change)
            {
            }


            property(
                std::shared_ptr<type_t> && _value,
                const on_change_type& _on_change = on_change_ptr<type_t>):
                m_value {_value},
                    on_change(_on_change)
            {
            }


            template<typename other_t>
            property(
                const std::shared_ptr<other_t>& _value,
                const on_change_type& _on_change = on_change_ptr<type_t>):
                m_value {_value},
                    on_change(_on_change)
            {
            }


            template<typename other_t>
            property(
                std::shared_ptr<other_t> && _value,
                const on_change_type& _on_change = on_change_ptr<type_t>):
                m_value {_value},
                    on_change(_on_change)
            {
            }


            /// Default copy
            /// constructor
            property(
                const property&) = default;


            /// Default move
            /// constructor
            property(
                property &&) = default;


            /// Default destructor
            ~property() = default;


        public:
            /// Getter on pointer
            type_t* operator()()
            {
                return m_value;
            }


            /// Getter on cpointer
            const type_t* operator()() const
            {
                return m_value;
            }


            /// Setter on pointer
            void operator()(type_t * _value)
            {
                if(_value != m_value.get())
                {
                    m_value = _value;
                    on_change(m_value);
                }
            }


            void operator()(
                const std::shared_ptr<type_t>& _value)
            {
                m_value = _value;
                on_change(m_value);
            }


            void operator()(
                std::shared_ptr<type_t> && _value)
            {
                m_value = _value;
                on_change(m_value);
            }


            template<typename other_t>
            void operator()(
                const std::shared_ptr<other_t>& _value)
            {
                m_value = _value;
                on_change(m_value);
            }


            template<typename other_t>
            void operator()(
                std::shared_ptr<other_t> && _value)
            {
                m_value = _value;
                on_change(m_value);
            }


        public:
            /// Getter function
            /// on cpointer
            const type_t* get() const
            {
                return m_value;
            }


            /// Getter function
            /// on pointer
            type_t* get()
            {
                return m_value;
            }


            /// Setter function
            /// on pointer
            void set(
                type_t * _value)
            {
                if(_value != m_value.get())
                {
                    m_value.reset(_value);
                    on_change(m_value);
                }
            }


            void set(
                const std::shared_ptr<type_t>& _value)
            {
                m_value = _value;
                on_change(m_value);
            }


            void set(
                std::shared_ptr<type_t> && _value)
            {
                m_value = _value;
                on_change(m_value);
            }


            template<typename other_t>
            void set(
                const std::shared_ptr<other_t>& _value)
            {
                m_value = _value;
                on_change(m_value);
            }


            template<typename other_t>
            void set(
                std::shared_ptr<other_t> && _value)
            {
                m_value = _value;
                on_change(m_value);
            }
    };
}

#endif
