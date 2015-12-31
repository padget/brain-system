#ifndef __BRAIN_COMPILERUTILS_HPP
#define  __BRAIN_COMPILERUTILS_HPP

#include "supports.hpp"

namespace brain
{
    namespace cpl
    {
        /// Build a array
        /// of tokens that
        /// represent's the
        /// logical translation
        /// of the source.
        template < typename config_t,
                 typename ... terminals_t >
        struct token_maker
        {
            /// Specialisation for find_match
            /// method for one terminal_t
            template <typename terminal_t>
            struct find_match
            {
                bool operator()(
                    std::string::const_iterator& begin,
                    std::string::const_iterator& end,
                    std::smatch& m,
                    token<config_t>& max_match)
                {
                    /// If a match is found
                    /// and if the max match
                    /// length is less than
                    /// the found match, the
                    /// current match become
                    /// the max match and true
                    /// is returned
                    if(std::regex_match(begin, end, m, terminal_t::regex_std)
                            and max_match.value().length() < m.str().length())
                    {
                        make_token(max_match,
                                   terminal_t::id,
                                   std::move(m.str()));

                        return true;
                    }

                    /// Else false is
                    /// returned
                    else
                        return false;
                }
            };

            /// Fill the vector of
            /// tokens by analysing
            /// of the stream
            void operator()(
                const std::string& filename,
                std::vector<token<config_t>>& tokens)
            {
                /// Statement is the
                /// result of the
                /// conversion from the
                /// stream into string
                auto && statement =
                    ifstream_to<std::basic_string<char_<config_t>>>(std::ifstream(filename)) + "\n";

                /// Temporary smatch
                std::smatch m;

                /// Temporary max_match
                /// via a token<enum_<config_t>>
                token<config_t> max_match;

                /// Temporary buffer
                /// iterators for
                /// exploring the
                /// statement
                auto buffer_begin = statement.cbegin(),
                     buffer_end   = statement.cbegin(),
                     end          = statement.cend();

                /// Initiliase the
                /// buffer_end
                buffer_end++;

                /// While the buffer_end is
                /// not equals to end ...
                while(buffer_end != end)
                {

                    using terminals =
                        meta::list<terminals_t...>;

                    using find_match_loop =
                        meta::loop_rt <
                        terminals,
                        find_match,
                        std::logical_or<bool> >;

                    /// Find existing matches
                    /// and store the result
                    /// into max_match and
                    /// into nothing_found
                    bool && nothing_found =
                        ! find_match_loop()(buffer_begin,
                                            buffer_end,
                                            m,
                                            max_match);

                    /// If no match is found
                    /// and max_match not empty
                    /// then
                    if(nothing_found and /// WARN not nothing_found or nothing_found
                            not max_match.value().empty())
                    {
                        /// The max_match is added
                        /// to the tokens vector
                        tokens.push_back(max_match);

                        /// The buffer_begin
                        /// becomes the predecessor
                        /// of buffer_end
                        buffer_begin = std::prev(buffer_end);

                        /// Finally the max_match
                        /// is reinitialized with
                        /// a default token
                        max_match = make_token<config_t>(enum_<config_t>::ignored);
                    }

                    /// Else the buffer_end
                    /// is incremented into
                    /// the statement
                    else
                        buffer_end++;

                    /// If the analyse is
                    /// ended and if there
                    /// is a match found,
                    /// this match is added
                    /// to the tokens vector
                    if(buffer_end == end and
                            not nothing_found)
                        tokens.push_back(max_match);
                }

                /// Predicate that
                /// identifies if
                /// a token is
                /// ignored or not
                auto && is_ignored = [](auto && t)
                {
                    return t.symbol_id() == enum_<config_t>::ignored;
                };

                /// Erases all tokens
                /// that are enum_<config_t>::ignored
                tokens.erase(std::remove_if(tokens.begin(),
                                            tokens.end(),
                                            is_ignored),
                             tokens.end());
            }
        };


        template < typename config_t,
                 typename symbol_list_t,
                 typename productions_list_t,
                 size_t _idx >
        struct and_analyser;

        template < typename config_t,
                 typename symbol_list_t,
                 typename productions_list_t,
                 size_t _idx >
        struct or_analyser;

        template < typename config_t,
                 typename symbol_t,
                 typename productions_t >
        struct symbol_analyser;

        template < typename config_t,
                 typename symbol_t,
                 bool is_terminal >
        struct terminal_analyser;

