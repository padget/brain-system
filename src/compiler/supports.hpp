#ifndef SUPPORTS_HPP_INCLUDED
#define SUPPORTS_HPP_INCLUDED

#include "../core.h"

class regex_match;
namespace brain
{
    namespace cpl
    {

        //--//--//--//--//--//--//--//--//--//--//
        //--//--//--//--//--//--//--//--//--//--//
        //--//--//--//--//--//--//--//--//--//--//

        template<typename target_t>
        struct target
        {
            using target_type =
                target_t;
        };


        ///
        template < typename id_t,
                 id_t _id >
        struct id_type
        {
            static id_t id;
        };

        template < typename id_t,
                 id_t _id >
        id_t id_type<id_t, _id>::id {_id};


        template<typename id_t>
        auto id_ =
            id_t::id;

        //--//--//--//--//--//--//--//--//--//--//
        //--//--//--//--//--//--//--//--//--//--//
        //--//--//--//--//--//--//--//--//--//--//

        /// A symbol represents
        /// a possible token for
        /// a grammar. This symbol
        /// has an identifier
        /// and can be terminal or
        /// not. Moreover, it has a
        /// target type that represent
        /// its type for an interpretor
        /// or a compiler.
        template < typename enum_t, /// Type of the id
                 enum_t _id, /// Id of the symbol
                 typename target_t, /// Target type of the symbol
                 bool b_is_terminal > /// True if the symbol is a terminal
        struct symbol:
            public id_type<enum_t, _id>,
            public target<target_t>
        {
            static constexpr bool is_terminal {b_is_terminal};
        };

        template < typename enum_t,
                 enum_t _id,
                 typename target_t,
                 bool b_is_terminal >
        constexpr bool symbol<enum_t, _id, target_t, b_is_terminal>::is_terminal;

        //--//--//--//--//--//--//--//--//--//--//
        //--//--//--//--//--//--//--//--//--//--//
        //--//--//--//--//--//--//--//--//--//--//

        struct indicative :
            public std::true_type
        {
        };

        struct non_indicative :
            public std::false_type
        {
        };

        template < typename enum_t,
                 enum_t _id,
                 const char* _regex,
                 typename indicative_t,
                 typename target_t = void >
        struct terminal :
            public symbol<enum_t, _id, target_t, true>
        {
            static constexpr const char* regex {_regex};
            static constexpr bool indicative {meta::v_<indicative_t>};
            static const std::regex regex_std;
        };

        template < typename enum_t,
                 enum_t _id,
                 const char* _regex,
                 typename indicative_t ,
                 typename target_t >
        constexpr const char* terminal<enum_t, _id, _regex, indicative_t, target_t>::regex;

        template < typename enum_t,
                 enum_t _id,
                 const char* _regex,
                 typename indicative_t ,
                 typename target_t >
        constexpr bool terminal<enum_t, _id, _regex, indicative_t, target_t>::indicative;

        template < typename enum_t,
                 enum_t _id,
                 const char* _regex,
                 typename indicative_t ,
                 typename target_t >
        const std::regex terminal<enum_t, _id, _regex, indicative_t, target_t>::regex_std
        {terminal<enum_t, _id, _regex, indicative_t, target_t>::regex};

        template < typename terminal_t,
                 typename enum_t >
        constexpr bool is_empty =
            terminal_t::id == enum_t::empty;

        template < typename terminal_t,
                 typename enum_t >
        constexpr bool is_bullshit =
            terminal_t::id == enum_t::bullshit;

        template < typename terminal_t,
                 typename enum_t >
        constexpr bool is_ignored =
            terminal_t::id == enum_t::ignored;

        //--//--//--//--//--//--//--//--//--//--//
        //--//--//--//--//--//--//--//--//--//--//
        //--//--//--//--//--//--//--//--//--//--//

        template < typename enum_t,
                 enum_t _id ,
                 typename target_t = void >
        struct non_terminal:
            public symbol<enum_t, _id, target_t, false>
        {
        };

        //--//--//--//--//--//--//--//--//--//--//
        //--//--//--//--//--//--//--//--//--//--//
        //--//--//--//--//--//--//--//--//--//--//

        enum class production_type :
        char
        {
            AND = '&',
            OR = '|',
            LIST = 'o'
        };

        template < typename enum_t,
                 production_type _type,
                 typename symbol_t,
                 typename ... symbols_t >
        struct production:
            public id_type<enum_t, symbol_t::id>
        {
            static constexpr production_type type {_type};

            using symbol_type =
                symbol_t;

            using symbols_list =
                meta::list<symbols_t...>;
        };

        template < typename enum_t,
                 production_type _type,
                 typename symbol_t,
                 typename ... symbols_t >
        constexpr production_type
        production<enum_t, _type, symbol_t, symbols_t...>::type;


        //--//--//--//--//--//--//--//--//--//--//
        //--//--//--//--//--//--//--//--//--//--//
        //--//--//--//--//--//--//--//--//--//--//

        template < typename enum_t,
                 typename root_production_t,
                 typename ... production_t >
        struct grammar
        {
            using enum_type =
                enum_t;

            using root_production_type =
                root_production_t;

            using productions_list =
                meta::list<production_t...>;
        };

        //--//--//--//--//--//--//--//--//--//--//
        //--//--//--//--//--//--//--//--//--//--//
        //--//--//--//--//--//--//--//--//--//--//

        /**
         * @class token
         * @author bmathieu
         * @date 17/09/2015
         * @file supports.hpp
         * @brief Token for scanning step
         */
        template<typename enum_t>
        class token:
            object
        {
                using token_def =
                    token<enum_t>;

            public:
                enum_t id =
                    enum_t::ignored;

