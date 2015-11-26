#ifndef __PROPERTY_HPP__BRAIN__
#define  __PROPERTY_HPP__BRAIN__

#include "pattern.hpp"

namespace brain
{
    /// //////// ///
    /// Property ///
    /// //////// ///


    template<typename property_t>
    const auto& get(
        const property_t& p)
    {
        return p.get();
    }


    template < typename property_t,
             typename type_t >
    void set(
        property_t& p,
        type_t& value)
    {
        p.set(value);
    }


    template < typename property_t,
             typename type_t >
    void set(
        property_t& p,
        type_t && value)
    {
        p.set(value);
    }


    /// Base class for
    /// a politic class
    template<typename type_t>
    struct politic:
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
    struct invalid_data:
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
    struct no_effect :
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

    /// A property represents
    /// an class attribute.
    /// The using of a property
    /// instead of traditionnal
    /// attributes enables to
    /// avoid the use of the
    /// gette / setter.
    /// politics_t is a list<...>
    /// of politics class that valids
    /// the data when it's set
    template < typename type_t,
             typename politic_t =
             no_effect<type_t >>
    class property
    {

        public:
            using type = property;
            using value_type = type_t;
            /// Politic used to
            /// validate the value
            /// of the property
            static politic_t s_politic;

        private:
            /// Private value of
            /// of the attribute
            value_type m_prop;

        public:
            /// Build a default
            constexpr property()
            {
            }


            /// Build with copy value
            property(
                const type_t& value)
                : m_prop((s_politic(value), value))
            {
            }


            /// Build with move value
            property(
                type_t && value)
                : m_prop((s_politic(value), value))
            {
            }


            /// Build with copy
            /// polymorphic value
            template<typename other_t>
            property(
                const other_t & value)
                : m_prop((s_politic(value), value))
            {
            }


            /// Build with move
            /// polymorphic value
            template<typename other_t>
            property(
                other_t && value)
                : m_prop((s_politic(value), value))
            {
            }


        public:
            /// Copy assignement
            property& operator=(
                const type_t& value)
            {
                m_prop = (s_politic(value), value);
                return *this;
            }


            /// Move assignement
            property& operator=(
                type_t && value)
            {
                m_prop = (s_politic(value), value);
                return *this;
            }


            /// Polymorphic move
            /// assignement
            template<typename other_t>
            property& operator=(
                const other_t& value)
            {
                m_prop = (s_politic(value), value);
                return *this;
            }


            /// Polymorphic move
            /// assignement
            template<typename other_t>
            property& operator=(
                other_t && value)
            {
                m_prop = (s_politic(value), value);
                return *this;
            }

        public:
            /// Value type caster
            operator value_type&()
            {
                return m_prop;
            }


            /// Const value type
            /// caster
            operator const value_type&() const
            {
                return m_prop;
            }
    };


    /// Static initialisation
    /// of property::s_politic
    template < typename type_t,
             typename politic_t >
    politic_t property<type_t, politic_t>::s_politic {};


    /// Overload of << operator
    /// for property<type_t>.
    /// Simple indirection of
    /// type_t::operator<<()
    template <class type_t, typename other_politic_t>
    std::ostream& operator<<(
        std::ostream& os,
        const property<type_t, other_politic_t>& p)
    {
        return os << static_cast<const type_t&>(p);
    }


    /// A reference is wrapper
    /// for c++ reference. A
    /// reference must be initialised
    /// at construction.
    template < typename type_t,
             typename politic_t = no_effect<type_t >>
    class reference
    {
        public:
            using type = reference;
            using value_type = type_t;
            using pointer_type = value_type*;
            using ref_type = value_type&;
            using cref_type = const value_type&;
            using uref_type = value_type &&;


        private:
            pointer_type m_value {nullptr};
            static const politic_t s_politic;


        public:
            /// Default trivial
            /// constructor
            reference() = default;

            ///
            reference(
                ref_type value):
                m_value((s_politic(value),
                         std::addressof(value)))
            {
            }


            reference(
                uref_type) = delete;


            reference(
                const reference&) = default;


        public:
            ///
            reference& operator=(
                const reference& other)
            {
                if(this != &other)
                    m_value =
                        (s_politic(other),
                         other.m_value);

                return *this;
            }


            /// Toggles the stored
            /// pointer to the new
            /// object.
            reference& operator=(
                ref_type value)
            {
                m_value =
                    (s_politic(value),
                     std::addressof(value));

                return *this;
            }

            reference& operator=(
                uref_type value)
            {
                *m_value =
                    (s_politic(value),
                     value);

                return *this;
            }

        public:
            /// Read only getter on
            /// the stored reference.
            /// Must be initialized
            /// before use this.
            operator cref_type() const
            {
                return *m_value;
            }

            cref_type get() const
            {
                return *m_value;
            }

            void set(
                uref_type value)
            {
                this->operator =(value);
            }

            void set(
                ref_type value)
            {
                this->operator =(value);
            }
    };


    template < typename type_t,
             typename politic_t >
    const politic_t reference<type_t, politic_t>::s_politic {};


    template<typename type_t>
    class component
    {
        public:
            using type = component;
            using value_type = type_t;
            using pointer_type = value_type*;
            using ref_type = value_type&;
            using cref_type = const value_type&;
            using uref_type = value_type &&;
        private:
            pointer_type m_value;
        public:
    };
}

#endif
