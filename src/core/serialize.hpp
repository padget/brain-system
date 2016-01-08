#ifndef __SERIALIZE_BRAIN_HPP__
#define __SERIALIZE_BRAIN_HPP__

#include "property.hpp"
#include <string>
#include <sstream>
#include <stack>
#include "meta.hpp"

namespace brain
{
    namespace serialize
    {
        template<typename char_t>
        struct format;

        template<typename char_t>
        struct injector;

        template<typename char_t>
        struct stream;


        /// Class to implements to
        /// be compatible with
        /// serialization library
        template<typename char_t>
        class serializable
        {
            public:
                /// Overload this method
                /// to specify the way
                /// to serialize the
                /// current object
                virtual void serialize(
                    stream<char_t>& out) const = 0;
        };


        /// Returns true_type
        /// if type_t inherits
        /// from serializable
        template < typename char_t,
                 typename type_t >
        using is_serializable_t =
            meta::lazy_t < std::is_base_of,
            serializable<char_t>, type_t >;


        /// /////////////////// ///
        /// Injector for Stream ///
        /// /////////////////// ///


        /// Basic injector for
        /// stream
        template<typename char_t>
        struct injector
        {
            /// Overload this method
            /// to operate some
            /// alterations on stream
            virtual stream<char_t>& operator()(
                stream<char_t>& out) = 0;
        };



        struct serializable_state
        {
            template<typename type_t>
            using state = void;
            /// meta::if_t<type_t, meta::is_iterable_t>;
        };


        template<typename char_t>
        struct member:
            public injector<char_t>
        {
            property<stream<char_t>> ss;

            template < typename type_t,
                     typename state_t >
            struct inner;











            virtual stream<char_t>& operator()(
                stream<char_t>& out)
            {
                return out;
            };
        };



        /// Injector that can
        /// transform basic
        /// types (int, char, ...)
        /// into the right inner
        /// type for the stream
        template<typename char_t>
        struct fundamental final:
            public injector<char_t>
        {
            /// Embedded stream
            property<stream<char_t>> ss;


            /// Component name
            property<std::basic_string<char_t>> comp_name;


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
                    typename stream<char_t>::attribute;

                ss() << attribute(name, ob);
            }


