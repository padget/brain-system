#ifndef __SERIALIZE_BRAIN_HPP__
#define __SERIALIZE_BRAIN_HPP__

#include "property.hpp"
#include <string>
#include <sstream>
#include "meta.hpp"

namespace brain
{

    template<typename char_t>
    struct format;


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
                        return value().empty();
                    }


                    /// Returns true if
                    /// value() is not empty
                    auto has_name()
                    {
                        return name().empty();
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
                        const std::basic_string<char_t>& _value):
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
                serializerstream & (*flag)(serializerstream&))
            {
                return flag(*this);
            }


            /// Add an attribute
            /// into the attributes list
            serializerstream& operator <<(
                const attribute& attr)
            {
                attr.depth(current_depth());
                attributes.push_back(attr);

                return *this;
            }


            /// Add an attribute
            /// into the attributes list
            serializerstream& operator <<(
                attribute && attr)
            {
                attr.depth(current_depth());
                attributes().push_back(attr);

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
            virtual std::basic_string<char_t> transform(
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
            virtual content transform(
                const serializerstream<char_t>& ss) const
            {
                content_builder builder;

                std::stack<std::basic_string<char_t>> parents;

                const auto& attrs =
                    ss.attributes();

                for(auto it = std::begin(attrs),
                        end = std::end(attrs);
                        it != end;
                        it++)
                {

                    builder << this->indent(' ', 4u * (*it).depth())
                            << '<' << (*it).name() << '>' ;
                    auto next =
                        std::next(it);


                    /// If the next element
                    /// has a greater depth
                    /// then a NL is added
                    /// in the builder and
                    /// the current name
                    /// is pushed into the
                    /// parents stack
                    if(next != end and
                            (*next).depth() < (*it).depth())
                    {
                        parents.push((*it).name());
                        builder << '\n' ;
                    }

                    /// Else if the next
                    /// element has less
                    /// depth, then the
                    /// the
                    else if(next != end and
                            (*next).depth() > (*it).depth())
                    {
                        builder << (*it).value()
                                << '<' << '/' << (*it).name() << '>'
                                << '\n'
                                << this->indent(' ', 4 * ((*it).depth() - 1))
                                << '<' << '/' << parents.top() << '>'
                                << '\n';
                        parents.pop();
                    }

                    else
                        builder << (*it).value()
                                << '<' << '/' << (*it).name() << '>'
                                << '\n';
                }

                return builder.str();
            }
    };
}

#endif
