#ifndef SUPPORTS_HPP_INCLUDED
#define SUPPORTS_HPP_INCLUDED

#include "../core.h"

class regex_match;
namespace brain
{
    namespace cpl
    {
        /// ///////////// ///
        /// Data supports ///
        /// ///////////// ///


        /// Alias for bullshit
        /// value of enum_t
        template<typename enum_t>
        constexpr enum_t bullshit_ =
            enum_t::bullshit;


        /// Alias for ignored
        /// value of enum_t
        template<typename enum_t>
        constexpr enum_t ignored_ =
            enum_t::ignored;


        /// Alias for empty
        /// value of enum_t
        template<typename enum_t>
        constexpr enum_t empty_ =
            enum_t::empty;


        /// A token is an
        /// object that contains
        /// the result of the
        /// source scanning.
        template < typename enum_t,
                 typename char_t >
        class token:
            object
        {
            public:
                /// Alias for
                /// enum_t
                using enum_type =
                    enum_t;


                /// Alias for
                /// char_t
                using char_type =
                    char_t;

            public:
                /// Id of the token.
                /// Defaulted initialized
                /// with enum_<config_t>::ignored
                property<enum_t> symbol_id {enum_t::ignored};


                /// The intrinsec value
                /// in the source
                property<std::basic_string<char_t>> value;


            public:
                /// Default constructor
                token() = default;


                /// Constructor by giving
                /// of an id and the value
                /// of the token
                token(
                    enum_t _id,
                    const std::basic_string<char_t>& v =
                        std::basic_string<char_t>()):
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
                    return symbol_id() !=  bullshit_<enum_t>;
                }
        };