        template < typename config_t,
                 typename production_t,
                 typename productions_list_t >
        struct production_analyser;


        /// Meta function that
        /// returns true_type
        /// if the id_t and
        /// other_id_t are equal
        template<typename id_t>
        struct ids_equal_predicate
        {
            template<typename other_id_t>
            using return_ =
                meta::bool_t <id_<id_t> == id_ <other_id_t>>;
        };


        /// Analyses the symbol_t
        /// by scanning the statement
        /// with its definition
        /// in the production list.
        template < typename config_t,
                 typename symbol_t,
                 typename productions_list_t >
        struct symbol_analyser
        {
            /// Extraction of the
            /// first type of the
            /// list of production
            /// that has its id equal
            /// to the symbol_t id :
            /// Extraction of the
            /// definition of the
            /// symbol_t in grammar
            using production_t =
                meta::find_one_if_t <
                productions_list_t,
                ids_equal_predicate<symbol_t >>;


            /// Analsye the current
            /// symbol by distinguing
            /// the terminal and the
            /// non terminals
            template <typename iterator_t>
            void operator()(
                iterator_t& iter,
                node<config_t>& res)
            {
                if(symbol_t::is_terminal)
                    terminal_analyser<config_t, symbol_t, symbol_t::is_terminal>()(iter, res);

                else
                    production_analyser<config_t, production_t, productions_list_t>()(iter, res);
            }
        };



        /**
         * @class terminal_analyser
         * @author bmathieu
         * @date 13/09/2015
         * @file utils.hpp
         * @brief Analyse a terminal and return true if the terminal_t::id
         * corresponds to the node.id passed in argument (by iterator).
         *
         * Moreover, if the node.id corresponds to the terminal_t::id, then
         * the iterator that encapsulates the node is incremented by one.
         */
        template < typename config_t,
                 typename symbol_t >
        struct terminal_analyser<config_t, symbol_t, true>
        {
            template <typename iterator_t>
            void operator()(
                iterator_t& iter,
                node<config_t>& res)
            {
                while((*iter).id == enum_<config_t>::ignored)
                    iter++;

                if((*iter).id == id_<symbol_t>)
                {
                    iter++;
                    res = std::move(node<config_t>(id_<symbol_t>, (*iter).value));
                }

                else
                    res = std::move(node<config_t>(enum_<config_t>::bullshit));
            }
        };

        /**
         * @brief Partial specialisation of terminal_analyser for the case false.
         */
        template < typename config_t,
                 typename symbol_t >
        struct terminal_analyser<config_t, symbol_t, false>
        {

            template <typename iterator_t>
            void operator()(
                iterator_t& iter,
                node<config_t>& res)
            {
                res = std::move(node<config_t>(enum_<config_t>::bullshit));
            }
        };

        /**
         * @class and_analyser
         * @author bmathieu
         * @date 12/09/2015
         * @file utils.hpp
         * @brief Functor to analyse production of type AND.
         *
         * Return true if the type '_idx' (reversing loop) corresponds to the id
         * of the given node id and the next too.
         */
        template < typename config_t,
                 typename production_t,
                 typename productions_list_t,
                 size_t _idx = meta::size_<typename production_t::symbols_list> >
        struct and_analyser
        {
            using symbol_t =
                meta::at_c < meta::size_<typename production_t::symbols_list> - _idx, typename production_t::symbols_list >;

            template <typename iterator_t>
            void operator()(
                iterator_t& iter,
                node<config_t>& res)
            {
                node<config_t> current_res;
                symbol_analyser<config_t, symbol_t, productions_list_t>()(iter, current_res);

                if(current_res)
                {
                    res = node<config_t>(id_<production_t>, {current_res});

                    node<config_t> next_res;
                    and_analyser < config_t, production_t, productions_list_t, _idx - 1 > ()(iter, next_res);

                    if(next_res)
                        res.childs.insert(res.childs.end(),
                                          next_res.childs.begin(),
                                          next_res.childs.end());

                    else
                        res = std::move(node<config_t>(enum_<config_t>::bullshit));
                }

                else
                    res = std::move(node<config_t>(enum_<config_t>::bullshit));
            }
        };

