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
            using token_factory =
                factory<token_<config_t>>;

            /// Specialisation for find_match
            /// method for one terminal_t
            template <typename terminal_t>
            struct find_match
            {
                bool operator()(
                    std::string::const_iterator& begin,
                    std::string::const_iterator& end,
                    std::smatch& m,
                    token_<config_t>& max_match)
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
                        token_factory::make(max_match,
                                            id_<terminal_t>,
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
                std::vector<token_<config_t>>& tokens)
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
                token_<config_t> max_match;

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
                        meta::foreach_type <
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
                    if(nothing_found and
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
                        token_factory::make_ignored(max_match);
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
                auto && is_ignored = [](const auto & t)
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


        /// The node maker
        /// build a tree of
        /// node based of
        /// a sequence of
        /// token
        template<typename grammar_t>
        struct node_maker
        {
            using node_type =
                node_<config_<grammar_t>>;
            using token_type =
                token_<config_<grammar_t>>;
            using tokens_type =
                tokens_<config_<grammar_t>>;
            using productions_list =
                productions_<grammar_t>;

            using node_factory =
                factory<node_<node_maker>>;



            /// Execute the process
            /// of the tree building
            void operator()(
                std::vector<token_type> & tokens,
                node_<config_<grammar_t>>& res)
            {
                meta::citerator_t<tokens_type> b =
                    tokens.cbegin();

                /// If b is not the
                /// end of the token
                /// sequence the
                /// analyse is triggered
                if(b not_eq tokens.end())
                    production_analyser<root_<grammar_t>>()(b, res);

                else
                    /// Build a bullshit
                    node_factory::make_bullshit(res);

                /// If after the analyse
                /// b is not not the end
                /// of the token sequence
                /// a bullshit token is
                /// built and returned
                if(b not_eq tokens.end())
                    node_factory::make_bullshit(res);

                /// Clear all tokens
                /// because the values
                /// has been moved
                /// to the corresponding
                /// nodes in the tree
                tokens.clear();
            }


            /// Declaration of the
            /// symbol_analyser
            template < typename symbol_t,
                     bool is_terminal  =
                     meta::v_<is_terminal_t<symbol_t>> >
            struct symbol_analyser;


            /// Declaration of the
            /// terminal_anlayser
            template <typename symbol_t>
            struct terminal_analyser;


            /// Declaration of the
            /// production_analyser
            template <typename production_t>
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
            template <typename symbol_t>
            struct symbol_analyser<symbol_t, false>
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
                    productions_list,
                    ids_equal_predicate<symbol_t >>;


                /// Analsye the current
                /// symbol
                template <typename iterator_t>
                void operator()(
                    iterator_t& iter,
                    node_<config_<symbol_t>>& res,
                    unsigned udec = 0u)
                {
                    /// it is the
                    /// production_analyser
                    production_analyser<production_t>()(iter, res, udec);
                }
            };


            /// Analyses the symbol_t
            /// by scanning the statement
            /// with its definition
            /// in the production list.
            template <typename symbol_t>
            struct symbol_analyser<symbol_t, true>
            {

                /// Analsye the current
                /// symbol
                template <typename iterator_t>
                void operator()(
                    iterator_t& iter,
                    node_<config_<symbol_t>>& res,
                    unsigned udec = 0u)
                {
                    logger<ROOT>::debug(std::string(3 * udec, ' '), "begin terminal ", (long)id_<symbol_t>, " value : '", (*iter).value(), "'");

                    /// the symbol_t is
                    /// a terminal, the
                    /// terminal_analyser
                    /// is triggered
                    terminal_analyser<symbol_t>()(iter, res, udec);

                    logger<ROOT>::debug(std::string(3 * udec, ' '), "end terminal ", (long)id_<symbol_t>, " value : '", (*iter).value(), "'");
                }
            };


            /// Analyse terminal
            /// symbol. Don't work
            /// on non terminal symbol
            template <typename symbol_t>
            struct terminal_analyser
            {
                static_assert(meta::v_<is_terminal_t<symbol_t>>,
                              "terminal_analyser : The symbol_t::is_terminal must be true");

                /// Analyse a terminal
                /// symbol and build
                /// the corresponding node
                template <typename iterator_t>
                void operator()(
                    iterator_t& iter,
                    node_<config_<symbol_t>>& res,
                    unsigned udec = 0u)
                {
                    logger<ROOT>::debug(std::string(3 * udec, ' '),
                                        "Examining of ",
                                        (long)(*iter).symbol_id(),
                                        " vs theorical ",
                                        (long)id_<symbol_t>);

                    /// If the current
                    /// symbol_id is the
                    /// same as the current
                    /// analysed symbol_t
                    /// the iterator is
                    /// incremented and
                    /// a node is built
                    if((*iter).symbol_id() == id_<symbol_t>)
                    {
                        node_factory::make(res,
                                           id_<symbol_t>,
                                           (*iter).value());
                        iter++;
                    }

                    /// Else makes a
                    /// bullshit node
                    else
                        node_factory::make_bullshit(res);
                }
            };


            /// Analyse the production
            /// that has a production_type
            /// equals to AND
            template <typename production_t>
            struct and_analyser
            {
                using symbols =
                    typename production_t::symbols_type;

                /// Functor executed for
                /// each symbol of the
                /// production_t
                template<typename symbol_t>
                struct foreach_symbol
                {
                    /// Process for
                    /// the symbol_t
                    template <typename iterator_t>
                    void operator()(
                        iterator_t& iter,
                        node_<config_<production_t>>& res,
                        bool& no_bullshit,
                        unsigned udec = 0u)
                    {
                        /// If no bullshit has
                        /// been detected during
                        /// the previous steps,
                        /// then ...
                        if(no_bullshit)
                        {
                            /// The potential child node
                            node_<config_<production_t>> potential_child;

                            /// Triggers the analyse
                            /// of the symbol_t
                            symbol_analyser<symbol_t>()(iter, potential_child, udec + 1);

                            /// If the potential child
                            /// is valid, it is added
                            /// the childs sequence of
                            /// the res node
                            if(potential_child)
                                res.childs().push_back(potential_child);

                            /// Else no_bullshit
                            /// is tagged to false
                            /// to by pass the next
                            /// steps of the process
                            else
                                no_bullshit = false;
                        }
                    }
                };


                using foreach_type =
                    meta::foreach_type<symbols, foreach_symbol>;


                /// Functor that launch
                /// of the and analyse
                template <typename iterator_t>
                void operator()(
                    iterator_t& iter,
                    node_<config_<production_t>>& res,
                    unsigned udec = 0u)
                {
                    logger<ROOT>::debug(std::string(3 * udec, ' '), "begin and ", (long) id_<production_t>);

                    /// The process is not began
                    /// so no bullshit has been
                    /// detected (=> true)
                    bool no_bullshit {true};

                    /// Foreach symbol,
                    /// the analyse is triggered
                    foreach_type()(iter, res, no_bullshit, udec);

                    /// After the all analyses,
                    /// if there is childs in
                    /// res and there is no
                    /// bullshit detected,
                    /// the res is tagged
                    /// with the id of the
                    /// production_t
                    if(!res.childs().empty()
                            and no_bullshit)
                        node_factory::make(res, id_<production_t>);

                    /// Else the res is
                    /// tagged as bullshit
                    else
                        node_factory::make_bullshit(res);

                    logger<ROOT>::debug(std::string(3 * udec, ' '), "end and ", (long)id_<production_t>);
                }
            };


            /// Analyse the production
            /// that has a production_type
            /// equals to LIST
            template <typename production_t>
            struct list_analyser
            {
                /// Functor that triggers
                /// the list analyse
                template <typename iterator_t>
                void operator()(
                    iterator_t& iter,
                    node_<config_<production_t>>& res,
                    unsigned udec = 0u)
                {
                    logger<ROOT>::debug(std::string(3 * udec, ' '), "begin list ", (long)id_<production_t>);

                    auto current = iter;

                    /// Even if there is
                    /// no element in the
                    /// list, the res is
                    /// tagged to id of
                    /// the production_t
                    node_factory::make(res, id_<production_t>);

                    /// Initiates the current_res
                    /// with a bullshit node
                    node_<config_<production_t>> current_res
                    { bullshit_<enum_<config_<production_t>>> };

                    /// While the current_res
                    /// is valid the process
                    /// will be running
                    do
                    {
                        /// A the beginning
                        /// of the iteration
                        /// the current_res
                        /// is reinitialized
                        /// with bullshit node
                        node_factory::make_bullshit(current_res);

                        /// Then, an and_analyse
                        /// is triggered to process
                        /// the production_t
                        and_analyser<production_t>()(current, current_res, udec);

                        /// If the analyse is
                        /// concluent, the iter
                        /// is udpated with
                        /// current and the all
                        /// childs of current_res
                        /// is added to the childs
                        /// of the res node
                        if(current_res)
                        {
                            iter = current;
                            res.childs().insert(res.childs().end(),
                                                current_res.childs().begin(),
                                                current_res.childs().end());
                        }
                    }
                    while(current_res);

                    logger<ROOT>::debug(std::string(3 * udec, ' '), "end list ", (long)id_<production_t>);
                }
            };


            /// Analyse the production
            /// that has a production_type
            /// equals to OR
            template <typename production_t>
            struct or_analyser
            {
                using symbols =
                    typename production_t::symbols_type;


                /// HERE
                template<typename symbol_t>
                struct foreach_symbol
                {
                    template <typename iterator_t>
                    void operator()(
                        iterator_t& iter,
                        node_<config_<production_t>>& res,
                        bool& found,
                        unsigned udec = 0u)
                    {
                        if(not found)
                        {
                            node_<config_<production_t>> potential_res;

                            symbol_analyser<symbol_t>()(iter, potential_res, udec + 1);

                            if(potential_res)
                            {
                                found = true;
                                res = std::move(potential_res);
                            }
                        }
                    }
                };


                using foreach_type =
                    meta::foreach_type<symbols, foreach_symbol>;


                template <typename iterator_t>
                void operator()(
                    iterator_t& iter,
                    node_<config_<production_t>>& res,
                    unsigned udec = 0u)
                {
                    bool found {false};
                    logger<ROOT>::debug(std::string(3 * udec, ' '), "begin or ", (long)id_<production_t>);
                    foreach_type()(iter, res, found, udec);
                    logger<ROOT>::debug(std::string(3 * udec, ' '), "end or ", (long)id_<production_t>);
                }
            };


            /**
             * @class production_analyser
             * @author bmathieu
             * @date 14/09/2015
             * @file utils.hpp
             * @brief Analyse a production (AND, OR, LIST)
             */
            template <typename production_t>
            struct production_analyser
            {
                using and_anl =
                    and_analyser<production_t>;
                using list_anl =
                    list_analyser<production_t>;
                using or_anl =
                    or_analyser<production_t>;

                template <typename iterator_t>
                void operator()(
                    iterator_t& iter,
                    node_<config_<production_t>>& res,
                    unsigned udec = 0u)
                {
                    switch(production_t::type)
                    {
                        case production_type::AND:
                            and_anl()(iter, res, udec);
                            break;

                        case production_type::LIST:
                            list_anl()(iter, res, udec);
                            break;

                        case production_type::OR:
                            or_anl()(iter, res, udec);
                            break;

                        default:
                            node_factory::make_bullshit(res);
                            break;
                    }
                }
            };
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
                                               (long) symbol_t::id);
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
            void operator()(const node_<config_t>& n,
                            unsigned udec = 0)
            {
                if(udec == 0u)
                    logger<enum_<config_t>>::info("---- ",
                                                  "node_displayer",
                                                  " ----");

                logger<enum_<config_t>>::info(std::string(udec, ' '),
                                              (long)n.symbol_id(),
                                              " ", n.value());

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