        /// Node is a translation
        /// of tokens into a tree
        /// given that a grammar
        template < typename enum_t,
                 typename char_t >
        class node:
            public token<enum_t, char_t>
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
                    const enum_t _id,
                    const std::basic_string<char_t>& _value =
                        std::basic_string<char_t>()):
                    token<enum_t, char_t>(_id, _value)
                {
                }


                /// Constructor by id
                /// and childs
                node(
                    enum_t _id,
                    std::initializer_list<node> && _childs):
                    token<enum_t, char_t>(_id),
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


        /// ///////////////// ///
        /// API Configuration ///
        /// ///////////////// ///


        /// A config conditions
        /// all compilation
        template < typename enum_t,
                 typename char_t,
                 template<typename, typename> typename token_t = token,
                 template<typename, typename> typename node_t = node >
        struct config
        {
            /// Alias for
            /// enum_<config_t>
            using enum_type =
                enum_t;


            /// Alias for char_t
            using char_type =
                char_t;


            /// Alias for token_t
            using token_type =
                token_t<enum_t, char_t>;


            /// Alias for
            /// std::vector<token_t>
            using tokens_type =
                std::vector<token_type>;


            /// Alias for node_t
            using node_type =
                node_t<enum_t, char_t>;
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


        /// Alias for member
        /// node_type
        template<typename type_t>
        using node_ =
            typename type_t::node_type;


        /// Alias for member
        /// token_type
        template<typename type_t>
        using token_ =
            typename type_t::token_type;


        /// Alias for member
        /// tokens_type
        template<typename type_t>
        using tokens_ =
            typename type_t::tokens_type;


        /// id_ operator
        /// to recover the
        /// id member of the
        /// id_t type
        template<typename id_t>
        constexpr enum_<config_<id_t>> id_ =
                                        id_t::symbol_id;


        /// Returns false_type
        /// because no enum_type
        /// member in type_t
        template < typename,
                 typename = void >
        struct has_config_type_t_
        {
            using type =
                std::false_type;
        };


        /// Returns true_type
        /// because of enum_type
        /// member in type_t
        template<typename type_t>
        struct has_config_type_t_ < type_t,
                meta::void_r<typename type_t::config_type >>
        {
            using type =
                std::true_type;
        };


        /// Evaluates the result of
        /// defer_t<has_config_type_t_, type_t>
        template<typename type_t>
        using has_config_type_t =
            meta::defer_t<has_config_type_t_, type_t>;


        /// ////////////////// ///
        /// Grammar definition ///
        /// ////////////////// ///

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
        struct symbol
        {
            using config_type =
                config_t;
            static constexpr enum_<config_t> symbol_id {_id};
            /// Static boolean
            /// that identifies
            /// if the symbol is
            /// a terminal symbol
            /// or not.
            static constexpr bool is_terminal {b_is_terminal};
        };


        /// Static initialisation
        /// of symbol_id member
        template < typename config_t,
                 enum_<config_t> _id,
                 bool b_is_terminal >
        constexpr enum_<config_t> symbol<config_t, _id, b_is_terminal>::symbol_id;


        /// Static initialization
        /// of the is_terminal
        /// member of symbol
        /// template
        template < typename config_t,
                 enum_<config_t> _id,
                 bool b_is_terminal >
        constexpr bool symbol<config_t, _id, b_is_terminal>::is_terminal;


        template<typename type_t>
        struct is_terminal_t_
        {
            using type = meta::if_t < meta::bool_t<true>,
                  std::true_type,
                  std::false_type >;
        };


        /// Return true_type
        /// if the symbol_t is
        /// marked as a terminal
        template<typename symbol_t>
        using is_terminal_t =
            meta::bool_t<symbol_t::is_terminal>;


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
        { terminal<config_t, _id, _regex>::regex.get() };


        /// Operator that
        /// determines if
        /// the symbols is
        /// empty
        template < typename symbol_t,
                 typename config_t >
        using is_empty =
            meta::bool_t<id_<symbol_t> == empty_<enum_<config_t>>>;


        /// Operator that
        /// determines if
        /// the symbols is
        /// empty
        template < typename symbol_t,
                 typename config_t >
        using is_bullshit =
            meta::bool_t<id_<symbol_t> == bullshit_<enum_<config_t>>>;


        /// Operator that
        /// determines if
        /// the symbols is
        /// empty
        template < typename symbol_t,
                 typename config_t >
        using is_ignored =
            meta::bool_t<id_<symbol_t> == ignored_<enum_<config_t>>>;


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
            UNDEFINED, /// Type undefined
            AND = '&', /// Sequence of symbols
            OR = '|', /// One of the symbols
            LIST = 'o' /// Loop of a sequence symbol
        };


        /// Alias for member
        /// production_type
        template<typename production_t>
        constexpr production_type prtype_ =
            production_t::prtype;


        /// Returns true_type
        /// if type_t is AND
        /// production
        template<typename type_t>
        using is_and_production_t =
            meta::bool_t < prtype_<type_t>
            == production_type::AND >;


        /// Returns true_type
        /// if type_t is OR
        /// production
        template<typename type_t>
        using is_or_production_t =
            meta::bool_t < prtype_<type_t>
            == production_type::OR >;


        /// Returns true_type
        /// if type_t is LIST
        /// production
        template<typename type_t>
        using is_list_production_t =
            meta::bool_t < prtype_<type_t>
            == production_type::LIST >;


        /// Definition of
        /// production. A production
        /// represent a rule for
        /// a grammar. It has a type,
        /// a symbol that is defined
        /// by the production and
        /// a list of symbols that
        /// defines the production
        template < production_type _type,
                 typename symbol_t,
                 typename ... symbols_t >
        struct production
        {
            static constexpr enum_<config_<symbol_t>> symbol_id {id_<symbol_t>};

            /// Alias for
            /// config_t
            using config_type =
                config_<symbol_t>;


            /// Static type of
            /// a production
            static constexpr production_type prtype {_type};


            /// Symbol that is
            /// defined by this
            /// production
            using symbol_type =
                symbol_t;


            /// List of symbols
            /// that defines the
            /// production
            using symbols_type =
                meta::list<symbols_t...>;
        };


        /// Static initialisation
        template < production_type _type,
                 typename symbol_t,
                 typename ... symbols_t >
        constexpr  enum_<config_<symbol_t>>
                                         production<_type, symbol_t, symbols_t...>::symbol_id;


        /// Static initialization
        /// member type
        template < production_type _type,
                 typename symbol_t,
                 typename ... symbols_t >
        constexpr production_type
        production<_type, symbol_t, symbols_t...>::prtype;


        /// Returns std::false_type
        /// if type_t::symbol_type
        /// doesn't exist
        template < typename type_t,
                 typename = void >
        struct has_symbol_type_t_
        {
            using type =
                std::false_type;
        };


        /// Returns std::true_type
        /// if type_t::symbol_type
        /// exists
        template<typename type_t>
        struct has_symbol_type_t_ < type_t,
                meta::void_r<typename type_t::symbol_type >>
        {
            using type =
                std::true_type;
        };


        /// Evaluates the result of
        /// t_<has_symbol_type_t_, type_t>
        template<typename type_t>
        using has_symbol_type_t =
            meta::defer_t<has_symbol_type_t_, type_t>;


        /// Returns std::false_type
        /// if type_t::symbols_type
        /// doesn't exist
        template < typename type_t,
                 typename = void >
        struct has_symbols_type_t_
        {
            using type =
                std::false_type;
        };


        /// Returns std::true_type
        /// if type_t::symbols_type
        /// exists
        template<typename type_t>
        struct has_symbols_type_t_ < type_t,
                meta::void_r<typename type_t::symbols_type >>
        {
            using type =
                std::true_type;
        };


        /// Evaluates the result of
        /// t_<has_symbols_type_t_, type_t>
        template<typename type_t>
        using has_symbols_type_t =
            meta::defer_t<has_symbols_type_t_, type_t>;


        /// Returns true_type
        /// if the type_t is
        /// recognized as a
        /// production
        template<typename type_t>
        using is_production_t =
            meta::bool_t < meta::v_<has_config_type_t<type_t>>
            and meta::v_<has_symbol_type_t<type_t>>
            and meta::v_<has_symbols_type_t<type_t>> >;


        /// Alias for member
        /// root_production_type
        template<typename grammar_t>
        using root_ =
            typename grammar_t::root_production_type;


        /// Alias for member
        /// productions_list
        template<typename grammar_t>
        using productions_ =
            typename grammar_t::productions_list;


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

            static_assert(meta::v_<is_production_t<root_production_type>>,
                          "grammar : root_production_type must be a production");
            static_assert(meta::v_<meta::and_t<is_production_t<production_t>...>>,
                          "grammar : all production_t... must be a production");
        };


        /// Factory that can
        /// initiate object like
        /// node or token
        template <typename type_t>
        struct factory:
            public pattag::factory
        {
            /// Transfers an id
            /// and a value to res
            inline static void make(
                type_t& res,
                enum_<type_t> _id,
                const std::basic_string<char_<type_t>>& value =
                    std::basic_string<char_<type_t>> {})
            {
                res.symbol_id(std::move(_id));
                res.value(std::move(value));
            }


            /// Transfers an id
            /// and a value and
            /// childs to res
            inline static void make(
                type_t& res,
                enum_<type_t> _id,
                std::initializer_list<type_t> && childs,
                const std::basic_string<char_<type_t>>& value =
                    std::basic_string<char_<type_t>> {})
            {
                factory::make(res, _id, value);
                res.childs(childs);
            }


            /// Build a bullshit
            /// node
            inline static void make_bullshit(
                node<enum_<type_t>, char_<type_t>>& res)
            {
                factory::make(res,
                              bullshit_<enum_<type_t>>,
                              {});
            }


            /// Build a bullshit
            /// token
            inline static void make_bullshit(
                token<enum_<type_t>, char_<type_t>>& res)
            {
                factory::make(res,
                              bullshit_<enum_<type_t>>);
            }


            /// Build a ignored
            /// node
            inline static void make_ignored(
                node<enum_<type_t>, char_<type_t>>& res)
            {
                factory::make(res,
                              ignored_<enum_<type_t>>,
                              {});
            }


            /// Build a ignored
            /// token
            inline static void make_ignored(
                token<enum_<type_t>, char_<type_t>>& res)
            {
                factory::make(res,
                              ignored_<enum_<type_t>>);
            }


            /// Build a empty
            /// node
            inline static void make_empty(
                node<enum_<type_t>, char_<type_t>>& res)
            {
                factory::make(res,
                              empty_<enum_<type_t>>,
                              {});
            }


            /// Build a empty
            /// token
            inline static void make_empty(
                token<enum_<type_t>, char_<type_t>>& res)
            {
                factory::make(res,
                              empty_<enum_<type_t>>);
            }
        };
    }
}

#endif // SUPPORTS_HPP_INCLUDED2