        /**
         * @brief Partial specialisation of and_analyse for the case '_idx' equals 0.
         */
        template < typename config_t,
                 typename production_t,
                 typename productions_list_t >
        struct and_analyser<config_t, production_t, productions_list_t, 0>
        {
            using symbol_t =
                meta::at_c<meta::size_<typename production_t::symbols_list>, typename production_t::symbols_list>;

            template <typename iterator_t>
            void operator()(
                iterator_t& iter,
                node<config_t>& res)
            {
                node<config_t> current_res;
                symbol_analyser<enum_<config_t>, symbol_t, productions_list_t>()(iter, current_res);

                if(current_res)
                    res = std::move(node<config_t>(id_<production_t>, {current_res}));

                else
                    res = std::move(node<config_t>(enum_<config_t>::bullshit));
            }
        };

        /**
         * @class list_analyser
         * @author bmathieu
         * @date 13/09/2015
         * @file utils.hpp
         * @brief Analyse a production of type LIST.
         *
         * Return always true because a list can be empty
         */
        template < typename config_t,
                 typename production_t,
                 typename productions_list_t >
        struct list_analyser
        {
            template <typename iterator_t>
            void operator()(
                iterator_t& iter,
                node<config_t>& res)
            {
                auto current =
                    iter;
                res = std::move(node<config_t>(id_<production_t>));
                node<config_t> current_res {node<config_t>(enum_<config_t>::ignored)};

                do
                {
                    and_analyser<config_t, production_t, productions_list_t>()(current, current_res);

                    if(current_res)
                    {
                        res.childs.insert(res.childs.end(),
                                          current_res.childs.begin(),
                                          current_res.childs.end());
                        iter = current;
                    }
                }
                while(current_res);
            }
        };

        /**
         * @class and_analyser
         * @author bmathieu
         * @date 12/09/2015
         * @file utils.hpp
         * @brief Functor to analyse production of type AND.
         *
         * Return true if the type '_idx' (reversing loop) corresponds to the id
         * of the given node id or one of the nexts.
         */
        template < typename config_t,
                 typename production_t,
                 typename productions_list_t,
                 size_t _idx = meta::size_<typename production_t::symbols_list> >
        struct or_analyser
        {
            using symbol_t =
                meta::at_c < meta::size_<typename production_t::symbols_list> - _idx, typename production_t::symbols_list >;

            template <typename iterator_t>
            void operator()(
                iterator_t& iter,
                node<config_t>& res)
            {
                node<config_t> current_res;
                symbol_analyser<config_t, symbol_t, productions_list_t>()(iter, res);

                if(not res)
                    or_analyser < config_t, production_t, productions_list_t, _idx - 1 > ()(iter, res);
            }
        };

        /**
         * @brief Partial specialisation of or_analyse for the case '_idx' equals 0.
         */
        template < typename config_t,
                 typename production_t,
                 typename productions_list_t >
        struct or_analyser<config_t, production_t, productions_list_t, 0>
        {
            using symbol_t =
                meta::at_c<meta::size_<typename production_t::symbols_list> , typename production_t::symbols_list>;

            template <typename iterator_t>
            void operator()(
                iterator_t& iter,
                node<config_t>& res)
            {
                symbol_analyser<config_t, symbol_t, productions_list_t>()(iter, res);
            }
        };

        /**
         * @class production_analyser
         * @author bmathieu
         * @date 14/09/2015
         * @file utils.hpp
         * @brief Analyse a production (AND, OR, LIST)
         */
        template < typename config_t,
                 typename production_t,
                 typename productions_list_t >
        struct production_analyser
        {
            using and_anl =
                and_analyser<config_t, production_t, productions_list_t>;
            using list_anl =
                list_analyser<config_t, production_t, productions_list_t>;
            using or_anl =
                or_analyser<config_t, production_t, productions_list_t>;

            template <typename iterator_t>
            void operator()(
                iterator_t& iter,
                node<config_t>& res)
            {
                switch(production_t::type)
                {
                    case production_type::AND:
                        and_anl()(iter, res);
                        break;

                    case production_type::LIST:
                        list_anl()(iter, res);
                        break;

                    case production_type::OR:
                        or_anl()(iter, res);
                        break;

                    default:
                        res = std::move(node<config_t>(enum_<config_t>::bullshit));
                        break;
                }
            }
        };

        /**
         * @brief Partial specialisation of production_analyser for the case no_type
         */
        template < typename config_t,
                 typename productions_list_t >
        struct production_analyser<config_t, meta::nil, productions_list_t>
        {
            template <typename iterator_t>
            void operator()(
                iterator_t& iter,
                node<config_t>& res)
            {
                res = std::move(node<config_t>(enum_<config_t>::bullshit));
            }
        };


