#ifndef __BRAIN_ANY_HPP__
#define __BRAIN_ANY_HPP__

#include "property.hpp"
#include <type_traits>

namespace brain
{
    /// An any object
    /// can embedded
    /// any type
    class any
    {
        public:
            /// Declaration of
            /// class placeholder
            class placeholder;


            /// Declaration of
            /// class holder
            template<typename type_t>
            class holder;


        private:
            /// The any_cast
            /// operation needs
            /// to access to the
            /// private content
            template<typename type_t>
            friend type_t* any_cast(
                any *);


            /// Content that can
            /// be of any type.
            /// A placeholder that
            /// really is a holder
            property<placeholder*> content;


        public:
            /// Default constructor
            any() = default;


            /// Constructor by copy
            /// of cref of the type_t
            /// object. Builds a holder
            /// pointer copy of this cref
            template<typename type_t>
            any(
                const type_t & value):
                content {new holder<type_t> {value}}
            {
            }


            /*
             * , typename boost::disable_if<boost::is_same<any&, type_t> >::type* = 0 // disable if value has type `any&`
                        , typename boost::disable_if<boost::is_const<type_t> >::type* = 0) // disable if value has type `const type_t&&`
             */
            // Perfect forwarding of type_t
            /// Constructor by move
            /// of an object of type_t
            template<typename type_t>
            any(type_t && value):
                content(new holder<meta::t_<std::decay<type_t>>>(static_cast < type_t && >(value)))
            {
            }


            /// Constructor by copy
            any(
                const any & other):
                content(other.content() ?
                        other.content()->clone() :
                        nullptr)
            {
            }


            /// Constructor by move
            any(any && other) :
                content {other.content()}
            {
                other.content(nullptr);
            }


            /// Destructor that
            /// deletes the pointer
            ~any()
            {
                clear();
            }


        public:
            /// Default operator=
            /// by copy
            any & operator=(
                const any&) = default;


            /// Assignement by
            /// move
            any & operator=(
                any && other)
            {
                if(this != &other)
                {
                    /// Moves the content
                    /// of the other and 
                    /// replaces the other
                    /// content by a nullptr
                    content(other.content());
                    other.content(nullptr);
                }

                return *this;
            }


        public:
            /// Returns true
            /// if the content
            /// different from
            /// nullptr
            bool empty() const
            {
                return content() != nullptr;
            }


            /// Deletes the
            /// content pointer
            void clear()
            {
                delete content();
                content(nullptr);
            }


            /// Returns the
            /// type_info of
            /// embedded content
            /// if it isn't empty
            /// else returns the
            /// the void type_info
            const std::type_info& type() const
            {
                return empty() ?
                       content()->type() :
                       typeid(void);
            }


        public:
            /// A fake class that
            /// is used to be inherited
            /// by the real class holder
            /// that contains the
            /// effective value
            class placeholder
            {
                public:
                    /// Default destructor
                    virtual ~placeholder() = default;


                public:
                    /// Returns the type
                    /// of the embedded
                    /// value of type_t
                    virtual const std::type_info& type() const = 0;


                    /// Clone the object
                    /// by polymorphism
                    virtual placeholder* clone() const = 0;
            };


            /// Effective class
            /// that contains the
            /// real value of type_t
            template<typename type_t>
            class holder :
                public placeholder
            {
                public:
                    /// Embedded real
                    /// value of type_t
                    property<type_t> held;


                public:
                    /// Constructor by copy
                    /// of the value from
                    /// type_t
                    holder(
                        const type_t & value)
                        : held(value)
                    {
                    }


                    /// Constructor by move
                    /// of the value from
                    /// type_t
                    holder(
                        type_t && value)
                        : held(static_cast < type_t && >(value))
                    {
                    }


                public:
                    /// Delete the operator=
                    /// by copy
                    holder & operator=(
                        const holder &) = delete;


                public:
                    /// Overload of the
                    /// methode type from
                    /// placeholder class
                    virtual const std::type_info & type() const
                    {
                        return typeid(type_t);
                    }


                    /// Overload of the
                    /// methode clone from
                    /// placeholder class
                    virtual placeholder * clone() const
                    {
                        return new holder(held());
                    }
            };
    };


    /// Exception that
    /// is thrown when
    /// a cast is
    /// illformed
    class bad_any_cast :
        public std::exception
    {
        public:
            /// Overload of the
            /// function what to
            /// express the error
            virtual const char * what() const noexcept
            {
                return "brain::bad_any_cast: "
                       "failed conversion using brain::any_cast";
            }
    };

    
    /// Cast the any pointer
    /// to pointer of type_t
    template<typename type_t>
    type_t* any_cast(any* operand)
    {
        return operand and operand->type() == typeid(type_t) ?
               std::addressof(static_cast<any::holder<std::remove_cv_t<type_t>> *>(operand->content())->held())
               : nullptr;
    }


    /// Cast the const any
    /// pointer to pointer
    /// of type_t
    template<typename type_t>
    inline const type_t* any_cast(
        const any* operand)
    {
        return any_cast<type_t>(const_cast<any *>(operand));
    }


    /// Cast the ref any
    /// to type_t
    template<typename type_t>
    inline type_t any_cast(
        any & operand)
    {
        using nonref =
            std::remove_reference_t<type_t> ;


        nonref * result =
            any_cast<nonref>(&operand);

        if(result == nullptr)
            throw(bad_any_cast());


        using ref_type =
            meta::select_t <
            std::is_reference<type_t>,
            type_t,
            std::add_lvalue_reference_t<type_t >>;

        return static_cast<ref_type>(*result);
    }


    /// Cast the const ref
    /// any to type_t
    template<typename type_t>
    inline type_t any_cast(
        const any & operand)
    {
        using nonref =
            std::remove_reference_t<type_t>;

        return any_cast<const nonref &>(
                   const_cast<any &>(operand));
    }


    /// Cast the rvalue any
    /// to type_t
    template<typename type_t>
    inline type_t any_cast(any && operand)
    {
        static_assert(
            meta::v_<std::is_rvalue_reference<type_t &&>>
            || meta::v_<std::is_const<std::remove_reference_t<type_t>>>,
            "boost::any_cast shall not be used for getting nonconst references to temporary objects"
        );
        return any_cast<type_t>(operand);
    }
}



#endif
