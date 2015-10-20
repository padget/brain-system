#ifndef TESTCORE_HPP
#define TESTCORE_HPP

#include "../../core/core.hpp"

//#include "../../compiler/supports.hpp"
//#include "../../compiler/parser.hpp"
//#include "../../compiler/scanner.hpp"
//#include "../../compiler/utils.hpp"

namespace brain
{
    namespace test
    {
        struct meta_test :
            public basic_test
        {
            virtual bool test()
            {
                return true;
            }
        };

        struct system_test :
            public basic_test
        {
                using system_clt = ptr::client_ptr<sys::system>;

                class sample_system :
                    public sys::system {};

                class sample_event :
                    public sys::event
                {

                    public:
                        inline sample_event(system_clt src) :
                            event(src)
                        {}

                        BRAIN_ALL_DEFAULT(sample_event)
                };

                template<typename system_t>
                struct sample_receiptor :
                    public sys::basic_receiptor <sample_event , system_t>
                {
                    public:
                        virtual void act(system_t& s, sample_event& e) const
                        { logger<ROOT>::debug("Helle Wolrd System test"); }
                };

                template<typename system_t>
                struct sample_receiptor2 :
                    public sys::basic_receiptor <sys::event , system_t>
                {
                    public:
                        virtual void act(system_t& s, sys::event& e) const
                        { logger<ROOT>::debug("Helle Wolrd System test 222"); }
                };

            public:

                virtual bool test()
                {
                    auto && s = sys::system_with_receiptors <
                                sample_system,
                                sample_receiptor<sample_system>,
                                sample_receiptor2<sample_system >> ()();

                    s->autoconnected(true);

                    sample_event e(s.make_client());
                    s->send(e);

                    logger<ROOT>::debug("source ", e.source().get());

                    auto && s2 = ptr::make_server<sample_system, sys::system>();
                    s2->receiptors().push_back(fct::unique<sample_receiptor2<sample_system>>());
                    s2->autoconnected(true);
                    sys::event e2(s2.make_client());
                    s2->send(e2);

                    return true;
                }
        };

        struct smart_ptr_test :
            public basic_test
        {

                class Base
                {

                    public:
                        virtual ~Base() {}
                        virtual std::string foo()
                        {return "base";}
                };

                class Derived:
                    public Base
                {

                    public:
                        virtual ~Derived() {}
                        virtual std::string foo()
                        {return "derived";}
                };

                class Derived2
                    : public Derived
                {
                    public:
                        virtual ~Derived2() {}
                        virtual std::string foo()
                        {return "derived";}
                };

            public:
                virtual bool test()
                {
                    using myptr = ptr::server_ptr<Base>;
                    myptr server(new Derived2());

                    myptr::client clt(server);

                    if(clt)
                        logger<smart_ptr_test>::debug("clt est OK ", clt->foo());

                    else
                        logger<smart_ptr_test>::debug("clt est KO");

                    {
                        myptr server2 = fct::mv(server);
                        logger<smart_ptr_test>::debug(" serveur ", bool(server2));
                    }

                    if(clt)
                        logger<smart_ptr_test>::debug("clt est OK ", clt->foo());

                    else
                        logger<smart_ptr_test>::debug("clt est KO");


                    return true;
                }
        };

