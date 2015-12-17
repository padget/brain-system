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
    /// Base class for
    /// a politic class
    template<typename type_t>
    struct politic: /// validated
            pattag::politic
    {
        /// Default destructor
        virtual ~politic() = default;


        /// Return true if
        /// the value respects
        /// the politic implemented,
        /// else must return false
        virtual bool operator()(
            const type_t& value) const = 0;


        /// Return true if
        /// the value respects
        /// the politic implemented,
        /// else must return false
        virtual bool operator()(
            type_t && value) const = 0;
    };


    /// Exception that must
    /// be used when the data
    /// is not validated by
    /// a politic
    struct invalid_data: /// validated
        public std::exception
    {
            /// Default constructor
            /// Initialises m_message
            /// with the default message
            invalid_data():
                m_message("brain::invalid_data")
            {
            }


            /// Construct that initialises
            /// the default message with
            /// the cause of invalid data
            invalid_data(
                const std::string& cause) :
                m_message(std::string("brain::invalid_data : ") += cause)
            {
            }


            /// Default destructor
            virtual ~invalid_data() = default;


            /// Returns m_message
            virtual const char*
            what() const noexcept
            {
                return m_message.c_str();
            }

        private:
            std::string m_message;
    };


    /// Politic that has
    /// no effect on the
    /// value of type_t
    template<typename type_t>
    struct no_effect : /// validated
        public politic<type_t>
    {
        /// Returns true
        virtual bool operator()(
            const type_t& value) const
        {
            return meta::v_ <
                   std::true_type >;
        };


        /// Returns true
        virtual bool operator()(
            type_t && value) const
        {
            return meta::v_ <
                   std::true_type >;
        };
    };

    /// ////////////////////////// ///
    /// General property interface ///
    /// ////////////////////////// ///


    /// General getter
    /// for property
    /// interface
    template<typename property_t>
    inline const auto& get(
        const property_t& p)
    {
        return p.get();
    }


    /// General getter
    /// for property
    /// interface
    template<typename property_t>
    inline auto& get(
        property_t& p)
    {
        return p.get();
    }


    /// General setter
    /// for property
    /// interface
    template < typename property_t,
             typename type_t >
    inline void set(
        property_t& p,
        type_t& value)
    {
        p.set(value);
    }


    /// General setter
    /// for property
    /// interface
    template < typename property_t,
             typename type_t >
    inline void set(
        property_t& p,
        type_t && value)
    {
        p.set(value);
    }


    /// General validator
    /// for property
    /// interface
    template<typename property_t>
    inline auto valid(
        const property_t& p)
    {
        return p.valid();
    }


    /// //////// ///
    /// Property ///
    /// //////// ///


    /// Generic property
    template < typename type_t,   /// Embedded type
             bool _is_component = true > /// Flag on life cycle on embedded value
    class property;

    /// Forbid the use
    /// of type_t&
    template < typename type_t,
             bool _is_component >
    class property<type_t&, _is_component>;


    /// Forbid the use
    /// of const type_t&
    template < typename type_t,
             bool _is_component >
    class property<const type_t&, _is_component>;


    /// Forbid the use
    /// of type_t&&
    template < typename type_t,
             bool _is_component >
    class property < type_t && , _is_component >;


    /// Implementation for
    /// type_t that's not
    /// pointer.
    template<typename type_t>
    class property<type_t, true> final
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


            /// Constructor by copy cref
            property(
                property && other):
                m_value(std::move(other.m_value))
            {
            }


            /// Default destructor
            ~property() = default;


        public:
            /// TODO Deleted operator=()

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
    class property<const type_t, true> final
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
    class property<type_t*, true> final
    {
            std::unique_ptr<type_t> m_value;

        public:
            /// Constructor by pointer
            property(
                type_t* _value = nullptr):
                m_value(_value)
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
            type_t& operator()()
            {
                return *m_value;
            }


            /// Getter by cref
            const type_t& operator()() const
            {
                return *m_value;
            }


            /// Setter by cref
            void operator()(
                const type_t& _value)
            {
                *m_value = _value;
            }


            /// Setter by uref
            void operator()(
                type_t && _value)
            {
                *m_value = _value;
            }


            /// Setter by pointer
            /// The pointer must not
            /// managed by any other
            /// agent
            void operator()(
                type_t* _value)
            {
                m_value.reset(_value);
            }


        public:
            /// Getter by cref
            const type_t& get() const
            {
                return *m_value;
            }


            /// Getter by ref
            type_t& get()
            {
                return *m_value;
            }


            /// Setter by cref
            void set(
                const type_t& _value)
            {
                *m_value = _value;
            }


            /// Setter by uref
            void set(
                type_t && _value)
            {
                *m_value = _value;
            }


            /// Setter by pointer
            /// The pointer must not
            /// managed by any other
            /// agent
            void set(
                type_t* _value = nullptr)
            {
                m_value.reset(_value);
            }
    };


    /// Implementation for
    /// type that is pointer
    /// and that considered
    /// as reference
    template<typename type_t>
    class property<type_t*, false> final
    {
            type_t* m_value;


        public:
            const type_t& get() const
            {
                return m_value;
            }

            type_t& get()
            {
                return m_value;
            }

            void set(const type_t& _value)
            {
                m_value = _value;
            }

            void set(type_t && _value)
            {
                m_value = _value;
            }
    };


}

#endif
