#ifndef __SERIALIZE_BRAIN_HPP__
#define __SERIALIZE_BRAIN_HPP__

#include "property.hpp"
#include <string>
#include <sstream>
#include <stack>
#include "meta.hpp"

namespace brain
{

    template<typename char_t>
    struct format;

    template<typename char_t>
    struct serializerflag;

    /// A serialization stream
    /// is a stream that can
    /// be configure to absorbs
    /// correctly data and to
    /// translate it into string
    /// readable data in order
    /// finally serialize them
    template<typename char_t>
    struct serializerstream final
    {
            /// An attribute is
            /// the main support
            /// of the data for
            /// a serialization
            /// stream
            class attribute final
            {
                public:
                    /// Depth of the attribute
                    /// in the object tree
                    monomorphe<unsigned> depth {0};


                    /// Name of the attribute
                    monomorphe<std::basic_string<char_t>> name;


                    /// Value of the attribute
                    monomorphe<std::basic_string<char_t>> value;


                    /// Returns true if
                    /// name() is not empty
                    auto has_value()
                    {
                        return !value().empty();
                    }


                    /// Returns true if
                    /// value() is not empty
                    auto has_name()
                    {
                        return !name().empty();
                    }


                public:
                    /// Default empty
                    /// constructor
                    attribute() = default;


                    /// Basic constructor
                    /// that build directly
                    /// name and value with
                    /// the passed parameters
                    attribute(
                        const std::basic_string<char_t>& _name,
                        const std::basic_string<char_t>& _value =
                            std::basic_string<char_t> {}):
                        name(_name),
                        value(_value)
                    {
                    }


                    /// Generic attribute
                    /// constructor for
                    /// all fundamental
                    /// types
                    template < typename fundamental_t,
                             typename = std::is_fundamental<fundamental_t >>
                    attribute(
                        const std::basic_string<char_t>& _name,
                        const fundamental_t& _value):
                        name(_name)
                    {
                        /// Conversion of the
                        /// fundamental _value
                        /// into a string value
                        std::basic_stringstream<char_t> ss;
                        ss << _value;
                        value(ss.str());
                    }
            };


            /// Last depth used into
            /// the stream storing
            monomorphe<unsigned> current_depth {0};


            /// List of all attributes
            /// injected in the stream
            monomorphe<std::list<attribute>> attributes;


            /// Operator << to alter
            /// the behaviour of the
            /// serialization stream
            serializerstream& operator <<(
                serializerflag<char_t> && flag)
            {
                return flag(*this);
            }


            /// Add an attribute
            /// into the attributes list
            serializerstream& operator <<(
                const std::basic_string<char_t>& _name)
            {
                attribute attr {_name};
                attr.depth(current_depth());
                attributes().push_back(attr);

                return *this;
            }


            /// Add an attribute
            /// into the attributes list
            serializerstream& operator <<(
                const attribute& attr)
            {
                current_depth() ++;
                attr.depth(current_depth());
                attributes().push_back(attr);
                current_depth() --;
                return *this;
            }


            /// Add an attribute
            /// into the attributes list
            serializerstream& operator <<(
                attribute && attr)
            {
                current_depth() ++;
                attr.depth(current_depth());
                attributes().push_back(attr);
                current_depth() --;

                return *this;
            }
    };


    /// Flag to specify
    /// that the depth
    /// of the serializer
    /// stream must be
    /// incremented
    template<typename char_t>
    serializerstream<char_t>& attrsbegin(
        serializerstream<char_t>& ss)
    {
        ss.current_depth()++ ;
        return ss;
    }


    /// Flag to specify
    /// that the depth
    /// of the serializer
    /// stream must be
    /// decremented
    template<typename char_t>
    serializerstream<char_t>& attrsend(
        serializerstream<char_t>& ss)
    {
        ss.current_depth()-- ;
        return ss;
    }


    /// Basic flag for
    /// serializerstream
    template<typename char_t>
    struct serializerflag
    {
        virtual serializerstream<char_t>& operator()(
            serializerstream<char_t>& out) = 0;
    };


