#ifndef SUPPORTS_HPP_INCLUDED
#define SUPPORTS_HPP_INCLUDED

#include "../core.h"

class regex_match;
namespace brain
{
    namespace cpl
    {
        /// A config conditions
        /// all compilation
        template < typename enum_t,
                 typename char_t >
        struct config
        {
            /// Alias for enum_<config_t>
            using enum_type =
                enum_t;


            /// Alias for char_t
            using char_type =
                char_t;
        };


        /// Alias that returns
        /// type_t::config_type
        template<typename type_t>
        using config_ =
            typename type_t::config_type;


        /// Alias that returns
        /// type_t::char_type
        template<typename type_t>
        using char_ =
            typename type_t::char_type;


        /// Alias that returns
        /// type_t::enum_type
        template<typename type_t>
        using enum_ =
            typename type_t::enum_type;


        /// An id_type is
        /// an object that
        /// has the id member
        template < typename config_t,
                 enum_<config_t> _id >
        struct id_type
        {
            /// Effective id
            /// of id_type
            static enum_<config_t> id;


            /// Alias for
            /// config_t
            using config_type =
                config_t;
        };


        /// Static declaration of
        /// id from id_type template
        template < typename config_t,
                 enum_<config_t> _id >
        enum_<config_t> id_type<config_t, _id>::id {_id};


        /// id_ operator
        /// to recover the
        /// id member of the
        /// id_t type
        template<typename id_t>
        auto id_ =
            id_t::id;


        /// A symbol represents
        /// a possible token for
        /// a grammar. This symbol
        /// has an identifier
        /// and can be terminal or
        /// not. Moreover, it has a
        /// target type that represent
        /// its type for an interpretor
        /// or a compiler.
        template < typename config_t, /// Type of the id
                 enum_<config_t> _id, /// Id of the symbol
                 bool b_is_terminal > /// True if the symbol is a terminal
        struct symbol:
            public id_type<config_t, _id>
        {
            /// Static boolean
            /// that identifies
            /// if the symbol is
            /// a terminal symbol
            /// or not.
            static constexpr bool is_terminal {b_is_terminal};
        };


        /// Static initialization
        /// of the is_terminal
        /// member of symbol
        /// template
        template < typename config_t,
                 enum_<config_t> _id,
                 bool b_is_terminal >
        constexpr bool symbol<config_t, _id, b_is_terminal>::is_terminal;


        /// A terminal is
        /// a symbol that
        /// has a regex and
        /// that is not defined
        /// by a production
        /// in a grammar
        template < typename config_t,
                 enum_<config_t> _id,
                 const meta::basic_string<char_<config_t>>& _regex >
        struct terminal :
            public symbol<config_t, _id, true>
        {
            /// Static char* that
            /// represent the containt
            /// of the regex
            static constexpr meta::basic_string<char_<config_t>> regex {_regex};


            /// Static standart regex
            static const std::basic_regex<char_<config_t>> regex_std;
        };


        /// Static initilisation
        /// of regex
        template < typename config_t,
                 enum_<config_t> _id,
                 const meta::basic_string<char_<config_t>>& _regex >
        constexpr meta::basic_string<char_<config_t>> terminal<config_t, _id, _regex>::regex;


        /// Static initialisation
        /// of regex_std
        template < typename config_t,
                 enum_<config_t> _id,
                 const meta::basic_string<char_<config_t>>& _regex >
        const std::basic_regex<char_<config_t>> terminal<config_t, _id, _regex>::regex_std
        {terminal<config_t, _id, _regex>::regex.get()};


        /// Operator that
        /// determines if
        /// the symbols is
        /// empty
        template < typename symbol_t,
                 typename config_t >
        using is_empty =
            meta::bool_t<id_<symbol_t> == enum_<config_t>::empty>;


        /// Operator that
        /// determines if
        /// the symbols is
        /// empty
        template < typename symbol_t,
                 typename config_t >
        using is_bullshit =
            meta::bool_t<id_<symbol_t> == enum_<config_t>::bullshit>;


        /// Operator that
        /// determines if
        /// the symbols is
        /// empty
        template < typename symbol_t,
                 typename config_t >
        using is_ignored =
            meta::bool_t<id_<symbol_t> == enum_<config_t>::ignored>;


        /// Non terminal
        /// definition
        template < typename config_t,
                 enum_<config_t> _id >
        struct non_terminal:
            public symbol<config_t, _id, false>
        {
        };


        /// Production type
        enum class production_type :
        char
        {
            AND = '&', /// Sequence of symbols
            OR = '|', /// One of the symbols
            LIST = 'o' /// Loop of a sequence symbol
        };