        /*
                enum class LQL
                {
                    empty,       // 0
                    bullshit,    // 1
                    ignored,     // 2
                    name,        // 3
                    string,      // 4
                    number,      // 5
                    lbracket,    // 6
                    rbracket,    // 7
                    lbrace,      // 8
                    rbrace,      // 9
                    expression,  // 10
                    expressions, // 11
                    component    // 12
                };

                constexpr char lql_ignored_reg[] = "[ \\n\\r\\t]+";
                constexpr char lql_name_reg[] = "[a-zA-Z_]+";
                constexpr char lql_string_reg[] = "'.*'";
                constexpr char lql_number_reg[] = "[0-9]+(\\.{1}[0-9]+){0,1}";
                constexpr char lql_lbracket_reg[] = "\\(";
                constexpr char lql_rbracket_reg[] = "\\)";
                constexpr char lql_lbrace_reg[] = "\\[";
                constexpr char lql_rbrace_reg[] = "\\]";

                using lql_name_t         = cpl::terminal<LQL, LQL::name, lql_name_reg, cpl::non_indicative, std::string>;
                using lql_ignored_t      = cpl::terminal<LQL, LQL::ignored, lql_ignored_reg, cpl::indicative>;
                using lql_string_t       = cpl::terminal<LQL, LQL::string, lql_string_reg, cpl::non_indicative, std::string>;
                using lql_number_t       = cpl::terminal<LQL, LQL::number, lql_number_reg, cpl::non_indicative, float>;
                using lql_lbracket_t     = cpl::terminal<LQL, LQL::lbracket, lql_lbracket_reg, cpl::indicative>;
                using lql_rbracket_t     = cpl::terminal<LQL, LQL::rbracket, lql_rbracket_reg, cpl::indicative>;
                using lql_lbrace_t       = cpl::terminal<LQL, LQL::lbrace, lql_lbrace_reg, cpl::indicative>;
                using lql_rbrace_t       = cpl::terminal<LQL, LQL::rbrace, lql_rbrace_reg, cpl::indicative>;

                class component_obj :
                    public nat::object
                {
                    public:
                        nat::plmproperty<object> value;
                };

                class expression_obj :
                    public nat::object
                {
                    public:
                        nat::property<std::string> name;
                        nat::property<component_obj> component;
                };

                class expressions_obj :
                    public nat::object
                {
                    public:
                        nat::property<std::vector<expression_obj>> expressions;
                };

                using lql_expression_nt  = cpl::non_terminal<LQL, LQL::expression, expression_obj>;
                using lql_expressions_nt = cpl::non_terminal<LQL, LQL::expressions, expressions_obj>;
                using lql_component_nt   = cpl::non_terminal<LQL, LQL::component, component_obj>;

                using lql_component   = cpl::production<LQL, cpl::production_type::OR, lql_component_nt, lql_number_t, lql_string_t, lql_expressions_nt>;
                using lql_expression  = cpl::production<LQL, cpl::production_type::AND, lql_expression_nt, lql_lbracket_t, lql_name_t, lql_component_nt, lql_rbracket_t>;
                using lql_expressions = cpl::production<LQL, cpl::production_type::LIST, lql_expressions_nt, lql_expression_nt>;

                using grammar = cpl::grammar<LQL, lql_expressions, lql_component, lql_expression, lql_expressions>;
                using token_maker = cpl::token_maker<LQL, lql_name_t, lql_string_t, lql_ignored_t, lql_number_t, lql_lbracket_t, lql_rbracket_t>;
                using node_maker = cpl::node_maker<LQL, grammar::root_production_type, grammar::productions_list>;
                using lql_scanner = cpl::scanner<LQL>;
                using lql_parser = cpl::parser<grammar>;


                struct scanner_test :
                    public basic_test
                {


                    public:
                        virtual bool test()
                        {
                            std::string filename = "resources/test/test.lql";
                            lql_scanner scan;
                            token_maker::tokens_type tokens;
                            cpl::scanner<LQL>::build_tokens<token_maker>(filename, tokens);

                            for(const auto & token : tokens)
                                logger<scanner_test>::debug((long) token.id, ' ', token.value);

                            return true;
                        }

                };

                struct parser_test :
                    public basic_test
                {
                    virtual bool test()
                    {
                        std::string filename = "resources/test/test.lql";
                        lql_scanner scan;
                        token_maker::tokens_type tokens;
                        cpl::scanner<LQL>::build_tokens<token_maker>(filename, tokens);

                        for(const auto & token : tokens)
                            logger<scanner_test>::debug((long) token.id, ' ', token.value);

                        node_maker::node_type node;
                        cpl::parser<grammar>::build_node<node_maker>(tokens, node);
                        cpl::node_displayer<LQL>()(node);
                        return true;
                    }

                };

                struct tree_maker_test :
                    public basic_test
                {
                    virtual bool test()
                    {
                        cpl::node<LQL> n {LQL::number, "12"};

                        logger<LQL>::debug(typeid(cpl::terminal_object_maker<LQL, lql_number_t>()(n)).name());



                        cpl::node<LQL> open {LQL::lbracket, "("};
                        cpl::node<LQL> num {LQL::number, "12"};
                        cpl::node<LQL> nam {LQL::name, "a_name"};
                        cpl::node<LQL> close {LQL::rbracket, ")"};
                        cpl::node<LQL> mother{LQL::expression, {open, nam, num, close}};

                        cpl::node_displayer<LQL>()(mother);

                        cpl::nonterminal_object_maker<LQL, lql_expression>()(mother);

                        return true;
                    }
                };
        */
    }
}

#endif