            ///
            virtual stream<char_t>& operator()(
                stream<char_t>& out)
            {
                /// Composition => depth++
                out.current_depth()++;

                auto& attrs =
                    ss().attributes();

                /// Align the depth with
                /// the out current_deph
                std::for_each(std::begin(attrs),
                              std::end(attrs),
                              [&out](auto & attr)
                {
                    attr.depth(attr.depth() +
                               out.current_depth());
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
                out.attributes().insert(
                    std::end(out.attributes()),
                    std::begin(ss().attributes()),
                    std::end(ss().attributes()));

                /// Composition => depth--
                out.current_depth()--;

                return out;
            }
        };


        /// Injector that can
        /// transform complex
        /// types (vector, toto, ...)
        /// into the right inner
        /// type for the stream
        template<typename char_t>
        struct complex final:
            public injector<char_t>
        {
            /// Embedded Serializerstream
            property<stream<char_t>> ss;


            /// Component name
            property<std::basic_string<char_t>> comp_name;


            /// Constructor that inject
            /// ob of type_t into the
            /// embedded serializer stream
            template <typename type_t>
            complex(
                const std::basic_string<char_t>& name,
                const type_t& ob):
                comp_name(name)
            {
                ob.serialize(ss());
            }


            /// For a complex type,
            /// inject them into
            /// the stream
            virtual stream<char_t>& operator()(
                stream<char_t>& out)
            {
                /// Composition => depth++
                out.current_depth()++;

                auto& attrs =
                    ss().attributes();

                /// Align the depth with
                /// the out current_deph
                std::for_each(std::begin(attrs),
                              std::end(attrs),
                              [&out](auto & attr)
                {
                    attr.depth(attr.depth()
                               + out.current_depth());
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
                out.attributes().insert(
                    std::end(out.attributes()),
                    std::begin(ss().attributes()),
                    std::end(ss().attributes()));

                /// Composition => depth--
                out.current_depth()--;

                return out;
            }
        };


        /// Injector that can
        /// transforms the parent
        /// data and replace the
        /// name of the parent
        /// by the name of the
        /// current class
        template < typename char_t,
                 typename parent_t >
        struct parent final:
            public injector<char_t>
        {

            /// Embedded stream
            property<stream<char_t>> ss;

            /// Constructor that takes an
            /// object of type_t and
            /// inject them into the
            /// stream ss of this flag
            template<typename type_t>
            parent(
                const type_t& ob)
            {
                /// Using the serialize
                /// methode of the parent
                static_cast<const parent_t>(ob).serialize(ss());
            }


            /// Suppress the first
            /// element of the list
            /// if exists and has only
            /// a name
            virtual stream<char_t>& operator()(
                stream<char_t>& out)
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


                /// Align the depth with
                /// the out current_deph
                std::for_each(std::begin(attrs),
                              std::end(attrs),
                              [&out](auto & attr)
                {
                    attr.depth(attr.depth() +
                               out.current_depth());
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
                out.attributes().insert(
                    std::end(out.attributes()),
                    std::begin(ss().attributes()),
                    std::end(ss().attributes()));

                return out;
            }
        };



        template <typename char_t>
        struct iterable final:
                injector<char_t>
        {
            template < typename citerator_t,
                     typename = is_serializable_t<char_t, meta::vt_<std::iterator_traits<citerator_t>> >>
            struct iterable_process;

            template<typename citerator_t>
            struct iterable_process <
                    citerator_t,
                    std::true_type >
            {
                void operator()(
                    stream<char_t>& ss,
                    const std::basic_string<char_t>& name,
                    const citerator_t& cbegin,
                    const citerator_t& cend)
                {
                    ss << name;
                    ss.current_depth()++;

                    std::for_each(cbegin, cend,
                                  [&ss](const auto & ob)
                    { ob.serialize(ss); });

                    ss.current_depth()--;
                }
            };

            template<typename citerator_t>
            struct iterable_process <
                    citerator_t,
                    std::false_type >
            {
                void operator()(
                    stream<char_t>& ss,
                    const std::basic_string<char_t>& name,
                    const citerator_t& cbegin,
                    const citerator_t& cend)
                {
                    ss << name;
                    ss.current_depth()++;

                    std::for_each(cbegin, cend,
                                  [&ss](const auto & ob)
                    { ss << stream<char_t>::attribute(); });

                    ss.current_depth()--;
                }
            };


            /// Embedded stream
            property<stream<char_t>> ss;

            template<typename citerator_t>
            iterable(
                const std::basic_string<char_t>& name,
                const citerator_t& cbegin,
                const citerator_t& cend)
            {
                iterable_process<citerator_t>()(ss(), name, cbegin, cend);
            }


            virtual stream<char_t>& operator()(
                stream<char_t>& out)
            {
                /// Composition => depth++
                out.current_depth()++;

                auto& attrs =
                    ss().attributes();

                // If the list is not
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

                /// Composition => depth--
                out.current_depth()--;

                return out;
            }
        };


        /// ////////////////////// ///
        /// Final format of stream ///
        /// ////////////////////// ///


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
                    const stream<char_t>& ss) const
                {
                    return std::basic_string<char_t>();
                }


                /// Shortcut for
                /// transform method
                inline auto operator()(
                    const stream<char_t>& ss)
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
                /// of any serializable
                /// class
                template<typename type_t>
                inline auto operator()(
                    const type_t& ob)
                {
                    stream<char_t> ss;
                    ob.serialize(ss);
                    return (*this)(ss);
                }
        };


        /// XML format that
        /// transforms an
        /// obejct or stream
        /// into XML
        template <typename char_t>
        class xml_format final :
            public format<char_t>
        {
                using content =
                    std::basic_string<char_t>;


                using content_builder =
                    std::basic_ostringstream<char_t>;


            public:
                /// Overload that
                /// implements an
                /// xml translation
                virtual inline content transform(
                    const stream<char_t>& ss) const
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


        /// JSON format that
        /// transforms an
        /// obejct or stream
        /// into JSON
        template <typename char_t>
        class json_format final :
            public format<char_t>
        {
                using content =
                    std::basic_string<char_t>;


                using content_builder =
                    std::basic_ostringstream<char_t>;


            public:
                /// Overload that
                /// implements an
                /// xml translation
                virtual inline content transform(
                    const stream<char_t>& ss) const
                {
                    content_builder builder;

                    using parent =
                        unsigned;

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
                            parents.push((*it).depth());
                            builder << this->indent(' ', 4 * (*it).depth())
                                    << (*it).name()
                                    << ':' << ' ' << '{' << '\n';
                        }

                        /// Else open/close balises
                        /// with inner value is
                        /// inserted into the builder :
                        /// <open>value</open>\n
                        else
                            builder << this->indent(' ', 4 * (*it).depth())

                                    << (*it).name()
                                    << ':' << ' '
                                    << (*it).value()
                                    << '\n' ;

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
                                    parents.top() >= (*next).depth())
                            {
                                builder << this->indent(' ', 4 * ((*it).depth() - 1))
                                        << '}' << '\n';
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
                                    << '}' << '\n';
                            parents.pop();
                        }
                    }

                    return builder.str();
                }
        };


