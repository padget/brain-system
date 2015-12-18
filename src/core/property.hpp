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


    /// Implementation for
    /// type_t that's not
    /// pointer.
    template<typename type_t>
    class property<type_t, managing::none> final
    {
            /// Embedded value
            type_t m_value;
            std::function<type_t&()> m_get;

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


            /// Constructor by copy cref
            property(
                property && other):
                m_value(std::move(other.m_value))
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
            }


            /// Setter on uref
            void operator()(
                type_t && _value)
            {
                m_value = _value;
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
            }


            /// Setter on uref
            void set(
                type_t && _value)
            {
                m_value = _value;
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


        public:
            /// Constructor by pointer
            property(
                type_t* _value = nullptr):
                m_value(_value)
            {
            }


            /// Constructor by
            /// smart pointer
            property(
                std::unique_ptr<type_t> && _value):
                m_value {_value}
            {
            }


            /// Constructor by
            /// smart pointer
            /// from another
            /// type
            template<typename other_t>
            property(
                std::unique_ptr<other_t> && _value):
                m_value {_value}
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
                    m_value.reset(_value);
            }


            void operator()(
                std::unique_ptr<type_t> && _value)
            {
                m_value = _value;
            }


            template<typename other_t>
            void operator()(
                std::unique_ptr<other_t> && _value)
            {
                m_value = _value;
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
                    m_value.reset(_value);
            }


            void set(
                std::unique_ptr<type_t> && _value)
            {
                m_value = _value;
            }


            template<typename other_t>
            void set(
                std::unique_ptr<other_t> && _value)
            {
                m_value = _value;
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

        public:
            /// Basic constructor
            /// based on pointer
            property(
                type_t* _value = nullptr):
                m_value {_value}
            {
            }


            property(
                const std::shared_ptr<type_t>& _value):
                m_value {_value}
            {
            }


            property(
                std::shared_ptr<type_t> && _value):
                m_value {_value}
            {
            }


            template<typename other_t>
            property(
                const std::shared_ptr<other_t>& _value):
                m_value {_value}
            {
            }


            template<typename other_t>
            property(
                std::shared_ptr<other_t> && _value):
                m_value {_value}
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
            void operator()(type_t* _value)
            {
                if(_value != m_value.get())
                    m_value = _value;
            }


            void operator()(
                const std::shared_ptr<type_t>& _value)
            {
                m_value = _value;
            }


            void operator()(
                std::shared_ptr<type_t> && _value)
            {
                m_value = _value;
            }


            template<typename other_t>
            void operator()(
                const std::shared_ptr<other_t>& _value)
            {
                m_value = _value;
            }


            template<typename other_t>
            void operator()(
                std::shared_ptr<other_t> && _value)
            {
                m_value = _value;
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
                type_t* _value)
            {
                if(_value != m_value.get())
                    m_value.reset(_value);
            }


            void set(
                const std::shared_ptr<type_t>& _value)
            {
                m_value = _value;
            }


            void set(
                std::shared_ptr<type_t> && _value)
            {
                m_value = _value;
            }


            template<typename other_t>
            void set(
                const std::shared_ptr<other_t>& _value)
            {
                m_value = _value;
            }


            template<typename other_t>
            void set(
                std::shared_ptr<other_t> && _value)
            {
                m_value = _value;
            }
    };
}

#endif
