#ifndef __PROPERTY_HPP__BRAIN__
#define  __PROPERTY_HPP__BRAIN__

#include "pattern.hpp"

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

    /// Generic property interface
    /// that defines the accessor/
    /// mutators
    template<typename type_t>
    class property /// validated
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
            inline virtual const type_t& get() const = 0;


            /// General lvalue setter
            inline virtual void set(
                type_t& value) = 0;


            /// General rvalue setter
            inline virtual void set(
                type_t && value) = 0;


            /// Returns true if
            /// the property contains
            /// a value, else false.
            inline virtual bool valid() const = 0;
    };


    /// General getter
    /// for property
    /// interface
    template<typename property_t>
    inline const auto& get(
        const property_t& p)
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


    /// A monomorphe represents
    /// an class attribute.
    /// The using of a monomorphe
    /// instead of traditionnal
    /// attributes enables to
    /// avoid the use of the
    /// gette / setter.
    template < typename type_t,
             typename politic_t =
             no_effect<type_t >>
    class monomorphe /// Validated
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
            monomorphe() = default;


            /// Build with copy value
            monomorphe(
                cref_type value):
                m_value((s_politic(value), value))
            {
            }


            /// Build with move value
            monomorphe(
                uref_type value):
                m_value((s_politic(value), value))
            {
            }


            /// Build with copy
            /// polymorphic value
            template<typename other_t>
            monomorphe(
                const other_t & value):
                m_value((s_politic(value), value))
            {
            }


            /// Default destructor
            ~monomorphe() = default;

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
            /// Getter on m_value
            inline virtual cref_type get() const
            {
                return m_value;
            }


            /// Setter on m_value
            inline virtual void set(
                uref_type value)
            {
                this->operator =(value);
            }


            /// Setter on m_value
            inline virtual void set(
                ref_type value)
            {
                this->operator =(value);
            }


            /// Always contains a
            /// value
            inline virtual bool valid() const
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
    /*template <class type_t, typename other_politic_t>
    std::ostream& operator<<(
        std::ostream& os,
        const monomorphe<type_t, other_politic_t>& p)
    {
        return os << static_cast<const type_t&>(p);
    }*/


    /// Enable to modelise
    /// a component (strength
    /// aggregation) in modele
    /// design
    template < typename type_t>
    class component: /// Validated
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


            /// Reference constructor
            /// of value_type based on
            /// args transmitted to the
            /// right constructor of
            /// value_type
            component(
                ref_type value):
                m_value(new value_type(value))
            {
            }


            /// UReference constructor
            /// of value_type based on
            /// args transmitted to the
            /// right constructor of
            /// value_type
            component(
                uref_type value):
                m_value(new value_type(value))
            {
            }


            /// CReference constructor
            /// of value_type based on
            /// args transmitted to the
            /// right constructor of
            /// value_type
            component(
                cref_type value):
                m_value(new value_type(value))
            {
            }


            /// POlymorphic constructor
            /// of value_type based on
            /// args transmitted to the
            /// right constructor of
            /// value_type
            template<typename derived_t>
            component(
                derived_t && value):
                m_value(new derived_t(value))
            {
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


            /// POlymorphic constructor
            /// of value_type based on
            /// args transmitted to the
            /// right constructor of
            /// value_type
            template<typename derived_t>
            component(
                derived_t* value):
                m_value(value)
            {
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

            /// Polymorphic reference
            /// assignement
            template<typename derived_t>
            component& operator=(
                derived_t && value)
            {
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


            /// Polymorphic pointer
            /// assignement
            template<typename derived_t>
            component& operator=(
                derived_t* value)
            {
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
            /// Getter on m_value
            inline virtual cref_type get() const
            {
                return *m_value;
            }


            /// Setter on m_value
            inline virtual void set(
                uref_type value)
            {
                this->operator =(value);
            }


            /// Setter on m_value
            inline virtual void set(
                ref_type value)
            {
                this->operator =(value);
            }


            /// Validator on m_value
            inline virtual bool valid() const
            {
                return static_cast<bool>(m_value);
            }
    };


    /// TODO
    template <typename type_t>
    class reference:
        public property<type_t>
    {
        private:
            struct counter
            {
                size_t count {0u};
            };

        public:
            using type = reference;
            using value_type = type_t;
            using pointer_type = value_type*;
            using ref_type = value_type&;
            using cref_type = const value_type&;
            using uref_type = value_type &&;

        private:
            pointer_type m_value {nullptr};
            counter* m_counter {nullptr};

        public:
            /// Default constructor
            reference() = default;


            /// Constructor for
            /// pointer_type
            reference(
                pointer_type value):
                m_value(value)
            {
                if(valid())
                {
                    m_counter = new counter();
                    m_counter->count++;
                }
            }


            /// Copy constructor
            reference(
                const reference& other):
                m_value(other.m_value)
            {
                if(valid())
                {
                    m_counter = other.m_counter;
                    m_counter->count++;
                }
            }


            /// Move constructor
            reference(
                reference && other):
                m_value(other.m_value),
                m_counter(other.m_counter)
            {
            }


            /// Destructor
            ~reference()
            {
                if(valid())
                    if(alone())
                    {
                        delete m_value;
                        delete m_counter;
                    }

                    else
                        m_counter->count--;
            }


        public:
            /// pointer assignement
            reference& operator=(
                pointer_type value)
            {
                if(value != m_value)
                {
                    if(valid())
                        if(alone())
                        {
                            auto* tmp = m_value;
                            delete tmp;
                        }

                        else
                        {
                            m_counter->count--;
                            m_counter = new counter();
                        }

                    m_value = value;
                }

                return *this;
            }


            /// Copy assignement
            reference& operator=(
                const reference& other)
            {
                if(this != &other)
                {
                    if(m_value != other.m_value)
                    {
                        if(valid())
                            if(alone())
                            {
                                auto* tmp = m_value;
                                delete tmp;
                            }

                            else
                            {
                                m_counter->count--;
                                m_counter = new counter();
                            }

                        m_value = other.m_value;
                    }
                    else 
                    {
                        
                    m}
                }

                return *this;
            }


            /// Move assignement
            reference& operator=(
                reference && other)
            {
                if(this != &other)
                {
                    m_counter = other.m_counter;
                    m_value = other.m_value;
                }

                return *this;
            }


        public:
            inline bool alone() const
            {
                return m_counter->count == 1;
            }



        public:
            /// Getter on m_value
            inline virtual cref_type get() const
            {
                return *m_value;
            }


            /// Setter on m_value
            inline virtual void set(
                uref_type value)
            {
                this->operator =(value);
            }


            /// Setter on m_value
            inline virtual void set(
                ref_type value)
            {
                this->operator =(value);
            }


            /// Validator on m_value
            inline virtual bool valid() const
            {
                return m_value != nullptr;
            }
    };



}

#endif