        /// LQL format that
        /// transforms an
        /// object or stream
        /// into LQL
        template <typename char_t>
        class lql_format final :
            public format<char_t>
        {
                using content =
                    std::basic_string<char_t>;


                using content_builder =
                    std::basic_ostringstream<char_t>;


            public:
                /// Overload that
                /// implements an
                /// xml translation
                virtual inline content transform(
                    const stream<char_t>& ss) const
                {
                    content_builder builder;

                    using parent =
                        unsigned;

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
                        auto& next =
                            std::next(it);

                        /// If the current value is
                        /// empty, then a simple
                        /// open balise is inserted :
                        /// <open>\n
                        if((*it).value().empty())
                        {
                            parents.push((*it).depth());
                            builder << this->indent(' ', 4 * (*it).depth())
                                    << '('
                                    << (*it).name()
                                    << '\n';
                        }

                        /// Else open/close balises
                        /// with inner value is
                        /// inserted into the builder :
                        /// <open>value</open>\n
                        else
                            builder << this->indent(' ', 4 * (*it).depth())
                                    << '('
                                    << (*it).name()
                                    <<  ' '
                                    << (*it).value()
                                    << ')' << '\n' ;

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
                                    parents.top() >= (*next).depth())
                            {
                                builder << this->indent(' ',
                                                        4 * ((*it).depth() - 1))
                                        << ')' << '\n';
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
                                    << '}' << '\n';
                            parents.pop();
                        }
                    }

                    return builder.str();
                }
        };


        /// //////////////// ///
        /// Temporary stream ///
        /// //////////////// ///


        /// A serialization stream
        /// is a stream that can
        /// be configure to absorbs
        /// correctly data and to
        /// translate it into string
        /// readable data in order
        /// finally serialize them
        template<typename char_t>
        struct stream final
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
                        property<unsigned> depth {0};


                        /// Name of the attribute
                        property<std::basic_string<char_t>> name;


                        /// Value of the attribute
                        property<std::basic_string<char_t>> value;


                        /// Returns true if
                        /// name() is not empty
                        auto has_value() const
                        {
                            return !value().empty();
                        }


                        /// Returns true if
                        /// value() is not empty
                        auto has_name() const
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
                property<unsigned> current_depth {0};


                /// List of all attributes
                /// injected in the stream
                property<std::list<attribute>> attributes;


                /// Operator << to alter
                /// the behaviour of the
                /// serialization stream
                stream& operator <<(
                    injector<char_t> && flag)
                {
                    return flag(*this);
                }


                /// Add an attribute
                /// into the attributes list
                stream& operator <<(
                    const std::basic_string<char_t>& _name)
                {
                    attribute attr {_name};
                    attr.depth(current_depth());
                    attributes().push_back(attr);
                    return *this;
                }


                /// Add an attribute
                /// into the attributes list
                stream& operator <<(
                    const attribute& attr)
                {
                    attr.depth(current_depth());
                    attributes().push_back(attr);
                    return *this;
                }


                /// Add an attribute
                /// into the attributes list
                stream& operator <<(
                    attribute && attr)
                {
                    attr.depth(current_depth());
                    attributes().push_back(attr);
                    return *this;
                }


                ///
                stream& operator<< (
                    const serializable<char_t>& ob)
                {
                    ob.serialize(*this);
                    return *this;
                }
        };
    }


    /// General marshalling
    /// function of the
    /// serialization API
    template < typename char_t,
             template<typename> typename format_t,
             typename type_t >
    std::basic_string<char_t> marshall(
        const type_t& ob)
    {
        return format_t<char_t>()(ob);
    }
}

#endif