                std::string value;

            public:
                token():
                    object()
                {
                }

                token(
                    enum_t _id,
                    const std::string& v = std::string()):
                    object(),
                    id(_id),
                    value(v)
                {
                }


                token(
                    const token_def& other):
                    object(other),
                    id(other.id),
                    value(other.value)
                {
                }


                token(
                    token_def && other):
                    object(other),
                    id(std::move(other.id)),
                    value(std::move(other.value))
                {
                }

                virtual ~token() = default;

            public:
                token_def& operator=(
                    const token_def& other)
                {
                    if(this != &other)
                    {
                        this->object::operator=(other);
                        id = other.id;
                        value = other.value;
                    }

                    return *this;
                }


                token_def& operator=(
                    token_def && other)
                {
                    if(this != &other)
                    {
                        this->object::operator=(other);
                        id = std::move(other.id);
                        value = std::move(other.value);
                    }

                    return *this;
                }

                operator bool() const
                {
                    return id !=  enum_t::bullshit;
                }
        };

        /**
         * @brief Build a token with an id and a value
         * @param id ID of the token in enum_t
         * @param value Value of the token from source
         * @return a token with id and value
         */
        template<typename enum_t>
        auto make_token(enum_t id,
                        const std::string& value)
        {
            return  token<enum_t> {id, value};
        }

        /**
         * @class node
         * @author bmathieu
         * @date 17/09/2015
         * @file supports.hpp
         * @brief Node for parsing step
         */
        template<typename enum_t>
        class node:
            public token<enum_t>
        {
                using token_def = token<enum_t>;

            public:
                //object_sptr m_object;
                std::vector<node> childs;

            public:
                node(): token_def()
                {
                }


                node(
                    const enum_t& _id):
                    token_def(_id)
                {
                }


                /*node(const enum_t& _id,
                     const std::string& v,
                     object_ptr && _object):
                    token_def(_id, v),
                    m_object(std::move(_object)) {}*/

                node(
                    const enum_t& _id,
                    const std::string& v):
                    token_def(_id, v) {}

                node(
                    const enum_t& _id,
                    std::initializer_list<node<enum_t>> && _childs):
                    token_def(_id),
                    childs(_childs) {}

                /*node(const enum_t& _id,
                     std::initializer_list<node<enum_t>> && _childs,
                     object_ptr && _object):
                    token_def(_id),
                    childs(_childs),
                    m_object(std::move(_object)) {}*/

                node(
                    node && other):
                    token_def(other),
                    //m_object(std::move(other.m_object)),
                    childs(std::move(other.childs))
                {
                }

                node(
                    const node& other):
                    token_def(other),
                    // m_object(other.m_object),
                    childs(other.childs)
                {
                }


                virtual ~node() {}

            public:
                node& operator=(
                    node && other)
                {
                    if(this != &other)
                    {
                        this->token_def::operator=(other);
                        //fct::assign(m_object, std::move(other.m_object));
                        childs = std::move(other.childs);
                    }

                    return *this;
                }

                node& operator=(
                    const node& other)
                {
                    if(this = &other)
                    {
                        this->token_def::operator=(other);
                        //fct::assign(m_object, other.m_object);
                        childs = other.childs;
                    }

                    return *this;
                }
        };

        //--//--//--//--//--//--//--//--//--//--//
        //--//--//--//--//--//--//--//--//--//--//
        //--//--//--//--//--//--//--//--//--//--//
        namespace reg
        {
            template<char c>
            struct character
            {
                static constexpr char value = c;
            };

            template<char c>
            constexpr char character<c>::value;

            // Minor
            using a = character < 'a' >;
            using b = character < 'b' >;
            using c = character < 'c' >;
            using d = character < 'd' >;
            using e = character < 'e' >;
            using f = character < 'f' >;
            using g = character < 'g' >;
            using h = character < 'h' >;
            using i = character < 'i' >;
            using j = character < 'j' >;
            using k = character < 'k' >;
            using l = character < 'l' >;
            using m = character < 'm' >;
            using n = character < 'n' >;
            using o = character < 'o' >;
            using p = character < 'p' >;
            using q = character < 'q' >;
            using r = character < 'r' >;
            using s = character < 's' >;
            using t = character < 't' >;
            using u = character < 'u' >;
            using v = character < 'v' >;
            using w = character < 'w' >;
            using x = character < 'x' >;
            using y = character < 'y' >;
            using z = character < 'z' >;

            //Major
            using A = character < 'A' >;
            using B = character < 'B' >;
            using C = character < 'C' >;
            using D = character < 'D' >;
            using E = character < 'E' >;
            using F = character < 'F' >;
            using G = character < 'G' >;
            using H = character < 'H' >;
            using I = character < 'I' >;
            using J = character < 'J' >;
            using K = character < 'K' >;
            using L = character < 'L' >;
            using M = character < 'M' >;
            using N = character < 'N' >;
            using O = character < 'O' >;
            using P = character < 'P' >;
            using Q = character < 'Q' >;
            using R = character < 'R' >;
            using S = character < 'S' >;
            using T = character < 'T' >;
            using U = character < 'U' >;
            using V = character < 'V' >;
            using W = character < 'W' >;
            using X = character < 'X' >;
            using Y = character < 'Y' >;
            using Z = character < 'Z' >;

            //figure
            using zero = character < '0' >;
            using one = character < '1' >;
            using two = character < '2' >;
            using three = character < '3' >;
            using four = character < '4' >;
            using five = character < '5' >;
            using six = character < '6' >;
            using seven = character < '7' >;
            using eight = character < '8' >;
            using nine = character < '9' >;
        }
    }
}

#endif // SUPPORTS_HPP_INCLUDED2