    ///
    template<typename char_t>
    struct fundamental final:
        public serializerflag<char_t>
    {
        /// Embedded Serializerstream
        monomorphe<serializerstream<char_t>> ss;


        /// Component name
        monomorphe<std::basic_string<char_t>> comp_name;


        /// Constructor that inject
        /// ob of type_t into the
        /// embedded serializer stream
        template < typename type_t,
                 typename = std::enable_if_t<std::is_fundamental<type_t>::value >>
        fundamental(
            const std::basic_string<char_t>& name,
            const type_t& ob):
            comp_name(name)
        {
            using attribute =
                typename serializerstream<char_t>::attribute;
            ss() << attribute(name, ob);
        }


        ///
        virtual serializerstream<char_t>& operator()(
            serializerstream<char_t>& out)
        {
            /// Composition => depth++
            out.current_depth() ++;

            auto& attrs =
                ss().attributes();

            /// Align the depth with
            /// the out current_deph
            std::for_each(std::begin(attrs),
                          std::end(attrs),
                          [&out](auto & attr)
            {
                attr.depth(attr.depth() + out.current_depth());
            });

            /// If the list is not
            /// empty and the first
            /// element has only a
            /// name, then this
            /// element is removed
            if(!attrs.empty() and
                    !attrs.front().has_value() and
                    attrs.front().has_name())
                attrs.front().name(comp_name());

            /// Add all elements from
            /// ss into out at the end.
            out.attributes().insert(std::end(out.attributes()),
                                    std::begin(ss().attributes()),
                                    std::end(ss().attributes()));

            out.current_depth() --;

            return out;
        }
    };



    ///
    template<typename char_t>
    struct composedof final:
        public serializerflag<char_t>
    {
        /// Embedded Serializerstream
        monomorphe<serializerstream<char_t>> ss;


        /// Component name
        monomorphe<std::basic_string<char_t>> comp_name;


        /// Constructor that inject
        /// ob of type_t into the
        /// embedded serializer stream
        template <typename type_t>
        composedof(
            const std::basic_string<char_t>& name,
            const type_t& ob):
            comp_name(name)
        {
            ss() << ob;
        }


        ///
        virtual serializerstream<char_t>& operator()(
            serializerstream<char_t>& out)
        {
            /// Composition => depth++
            out.current_depth() ++;

            auto& attrs =
                ss().attributes();

            /// Align the depth with
            /// the out current_deph
            std::for_each(std::begin(attrs),
                          std::end(attrs),
                          [&out](auto & attr)
            {
                attr.depth(attr.depth() + out.current_depth());
            });

            /// If the list is not
            /// empty and the first
            /// element has only a
            /// name, then this
            /// element is removed
            if(!attrs.empty() and
                    !attrs.front().has_value() and
                    attrs.front().has_name())
                attrs.front().name(comp_name());

            /// Add all elements from
            /// ss into out at the end.
            out.attributes().insert(std::end(out.attributes()),
                                    std::begin(ss().attributes()),
                                    std::end(ss().attributes()));

            out.current_depth() --;

            return out;
        }
    };


    /// Flag to signify that
    /// the current object is
    /// a part of parent class
    template < typename char_t,
             typename parent_t >
    struct fromparent final:
        public serializerflag<char_t>
    {

        /// Embedded Serializerstream
        monomorphe<serializerstream<char_t>> ss;

        /// Constructor that takes an
        /// object of type_t and
        /// inject them into the
        /// stream ss of this flag
        template <typename type_t>
        fromparent(
            const type_t& ob)
        {
            /// Use the operator
            /// << specifically
            /// implemented for type_t
            ss() << static_cast<const parent_t&>(ob);
        }


        /// Suppress the first
        /// element of the list
        /// if exists and has only
        /// a name
        virtual serializerstream<char_t>& operator()(
            serializerstream<char_t>& out)
        {
            auto& attrs =
                ss().attributes();


            /// Align the depth with
            /// the out current_deph
            std::for_each(std::begin(attrs),
                          std::end(attrs),
                          [&out](auto & attr)
            {
                attr.depth(attr.depth() + out.current_depth());
            });


            /// If the list is not
            /// empty and the first
            /// element has only a
            /// name, then this
            /// element is removed
            if(!attrs.empty() and
                    !attrs.front().has_value() and
                    attrs.front().has_name())
                attrs.pop_front();

            /// Add all elements from
            /// ss into out at the end.
            out.attributes().insert(std::end(out.attributes()),
                                    std::begin(ss().attributes()),
                                    std::end(ss().attributes()));
            return out;
        }
    };