        /**
         * @class node_maker
         * @author bmathieu
         * @date 14/09/2015
         * @file utils.hpp
         * @brief Build the node tree from an array of token and
         * in accordance with a grammar ('productions_list_t').
         */
        template < typename config_t,
                 typename root_production_t,
                 typename productions_list_t >
        struct node_maker
        {
            using node_type =
                node<config_t>;
            using token_type =
                token<config_t>;
            using tokens_type =
                std::vector<token_type>;
            using root_type =
                root_production_t;
            using productions_list =
                productions_list_t;

            void operator()(
                tokens_type & tokens,
                node<config_t>& res)
            {
                typename tokens_type::const_iterator b =
                    tokens.cbegin();

                if(b not_eq tokens.end())
                    production_analyser<config_t, root_type, productions_list>()(b, res);

                else
                    res = std::move(node<config_t>(enum_<config_t>::bullshit));

                if(b not_eq tokens.end())
                    res = std::move(node<config_t>(enum_<config_t>::bullshit));
            }
        };

        //--//--//--//--//--//--//--//--//--//--//
        //--//--//--// TREE MANANGER /--//--//--//
        //--//--//--//--//--//--//--//--//--//--//

        template <typename to_t>
        struct converter
        {
            auto operator()(
                const std::string& from)
            {
                return static_cast<to_t>(from);
            }
        };


        template<>
        struct converter<int>
        {
            auto operator()(
                const std::string& from)
            {
                return std::stoi(from);
            }
        };


        template<>
        struct converter<long>
        {
            auto operator()(
                const std::string& from)
            {
                return std::stol(from);
            }
        };


        template<>
        struct converter<long long>
        {
            auto operator()(
                const std::string& from)
            {
                return std::stoll(from);
            }
        };


        template<>
        struct converter<unsigned>
        {
            unsigned operator()(
                const std::string& from)
            {
                return std::stoul(from);
            }
        };


        template<>
        struct converter<unsigned long>
        {
            auto operator()(
                const std::string& from)
            {
                return std::stoul(from);
            }
        };

        template<>
        struct converter<unsigned long long>
        {
            auto operator()(
                const std::string& from)
            {
                return std::stoull(from);
            }
        };


        template<>
        struct converter<float>
        {
            auto operator()(
                const std::string& from)
            {
                return std::stof(from);
            }
        };

        template<>
        struct converter<double>
        {
            auto operator()(
                const std::string& from)
            {
                return std::stod(from);
            }
        };

        template<>
        struct converter<long double>
        {
            auto operator()(
                const std::string& from)
            {
                return std::stold(from);
            }
        };

        template < typename config_t,
                 typename symbol_t >
        struct terminal_object_maker
        {
            using node_type =
                node<config_t>;
            using target =
                typename symbol_t::target_type;

            target operator()(
                const node_type& n)
            {
                return n.id == id_<symbol_t> ?
                       converter<target>()(n.value) :
                       target();
            }
        };

        template<typename config_t>
        struct node_displayer;

        template < typename config_t,
                 typename production_t >
        struct nonterminal_object_maker
        {
            using node_type =
                node<config_t>;
            using target =
                typename production_t::symbol_type::target_type;

            target operator()(
                const node_type& n)
            {
                node_displayer<enum_<config_t>>()(n);

                if(not n.childs.empty())
                {
                    typename production_t::symbols_list::elements args;
                    make_for_each_symbol<typename production_t::symbols_list>()(n.childs, args);
                }

                return target();
            }

            template < typename symbol_list_t,
                     size_t _idx = symbol_list_t::last_idx >
            struct make_for_each_symbol
            {
                using current_symbol =
                    meta::at_c < symbol_list_t::last_idx - _idx, symbol_list_t >;

                void operator()(
                    const std::vector<node_type>& childs,
                    typename symbol_list_t::elements& args)
                {
                    if(childs[_idx].id == id_<current_symbol>)
                    {
                        std::get<_idx>(args) =
                            terminal_object_maker<enum_<config_t>, current_symbol>()(childs[_idx]);
                        make_for_each_symbol < symbol_list_t, _idx - 1 > ()(childs, args);
                    }
                }
            };