        /// Definition of
        /// production. A production
        /// represent a rule for
        /// a grammar. It has a type,
        /// a symbol that is defined
        /// by the production and
        /// a list of symbols that
        /// defines the production
        template < typename config_t,
                 production_type _type,
                 typename symbol_t,
                 typename ... symbols_t >
        struct production:
            public id_type<config_t, symbol_t::id>
        {
            /// Alias for
            /// config_t
            using config_type =
                config_t;


            /// Static type of
            /// a production
            static constexpr production_type type {_type};


            /// Symbol that is
            /// defined by this
            /// production
            using symbol_type =
                symbol_t;


            /// List of symbols
            /// that defines the
            /// production
            using symbols_list =
                meta::list<symbols_t...>;
        };


        /// Static initialization
        /// member type
        template < typename config_t,
                 production_type _type,
                 typename symbol_t,
                 typename ... symbols_t >
        constexpr production_type
        production<config_t, _type, symbol_t, symbols_t...>::type;


        /// Definition of a
        /// Grammar. A grammar
        /// has a root production
        /// and a list of other
        /// production that defines
        /// the containt of the
        /// former.
        template < typename config_t,
                 typename root_production_t,
                 typename ... production_t >
        struct grammar
        {
            /// Alias for
            /// config_t
            using config_type =
                config_t;


            /// Root production
            /// of the grammar
            using root_production_type =
                root_production_t;


            /// List of production
            /// that defines the
            /// grammar. The root
            /// must be contained
            /// in this list
            using productions_list =
                meta::list<production_t...>;
        };



        /// A token is an
        /// object that contains
        /// the result of the
        /// source scanning.
        template <typename config_t>
        class token:
            object
        {
            public:
                /// Alias for
                /// config_t
                using config_type =
                    config_t;


                /// Id of the token.
                /// Defaulted initialized
                /// with enum_<config_t>::ignored
                property<enum_<config_t>> symbol_id {enum_<config_t>::ignored};


                /// The intrinsec value
                /// in the source
                property<std::basic_string<char_<config_t>>> value;


            public:
                /// Default constructor
                token() = default;


                /// Constructor by giving
                /// of an id and the value
                /// of the token
                token(
                    enum_<config_t> _id,
                    const std::basic_string<char_<config_t>>& v =
                        std::basic_string<char_<config_t>>()):
                    object(),
                    symbol_id(_id),
                    value(v)
                {
                }


                /// Copy constructor
                token(
                    const token&) = default;


                /// Move constructor
                token(
                    token &&) = default;


                /// Default destructor
                virtual ~token() = default;


            public:
                /// default copy
                /// operator=
                token& operator=(
                    const token&) = default;


                /// default copy
                /// operator=
                token& operator=(
                    token &&) = default;


            public:
                /// Return true if
                /// the symbol_id is
                /// not equal to bullshit
                operator bool() const
                {
                    return symbol_id() !=  enum_<config_t>::bullshit;
                }
        };


        /// Builds a token given
        /// that an id and a
        /// value
        template <typename config_t>
        auto make_token(
            enum_<config_t> id,
            const std::basic_string<char_<config_t>>& value =
                std::basic_string<char_<config_t>>())
        {
            return token<config_t> {id, value};
        }


        /// Replaces the id and
        /// value of res by new
        /// value and id
        template <typename config_t>
        void make_token(
            token<config_t>& res,
            enum_<config_t> id,
            const std::basic_string<char_<config_t>>& value =
                std::basic_string<char_<config_t>>())
        {
            res.symbol_id(std::move(id));
            res.value(std::move(value));
        }


        /// Node is a translation
        /// of tokens into a tree
        /// given that a grammar
        template <typename config_t>
        class node:
            public token<config_t>
        {
            public:
                /// List of childs
                /// in a tree structure
                property<std::vector<node>> childs;

            public:
                /// Default constructor
                node() = default;


                /// Constructor by
                /// id and value
                node(
                    const enum_<config_t>& _id,
                    const std::basic_string<char_<config_t>>& _value =
                        std::basic_string<char_<config_t>>()):
                    token<config_t>(_id, _value)
                {
                }


                /// Constructor by id
                /// and childs
                node(
                    const enum_<config_t>& _id,
                    std::initializer_list<node> && _childs):
                    token<config_t>(_id),
                    childs(_childs)
                {
                }


                /// Move constructor
                node(
                    node &&) = default;


                /// Copy constructor
                node(
                    const node&) = default;


                /// Default destructor
                virtual ~node() = default;


            public:
                /// Default move
                /// operator=
                node& operator=(
                    node &&) = default;


                /// Default copy
                /// operator=
                node& operator=(
                    const node&) = default;
        };
    }
}

#endif // SUPPORTS_HPP_INCLUDED2