    /// A Format is the
    /// way that an object
    /// data is transform
    /// to serialize an
    /// object
    template<typename char_t>
    class format
    {
        public:
            /// Overload this method
            /// in order to convert
            /// the content of the stream
            /// into an basic_string
            virtual inline std::basic_string<char_t> transform(
                const serializerstream<char_t>& ss) const
            {
                return std::basic_string<char_t>();
            }


            /// Shortcut for
            /// transform method
            inline auto operator()(
                const serializerstream<char_t>& ss)
            {
                return transform(ss);
            }


            /// Returns a string
            /// that represents
            /// an indentation
            auto indent(char_t c,
                        unsigned nb_char) const
            {
                return std::basic_string<char_t>(nb_char,
                                                 c);
            }


            /// Direct transformation
            /// of any class that supports
            /// the serializerstream
            /// operator <<
            template<typename type_t>
            inline auto operator()(
                const type_t& ob)
            {
                serializerstream<char_t> ss;
                return (*this)(ss << ob);
            }
    };


    template <typename char_t>
    class xml_format final :
        public format<char_t>
    {
            using content =
                std::basic_string<char_t>;


            using content_builder =
                std::basic_ostringstream<char_t>;

        public:
            /// Overload transform
            /// to implements an
            /// xml translation
            virtual inline content transform(
                const serializerstream<char_t>& ss) const
            {
                content_builder builder;

                using parent =
                    std::tuple<unsigned, std::basic_string<char_t>>;

                /// A stack to store
                /// the hierarchy of
                /// the current node
                std::stack<parent> parents;

                const auto& attrs =
                    ss.attributes();


                /// For each node of
                /// the list of the
                /// attributes
                for(auto it = std::begin(attrs),
                        end = std::end(attrs);
                        it != end;
                        it++)
                {
                    auto next =
                        std::next(it);

                    /// If the current value is
                    /// empty, then a simple
                    /// open balise is inserted :
                    /// <open>\n
                    if((*it).value().empty())
                    {
                        parents.push(parent((*it).depth(), (*it).name()));
                        builder << this->indent(' ', 4 * (*it).depth())
                                << '<'
                                << (*it).name()
                                << '>' << '\n';
                    }

                    /// Else open/close balises
                    /// with inner value is
                    /// inserted into the builder :
                    /// <open>value</open>\n
                    else
                        builder << this->indent(' ', 4 * (*it).depth())
                                << '<'
                                << (*it).name()
                                << '>'
                                << (*it).value()
                                << '<' << '/'
                                << (*it).name()
                                << '>' << '\n' ;

                    /// Finally, if there is
                    /// a change of depth in
                    /// upper direction, so
                    /// a close balise is
                    /// inserted with the
                    /// top parent name of
                    /// parents stack.
                    if(next != end and
                            (*next).depth() < (*it).depth() and
                            !parents.empty())
                    {
                        while(!parents.empty() and
                                std::get<0>(parents.top()) >= (*next).depth())
                        {
                            builder << this->indent(' ', 4 * ((*it).depth() - 1))
                                    << '<' << '/'
                                    << std::get<1>(parents.top())
                                    << '>' << '\n';
                            parents.pop();
                        }
                    }
                }

                /// If the stack of parents
                /// is not empty and if there
                /// were something in the attrs
                /// list, so we close each
                /// parent that is staying
                if(!parents.empty() and
                        !attrs.empty())
                {
                    auto last_depth =
                        attrs.back().depth();

                    while(!parents.empty())
                    {
                        last_depth--;
                        builder << this->indent(' ', 4 * last_depth)
                                << '<' << '/'
                                << std::get<1>(parents.top())
                                << '>' << '\n';
                        parents.pop();
                    }
                }

                return builder.str();
            }
    };
}

#endif
