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
            class placeholder;

            template<typename type_t>
            class holder;

        private:
            property<placeholder*> content;
            
            template<typename type_t>
            friend type_t * any_cast(any *);

        public:
            any() = default;


            template<typename type_t>
            any(
                const type_t & value):
                content {new holder<type_t> {value}}
            {
            }


            any(
                const any & other):
                content(other.content() ?
                        other.content()->clone() :
                        nullptr)
            {
            }


            any(any && other) :
                content {other.content()}
            {
                other.content(nullptr);
            }

            /*
             * , typename boost::disable_if<boost::is_same<any&, type_t> >::type* = 0 // disable if value has type `any&`
                        , typename boost::disable_if<boost::is_const<type_t> >::type* = 0) // disable if value has type `const type_t&&`
             */
            // Perfect forwarding of type_t
            template<typename type_t>
            any(type_t && value):
                content(new holder<meta::t_<std::decay<type_t>>>(static_cast < type_t && >(value)))
            {
            }

        public:
            any & operator=(
                const any&) = default;

            // move assignement
            any & operator=(
                any && other)
            {
                if(this != &other)
                {
                    content(other.content());
                    other.content(nullptr);
                }

                return *this;
            }

        public: // queries

            bool empty() const
            {
                return content() != nullptr;
            }

            void clear()
            {
                delete content();
                content(nullptr);
            }

            const std::type_info& type() const
            {
                return empty() ?
                       content()->type() :
                       typeid(void);
            }


        public:

            class placeholder
            {
                public:
                    virtual ~placeholder() = default;

                public:
                    virtual const std::type_info & type() const = 0;
                    virtual placeholder * clone() const = 0;
            };

            template<typename type_t>
            class holder :
                public placeholder
            {
                public:
                    property<type_t> held;


                public:
                    holder(
                        const type_t & value)
                        : held(value)
                    {
                    }


                    holder(
                        type_t && value)
                        : held(static_cast < type_t && >(value))
                    {
                    }

                public:
                    holder & operator=(
                        const holder &) = delete;

                public:

                    virtual const std::type_info & type() const
                    {
                        return typeid(type_t);
                    }

                    virtual placeholder * clone() const
                    {
                        return new holder(held());

                    }
            };

            

    };

    class bad_any_cast :
        public std::exception
    {
        public:
            virtual const char * what() const noexcept
            {
                return "boost::bad_any_cast: "
                       "failed conversion using boost::any_cast";
            }
    };


    template<typename type_t>
    type_t* any_cast(any* operand)
    {
        return operand and operand->type() == typeid(type_t) ?
               std::addressof(static_cast<any::holder<std::remove_cv_t<type_t>> *>(operand->content())->held())
               : nullptr;
    }

    template<typename type_t>
    inline const type_t* any_cast(
        const any* operand)
    {
        return any_cast<type_t>(const_cast<any *>(operand));
    }

    template<typename type_t>
    type_t any_cast(
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

    template<typename type_t>
    inline type_t any_cast(
        const any & operand)
    {
        using nonref =
            std::remove_reference_t<type_t>;

        return any_cast<const nonref &>(
                   const_cast<any &>(operand));
    }


    template<typename type_t>
    inline type_t any_cast(any && operand)
    {
        static_assert(
            std::is_rvalue_reference < type_t && >::value /*true if type_t is rvalue or just a value*/
            || std::is_const< typename std::remove_reference<type_t>::type >::value,
            "boost::any_cast shall not be used for getting nonconst references to temporary objects"
        );
        return any_cast<type_t>(operand);
    }

}



#endif