            template<typename symbol_list_t>
            struct make_for_each_symbol<symbol_list_t, 0>
            {
                using current_symbol =
                    meta::at_c<symbol_list_t::last_idx, symbol_list_t>;

                void operator()(
                    const std::vector<node_type>& childs,
                    typename symbol_list_t::elements& args)
                {
                    if(childs[0].id == id_<current_symbol>)
                        std::get<0>(args) =
                            std::move(terminal_object_maker<enum_<config_t>, current_symbol>()(childs[0]));
                }
            };
        };

        template<typename grammar_t>
        struct tree_maker
        {
            using grammar =
                grammar_t;
            using root_production_type =
                typename grammar::root_production_type;
            using root_symbol =
                typename root_production_type::symbol_type;
            using target =
                typename root_symbol::target_type;
            using enum_type =
                typename grammar_t::enum_type;
            using node_type =
                node<enum_type>;

            target operator()(
                const node_type& root_node)
            {
                auto node_id = root_node.id;

                return target();
            }
        };

        //--//--//--//--//--//--//--//--//--//--//
        //--//--//--// DISPLAYER    //--//--//--//
        //--//--//--//--//--//--//--//--//--//--//

        /**
         * @class symbol_displayer
         * @author Benjamin
         * @date 14/09/2015
         * @file utils.hpp
         * @brief Display the content of the symbol and the next
         * in the list.
         */
        template < typename config_t,
                 typename symbols_list_t,
                 production_type _type,
                 size_t _idx = symbols_list_t::last_idx >
        struct symbol_displayer
        {
            using symbol_t =
                meta::at_c < symbols_list_t::last_idx - _idx, symbols_list_t >;

            void operator()()
            {
                logger<enum_<config_t>>::trace("  ", static_cast<char>(_type), " --- ", (long) symbol_t::id);
                symbol_displayer < enum_<config_t>, symbols_list_t, _type, _idx - 1 > ()();
            }
        };

        /**
         * @brief Partial specialisation of symbol_displayer for case 0
         */
        template < typename config_t,
                 typename symbols_list_t,
                 production_type _type >
        struct symbol_displayer<config_t, symbols_list_t, _type, 0>
        {
            using symbol_t =
                meta::at_c<symbols_list_t::last_idx, symbols_list_t>;

            void operator()()
            {
                logger<enum_<config_t>>::trace("  ",
                                               static_cast<char>(_type),
                                               " --- ",
                                               (long)symbol_t::id);
            }
        };

        /**
         * @class production_displayer
         * @author Benjamin
         * @date 14/09/2015
         * @file utils.hpp
         * @brief Display the content of the production and the next
         * in the list.
         */
        template < typename config_t,
                 typename productions_list_t,
                 size_t _idx = productions_list_t::last_idx >
        struct production_displayer
        {
            using production_t =
                meta::at_c < productions_list_t::last_idx - _idx, productions_list_t >;

            void operator()()
            {
                logger<enum_<config_t>>::trace(" - production ", (long)production_t::id);
                symbol_displayer <enum_<config_t>, typename production_t::symbols_list, production_t::type>()();
                production_displayer < enum_<config_t>, productions_list_t, _idx - 1 > ()();
            }
        };

        /**
         * @brief Partial specialisation of production_displayer for case 0
         */
        template < typename config_t,
                 typename productions_list_t >
        struct production_displayer<config_t, productions_list_t, 0>
        {
            using production_t =
                meta::at_c<productions_list_t::last_idx, productions_list_t>;

            void operator()()
            {
                logger<enum_<config_t>>::trace(" - production ", (long)production_t::id);
                symbol_displayer <enum_<config_t>, typename production_t::symbols_list, production_t::type>()();
            }
        };

        /**
         * @class grammar_displayer
         * @author Benjamin
         * @date 14/09/2015
         * @file utils.hpp
         * @brief Display the content of the grammar
         */
        template <typename grammar_t>
        struct grammar_displayer
        {
            using root_production_type =
                typename grammar_t::root_production_type;
            using enum_type =
                typename grammar_t::enum_type;
            using productions_list =
                typename grammar_t::productions_list;

            void operator()()
            {
                using log_t =
                    enum_<config_<grammar_t>>;

                logger<log_t>::trace("-----", "grammar_displayer", "-----");
                logger<log_t>::trace("root symbol ", (long)root_production_type::id);
                production_displayer<enum_type, productions_list>()();
                logger<log_t>::trace("-----", "grammar_displayer", "-----");
            }
        };

