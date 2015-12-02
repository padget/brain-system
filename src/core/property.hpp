#ifndef __PROPERTY_HPP__BRAIN__
#define  __PROPERTY_HPP__BRAIN__

#include "pattern.hpp"

namespace brain
{


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

    /// ////////////////////////// ///
    /// General property interface ///
    /// ////////////////////////// ///

    /// Generic property interface
    /// that defines the accessor/
    /// mutators
    template<typename type_t>
    class property
    {
        protected:
            using type = property;
            using value_type = type_t;
            using pointer_type = value_type*;
            using ref_type = value_type&;
            using cref_type = const value_type&;
            using uref_type = value_type &&;

        public:
            /// General constness getter
            virtual const type_t& get() const = 0;


            /// General lvalue setter
            virtual void set(
                type_t& value) = 0;


            /// General rvalue setter
            virtual void set(
                type_t && value) = 0;


            /// Returns true if
            /// the property contains
            /// a value, else false.
            virtual bool valid() const = 0;
    };


    /// General getter
    /// for property
    /// interface
    template<typename property_t>
    const auto& get(
        const property_t& p)
    {
        return p.get();
    }


    /// General setter
    /// for property
    /// interface
    template < typename property_t,
             typename type_t >
    void set(
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
    void set(
        property_t& p,
        type_t && value)
    {
        p.set(value);
    }


    /// General validator
    /// for property
    /// interface
    template<typename property_t>
    auto valid(
        const property_t& p)
    {
        return p.valid();
    }


    /// //////// ///
    /// Property ///
    /// //////// ///


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
    class monomorphe
    {
        public:
            using type = monomorphe;
            using value_type = type_t;
            using pointer_type = value_type*;
            using ref_type = value_type&;
            using cref_type = const value_type&;
            using uref_type = value_type &&;

            /// Politic used to
            /// validate the value
            /// of the property
            static politic_t s_politic;

        private:
            /// Private value of
            /// of the attribute
            value_type m_value;

        public:
            /// Build a default
            constexpr monomorphe() = default;


            /// Build with copy value
            monomorphe(
                cref_type value)
                : m_value((s_politic(value), value))
            {
            }


            /// Build with move value
            monomorphe(
                uref_type value)
                : m_value((s_politic(value), value))
            {
            }


            /// Build with copy
            /// polymorphic value
            template<typename other_t>
            monomorphe(
                const other_t & value)
                : m_value((s_politic(value), value))
            {
            }


            /// Build with move
            /// polymorphic value
            template<typename other_t>
            monomorphe(
                other_t && value)
                : m_value((s_politic(value), value))
            {
            }


        public:
            /// Copy assignement
            monomorphe& operator=(
                cref_type value)
            {
                m_value = (s_politic(value), value);
                return *this;
            }


            /// Move assignement
            monomorphe& operator=(
                uref_type value)
            {
                m_value = (s_politic(value), value);
                return *this;
            }


            /// Polymorphic move
            /// assignement
            template<typename other_t>
            monomorphe& operator=(
                const other_t& value)
            {
                m_value = (s_politic(value), value);
                return *this;
            }


            /// Polymorphic move
            /// assignement
            template<typename other_t>
            monomorphe& operator=(
                other_t && value)
            {
                m_value = (s_politic(value), value);
                return *this;
            }

        public:
            /// Value type caster
            operator ref_type()
            {
                return m_value;
            }


            /// Const value type
            /// caster
            operator cref_type() const
            {
                return m_value;
            }


        public:
            ///
            virtual cref_type get() const
            {
                return m_value;
            }


            ///
            virtual void set(
                uref_type value)
            {
                this->operator =(value);
            }


            ///
            virtual void set(
                ref_type value)
            {
                this->operator =(value);
            }


            /// Always contains a
            /// value
            virtual bool valid() const
            {
                return true;
            }
    };


    /// Static initialisation
    /// of property::s_politic
    template < typename type_t,
             typename politic_t >
    politic_t monomorphe<type_t, politic_t>::s_politic {};


    /// Overload of << operator
    /// for property<type_t>.
    /// Simple indirection of
    /// type_t::operator<<()
    template <class type_t, typename other_politic_t>
    std::ostream& operator<<(
        std::ostream& os,
        const monomorphe<type_t, other_politic_t>& p)
    {
        return os << static_cast<const type_t&>(p);
    }


    /// A reference is wrapper
    /// for c++ reference.
    /// Doesn't support temporary
    /// reference
    template < typename type_t,
             typename politic_t = no_effect<type_t >>
    class reference:
        public property<type_t>
    {
        public:
            using type = reference;
            using value_type = type_t;
            using pointer_type = value_type*;
            using ref_type = value_type&;
            using cref_type = const value_type&;
            using uref_type = value_type &&;


        private:
            /// Embedded pointer
            /// on value
            pointer_type m_value;


            /// politic checked before
            /// each change of m_value
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


            /// Non move construction
            /// possible. Indeed, the
            /// reference must not be
            /// temporary
            reference(
                uref_type) = delete;


            ///
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


            ///
            reference& operator=(
                uref_type value) = delete;


        public:
            /// Read only getter on
            /// the stored reference.
            /// Must be initialized
            /// before use this.
            operator cref_type() const
            {
                return *m_value;
            }


            ///
            virtual cref_type get() const
            {
                return *m_value;
            }


            ///
            virtual void set(
                uref_type value)
            {
                this->operator =(value);
            }


            ///
            virtual void set(
                ref_type value)
            {
                this->operator =(value);
            }


            ///
            virtual bool valid() const
            {
                return m_value != nullptr;
            }
    };


    template < typename type_t,
             typename politic_t >
    const politic_t reference<type_t, politic_t>::s_politic {};



    /// Enable to modelise
    /// a component (strength
    /// aggregation) in modele
    /// design
    template < typename type_t,
             typename politic_t = no_effect<type_t >>
    class component:
        public property<type_t>
    {
        public:
            using type = component;
            using value_type = type_t;
            using pointer_type = value_type*;
            using ref_type = value_type&;
            using cref_type = const value_type&;
            using uref_type = value_type &&;
        private:

            /// Embedded pointer
            /// on value
            std::unique_ptr<value_type> m_value;

        public:

            /// Default trivial
            /// constructor
            component() = default;


            /// Universal constructor
            /// of value_type based on
            /// args transmitted to the
            /// right constructor of
            /// value_type
            component(
                ref_type value):
                m_value(new value_type(value))
            {
            }


            component(
                uref_type value):
                m_value(new value_type(value))
            {
            }


            component(
                cref_type value):
                m_value(new value_type(value))
            {
            }

            template<typename derived_t>
            component(
                derived_t && value):
                m_value(new derived_t(value))
            {
                
                std::cout << "polymorphic ref cst" << std::endl;
            }


            /// If the argument is
            /// pointer_type, so
            /// this pointer is directly
            /// injected in the pointer
            component(
                pointer_type value):
                m_value(value)
            {
            }
            
            
            template<typename derived_t>
            component(
                derived_t* value):
                m_value(value)
            {
                
                std::cout << "polymorphic pointer cst" << std::endl;
            }


            /// Default move
            /// constructor
            component(
                component &&) = default;


            /// A the destruction
            /// of the component,
            /// the value is also
            /// destroyed
            ~component() = default;


        public:
            /// Copy assignement that
            /// delete old m_value and
            /// copy the new value into
            /// a new copy of value
            component& operator=(
                ref_type value)
            {
                m_value.reset(new value_type(value));

                return *this;
            }


            /// Copy assignement that
            /// delete old m_value and
            /// copy the new value into
            /// a new copy of value
            component& operator=(
                cref_type value)
            {
                m_value.reset(new value_type(value));

                return *this;
            }


            /// Move assignement that
            /// delete old m_value and
            /// copy the new value into
            /// a new copy of value
            component& operator=(
                uref_type value)
            {
                m_value.reset(new value_type(value));

                return *this;
            }
            
            template<typename derived_t>
            component& operator=(
                derived_t&& value)
            {
                std::cout << "polymorphic ref ass" << std::endl;
                m_value.reset(new derived_t(value));

                return *this;
            }


            /// Assignement by
            /// injection of a
            /// new pointer
            component& operator=(
                pointer_type value)
            {
                m_value.reset(value);

                return *this;
            }
            
            template<typename derived_t>
            component& operator=(
                derived_t* value)
            {
                
                std::cout << "polymorphic pointer ass" << std::endl;
                m_value.reset(value);

                return *this;
            }

        public:
            /// Read only getter on
            /// the stored component.
            /// Must be initialized
            /// before use this.
            operator cref_type() const
            {
                return *m_value;
            }


        public:
            ///
            virtual cref_type get() const
            {
                return *m_value;
            }


            virtual void set(
                uref_type value)
            {
                this->operator =(value);
            }

            virtual void set(
                ref_type value)
            {
                this->operator =(value);
            }

            ///
            virtual bool valid() const
            {
                return static_cast<bool>(m_value);
            }
    };
}

#endif
