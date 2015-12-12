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

    /// TODO Gestion des expcetions dans tous le fichier

    /// A monomorphe represents
    /// an class attribute.
    /// The using of a monomorphe
    /// instead of traditionnal
    /// attributes enables to
    /// avoid the use of the
    /// gette / setter.
    template <typename type_t>
    class monomorphe final/// Validated
    {
            static_assert(!meta::v_<std::is_pointer<type_t>>,
                          "monomorphe mustn't be used with pointers");

        public:
            using type =
                monomorphe;
            using value_type =
                type_t;
            using pointer_type =
                value_type*;
            using ref_type =
                value_type&;
            using cref_type =
                const value_type&;
            using uref_type =
                value_type &&;


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
                m_value(value)
            {
            }


            /// Build with move value
            monomorphe(
                uref_type value):
                m_value(value)
            {
            }


            /// Build with copy
            /// polymorphic value
            template<typename other_t>
            monomorphe(
                const other_t & value):
                m_value(value)
            {
            }


            /// Default destructor
            ~monomorphe() = default;

        public:
            /// Copy assignement
            monomorphe& operator=(
                cref_type value)
            {
                m_value = value;
                return *this;
            }


            /// Move assignement
            monomorphe& operator=(
                uref_type value)
            {
                m_value = value;
                return *this;
            }


            /// Polymorphic move
            /// assignement
            template<typename other_t>
            monomorphe& operator=(
                const other_t& value)
            {
                m_value = value;
                return *this;
            }


        public:
            /// Value type caster
            inline virtual ref_type operator()()
            {
                return m_value;
            }


            /// Const value type
            /// caster
            inline virtual cref_type operator()() const
            {
                return m_value;
            }


            ///
            inline virtual void operator()(ref_type value)
            {
                m_value = value;
            };


            ///
            inline virtual void operator()(cref_type value)
            {
                m_value = value;
            };


            ///
            inline virtual void operator()(uref_type value)
            {
                m_value = value;
            };


            ///
            inline virtual void operator()(pointer_type value)
            {
                m_value = *value;
            }


        public:
            /// Getter on m_value
            inline virtual cref_type get() const
            {
                return m_value;
            }


            /// TODO Doc + Test
            inline virtual ref_type get()
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


    /// Enable to modelise
    /// a component (strength
    /// aggregation) in modele
    /// design
    /// Polymorphe
    template <typename type_t>
    class component final /// Not validated
    {
            template<typename derived_t>
            friend class component;

        public:
            using type =
                component;
            using value_type =
                type_t;
            using pointer_type =
                value_type*;
            using ref_type =
                value_type&;
            using cref_type =
                const value_type&;
            using uref_type =
                value_type &&;


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
                std::cout << "WEEEEEHHH" << std::endl;
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


            /// TODO to test
            template<typename derived_t>
            component(
                component<derived_t> && other):
                m_value(std::move(other.m_value))
            {
            }

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


            /// TODO To test
            component& operator=(
                component &&) = default;



            /// TODO To test
            template<typename derived_t>
            component& operator=(
                component<derived_t> && other)
            {
                if(this != &other)
                    if(this.m_value != other.m_value)
                        this.m_value = other.m_value;
            }

        public:
            /// Read only getter on
            /// the stored component.
            /// Must be initialized
            /// before use this.
            inline cref_type operator()() const
            {
                return *m_value;
            }


            /// TODO DOc + Test
            inline ref_type operator()()
            {
                return *m_value;
            }


            ///TODO DOc + Test
            inline virtual void operator()(
                cref_type value)
            {
                std::cout << "cref_type" << std::endl;
                m_value.reset(new value_type(value));
            };


            ///TODO DOc + Test
            inline virtual void operator()(
                uref_type value)
            {
                std::cout << "uref_type" << std::endl;
                m_value.reset(new value_type(value));
            };


            /// TODO Doc  + Test
            template<typename derived_t>
            inline void operator()(
                derived_t && value)
            {
                m_value.reset(new meta::extract_basic_type_t<derived_t>(value));
            }


            ///TODO DOc + Test
            inline virtual void operator()(
                pointer_type value)
            {
                m_value.reset(value);
            }


        public:
            /// Getter on m_value
            inline virtual cref_type get() const
            {
                return *m_value;
            }


            /// TODO Doc + TEst
            inline virtual ref_type get()
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



    /// Wrapper of vector
    /// of component
    template<typename type_t>
    using component_vec =
        std::vector<component<type_t>>;


    /// Wrapper of list
    /// of component
    template<typename type_t>
    using component_list =
        std::list<component<type_t>>;


    /// Wrapper of set
    /// of component
    template<typename type_t>
    using component_set =
        std::set<component<type_t>>;


    /// A shared component is a
    /// component that can be shared
    /// between several instances
    template<typename type_t>
    class shared_component final
    {
            template<typename derived_t>
            friend class shared_component;
        public:
            using type =
                shared_component;
            using value_type =
                type_t;
            using pointer_type =
                value_type*;
            using ref_type =
                value_type&;
            using cref_type =
                const value_type&;
            using uref_type =
                value_type &&;

        private:
            /// TODO doc
            std::shared_ptr<value_type> m_value;

        public:
            /// TODO doc
            shared_component() = default;


            /// TODO doc
            shared_component(
                ref_type value):
                m_value(new value_type(value))
            {
            }


            /// TODO doc
            shared_component(
                cref_type value):
                m_value(new value_type(value))
            {
            }


            /// TODO doc
            shared_component(
                uref_type value):
                m_value(new value_type(value))
            {
            }


            /// TODO doc
            template<typename derived_t>
            shared_component(
                derived_t && value):
                m_value(new meta::extract_basic_type_t<derived_t>(value))
            {
            }


            /// TODO doc
            shared_component(
                pointer_type value):
                m_value(value)
            {
            }


            /// TODO doc test
            template<typename derived_t>
            shared_component(
                derived_t* value):
                m_value(value)
            {
            }

            /// TODO doc
            shared_component(
                const value_type* value):
                m_value(new value_type(*value))
            {
            }


            /// TODO doc test
            template<typename derived_t>
            shared_component(
                const derived_t* value):
                m_value(new derived_t(*value))
            {
            }


            /// TODO doc test
            shared_component(
                const shared_component&) = default;


            /// TODO doc test
            template<typename derived_t>
            shared_component(
                const shared_component<derived_t>& other):
                m_value(other.m_value)
            {
            }


            /// TODO doc test
            shared_component(
                shared_component &&) = default;


            /// TODO doc test
            template<typename derived_t>
            shared_component(
                shared_component<derived_t> && other):
                m_value(std::move(other.m_value))
            {}


            /// TODO doc test
            ~shared_component() = default;

        public:
            /// TODO doc test
            shared_component& operator=(
                ref_type value)
            {
                if(std::addressof(value) != m_value.get())
                    m_value.reset(new value_type(value));

                return *this;
            }


            /// TODO doc test
            shared_component& operator=(
                cref_type value)
            {
                if(std::addressof(value) != m_value.get())
                    m_value.reset(new value_type(value));

                return *this;
            }


            /// TODO doc test
            shared_component& operator=(
                uref_type value)
            {
                if(std::addressof(value) != m_value.get())
                    m_value.reset(new value_type(value));

                return *this;
            }


            /// TODO doc test
            template<typename derived_t>
            shared_component& operator=(
                derived_t && value)
            {
                if(std::addressof(value) != m_value.get())
                    m_value.reset(new value_type(value));

                return *this;
            }


            /// TODO doc test
            shared_component& operator=(
                pointer_type value)
            {
                if(value != m_value.get())
                    m_value.reset(value);

                return *this;
            }


            /// TODO doc test
            template<typename derived_t>
            shared_component& operator=(
                derived_t* value)
            {
                if(value != m_value.get())
                    m_value.reset(value);

                return *this;
            }


            /// TODO doc test
            shared_component& operator=(
                const shared_component&) = default;


            /// TODO doc test
            template<typename derived_t>
            shared_component& operator=(
                const shared_component<derived_t>& other)
            {
                m_value = other.m_value;
                return *this;
            }


            /// TODO doc test
            shared_component& operator=(
                shared_component &&) = default;


            /// TODO doc test
            template<typename derived_t>
            shared_component& operator=(
                shared_component<derived_t> && other)
            {
                m_value = std::move(other.m_value);
                return *this;
            };


        public:
            /// TODO doc test
            virtual inline cref_type operator()() const
            {
                return *m_value;
            }


            /// TODO doc test
            virtual inline ref_type operator()()
            {
                return *m_value;
            }


            ///TODO DOc + Test
            inline virtual void operator()(
                ref_type value)
            {
                m_value.reset(new value_type(value));
            };


            ///TODO DOc + Test
            inline virtual void operator()(
                cref_type value)
            {
                m_value.reset(new value_type(value));
            };


            ///TODO DOc + Test
            inline virtual void operator()(
                uref_type value)
            {
                m_value.reset(new value_type(value));
            };


            ///TODO DOc + Test
            inline virtual void operator()(
                pointer_type value)
            {
                m_value.reset(value);
            }


        public:
            /// Getter on m_value
            inline virtual cref_type get() const
            {
                return *m_value;
            }


            /// TODO doc test
            inline virtual ref_type get()
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


    /// Wrapper of vector
    /// of shared_component
    template<typename type_t>
    using scomponent_vec =
        std::vector<shared_component<type_t>>;


    /// Wrapper of list
    /// of shared_component
    template<typename type_t>
    using scomponent_list =
        std::list<shared_component<type_t>>;


    /// Wrapper of set
    /// of shared_component
    template<typename type_t>
    using scomponent_set =
        std::set<shared_component<type_t>>;


    /// TODO
    template <typename type_t>
    class reference final
    {
            template<typename derived_t>
            friend class reference;


            template<typename derived_t>
            friend class shared_component;


        public:
            using type =
                reference;
            using value_type =
                type_t;
            using pointer_type =
                value_type*;
            using ref_type =
                value_type&;
            using cref_type =
                const value_type&;
            using uref_type =
                value_type &&;

        private:
            /// TODO doc test
            std::weak_ptr<pointer_type> m_value;


        public:
            /// Default constructor
            reference() = default;


            /// TODO doc test
            reference(
                const reference&) = default;


            /// TODO doc test
            template<typename derived_t>
            reference(
                const reference<derived_t>& r):
                m_value(r.m_value)
            {
            }


            /// TODO doc test
            template<typename derived_t>
            reference(
                const shared_component<derived_t>& s):
                m_value(s.m_value)
            {
            }


            /// TODO doc test
            reference(
                reference &&) = default;


            /// TODO doc test
            template<typename derived_t>
            reference(
                reference<derived_t> && r):
                m_value(std::move(r.m_value))
            {
            }


        public:
            /// TODO doc test
            reference& operator=(
                const reference&) = default;


            /// TODO doc test
            template<typename derived_t>
            reference& operator=(
                const reference<derived_t>& other)
            {
                m_value = other.m_value;
            }


            /// TODO doc test
            template<typename derived_t>
            reference& operator=(
                const shared_component<derived_t>& other)
            {
                m_value = other.m_value;
            }


            /// TODO doc test
            reference& operator= (
                reference &&) = default;


            /// TODO doc test
            template<typename derived_t>
            reference& operator=(
                reference<derived_t> && other)
            {
                m_value = other.m_value;
            }


        public:
            /// TODO doc test
            inline virtual cref_type operator()() const
            {
                return *m_value;
            }


            /// TODO Doc test
            inline virtual ref_type operator()()
            {
                return *m_value;
            }


        public:
            /// Getter on m_value
            inline virtual cref_type get() const
            {
                return *m_value;
            }


            /// Getter on m_value
            inline virtual ref_type get()
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
                return m_value.expired();
            }
    };
}

#endif