        template<typename id_t>
        struct is_same_id
        {
            template<typename other_id_t>
            using return_ =
                meta::bool_t_<id_<id_t> == id_<other_id_t>>;
        };

        /**
         * @class production_defined
         * @author bmathieu
         * @date 14/09/2015
         * @file utils.hpp
         * @brief Determines if a production 'production_t' is fully defined.
         *
         * If each non-terminal symbol which is contained in production is
         * defined in 'productions_list_t', value is true, else value is false.
         */
        template < typename production_t,
                 typename productions_list_t,
                 size_t _idx = production_t::symbols_list::last_idx >
        struct production_defined
        {
            using symbol_type =
                meta::at_c<_idx, typename production_t::symbols_list>;



            static constexpr bool value =
                (symbol_type::is_terminal
                 or (not symbol_type::is_terminal
                     and meta::size_<meta::filter_t<productions_list_t, is_same_id<symbol_type>>> == 1))
                and meta::v_ < production_defined < production_t, productions_list_t, _idx - 1 >>;
        };

        template < typename production_t,
                 typename productions_list_t,
                 size_t _idx >
        constexpr bool production_defined<production_t, productions_list_t, _idx>::value;

        /**
         * @brief Partial specialisation of production_defined for case 0
         */
        template < typename production_t,
                 typename productions_list_t >
        struct production_defined<production_t, productions_list_t, 0>
        {
            using symbol_type =
                meta::at_c<0, typename production_t::symbols_list>;
            static constexpr bool value =
                symbol_type::is_terminal
                or (not symbol_type::is_terminal
                    and meta::size_<meta::filter_t<productions_list_t, is_same_id<symbol_type>>> == 1);
        };

        template < typename production_t,
                 typename productions_list_t >
        constexpr bool production_defined<production_t, productions_list_t, 0>::value;

        /**
         * @class productions_defined
         * @author bmathieu
         * @date 14/09/2015
         * @file utils.hpp
         * @brief Determines if all productions of 'productions_list_t'
         * is fully defined.
         */
        template < typename productions_list_t,
                 size_t _idx = productions_list_t::last_idx >
        struct productions_defined
        {
            using production_t =
                meta::at_c<0, productions_list_t>;
            static constexpr bool value =
                meta::v_<production_defined<production_t, productions_list_t>>
                and meta::v_ < productions_defined < productions_list_t, _idx - 1 >>;
        };

        template < typename productions_list_t,
                 size_t _idx >
        constexpr bool productions_defined<productions_list_t, _idx>::value;

        /**
         * @brief Partial specialisation of productions_defined for the case O
         */
        template <typename productions_list_t>
        struct productions_defined<productions_list_t, 0>
        {
            using production_t =
                meta::at_c<0, productions_list_t>;
            static constexpr bool value = meta::v_<production_defined<production_t, productions_list_t>>;
        };

        template <typename productions_list_t>
        constexpr bool productions_defined<productions_list_t, 0>::value;

        /**
         * @class grammar_checker
         * @author bmathieu
         * @date 14/09/2015
         * @file utils.hpp
         * @brief Check if a grammar is correctly defined
         */
        template<typename grammar_t>
        struct grammar_checker
        {
            using productions_list =
                typename grammar_t::productions_list;

            auto operator()()
            {
                auto there_is_no_problem = true;
                there_is_no_problem &= meta::v_<productions_defined<productions_list>>;
                return there_is_no_problem;
            }
        };

        /**
         * @class node_displayer
         * @author bmathieu
         * @date 17/09/2015
         * @file utils.hpp
         * @brief Displays node and childs recursively
         */
        template<typename config_t>
        struct node_displayer
        {
            void operator()(const node<config_t>& n,
                            unsigned udec = 0)
            {
                if(udec == 0u)
                    logger<enum_<config_t>>::info("---- ",
                                                  "node_displayer",
                                                  " ----");

                logger<enum_<config_t>>::info(std::string(udec, ' '),
                                              (long)n.symbol_id());

                for(const auto & child : n.childs())
                    node_displayer()(child,
                                     udec + 3u);

                if(udec == 0u)
                    logger<enum_<config_t>>::info("---- ",
                                                  "node_displayer",
                                                  " ----");
            }
        };

    }
}

#endif // __BRAIN_COMPILERUTILS_HPP
