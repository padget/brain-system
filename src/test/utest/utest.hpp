#ifndef TESTCORE_HPP
#define TESTCORE_HPP

///#include "../../core/core.hpp"

///#include "../../compiler/supports.hpp"
///#include "../../compiler/parser.hpp"
///#include "../../compiler/scanner.hpp"
///#include "../../compiler/utils.hpp"

#include "../../meta/meta.hpp"
namespace brain
{
    namespace test
    {
        struct object_test:
            public basic_test
        {
            virtual void test()
            {
                object o1;
                object o2 {o1};
                add_step(o1.id() != o2.id(),
                         "test of constructor by copy");
                object o3;
                add_step(o1.id() != o3.id() && o2.id() != o3.id(),
                         "test of default constructor");
                o3 = o1;
                add_step(o1.id() != o3.id(),
                         "test of copy assignement");
                object o5;
                auto o5_id = o5.id();
                object o6 {std::move(o5)};
                add_step(o5_id == o6.id(),
                         "test of move assignement");
                auto o6_id = o6.id();
                object o7 {std::move(o6)};
                add_step(o7.id() == o6_id,
                         "test of move constructor");
                object o8;
                o8.id(9);
            }
        };

        struct property_value_test:
            public basic_test
        {

            virtual void test()
            {
                {
                    property<int> pi {[](const int & a) {std::cout << "coucou";}};
                    pi(2);
                }

                {
                    int i {1};
                    property<int> pi {i};
                    add_step(pi() == i,
                             "test of cref constructor");
                }

                {
                    property<int> pi {1};
                    add_step(pi() == 1,
                             "test of uref constructor");
                }

                {
                    property<int> pi {1}, pi2 {pi};
                    add_step(pi() == pi2(),
                             "test of cref copy constructor");
                }

                {
                    property<int> pi {1};
                    pi(2);
                    add_step(pi() == 2,
                             "test of uref setter");
                }

                {
                    property<int> pi {1};
                    int i {2};
                    pi(i);
                    add_step(pi() == 2,
                             "test of cref setter");
                }

                {
                    property<int> pi {1};
                    pi.set(2);
                    add_step(pi() == 2,
                             "test of uref function setter");
                }

                {
                    property<int> pi {1};
                    int i {2};
                    pi.set(i);
                    add_step(pi() == 2,
                             "test of cref function setter");
                }

                {
                    property<long> pl {4L};
                    property<int> pi {pl()};
                    std::cout << pi() << std::endl;
                }
            }
        };


        struct property_cvalue_test:
            public basic_test
        {
            virtual void test()
            {
                {
                    property<const int> pi {1};
                    add_step(pi() == 1,
                             "test of uref constructor");
                }

                {
                    int i {1};
                    property<const int> pi {i};
                    add_step(pi() == 1,
                             "test of cref constructor");
                }

                {
                    property<const int> pi {1}, pi2 {pi};
                    add_step(pi() == pi2(),
                             "test of cref copy constructor");
                }

                {
                    property<const int> pi {property<const int>{1}};
                    add_step(pi() == 1,
                             "test of uref move constructor");
                }

            }
        };


        struct property_pointer_test:
            public basic_test
        {
            virtual void test()
            {
                {
                    property<int*> pi {new int{1}};
                    add_step(*pi() == 1,
                             "test of pointer constructor");
                }

                {
                    int* pointer {nullptr};
                    property<int *> pi {property<int *>{pointer = new int{1}}};
                    add_step(*pi() == 1 and
                             pi() == pointer,
                             "test of move semantic constructor");
                }

                {
                    property<int*> pi {new int{1}};
                    pi(new int {2});
                    add_step(*pi() == 2,
                             "test of pointer setter");
                }

                {
                    property<int *> pi {new int{1}};
                    pi.set(new int {2});
                    add_step(*pi() == 2,
                             "test of set function pointer");
                }
            }
        };


        class foo:
            public object
        {

            public:
                property<object> o2;
                virtual void serialize(
                    serialize::stream<char>& out) const
                {
                    out << "foo";
                    out << serialize::parent<char, object>(*this);
                    out << serialize::complex<char>("an_object", o2());
                }
        };

        class foo2 :
            public foo
        {
            public:
                property<object> o1;
                virtual void serialize(
                    serialize::stream<char>& out) const
                {
                    out << "foo2";
                    out << serialize::parent<char, foo>(*this);
                    out << serialize::complex<char>("o1", o1());
                }

        };


        struct marshalling_test:
            public basic_test
        {
            virtual void test()
            {
                foo2 f;
                std::cout << marshall<char, serialize::xml_format>(f) << std::endl;
            }
        };

        struct system_test:
            public basic_test
        {
            virtual void test()
            {
                sys::system s, s2;
                std::cout << marshall<char, serialize::xml_format>(s) << std::endl;
                std::cout << std::boolalpha;
                std::cout << (s == s2) << std::endl;
            }
        };


        struct any_test:
            public basic_test
        {
            virtual void test()
            {
                any d {1.};
                any d2 {4};
                any a {std::string("coucou")};
                std::cout << "any " << any_cast<double>(d) << std::endl;

            }
        };


    }



    namespace test
    {
        /*
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
            */


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


        using lqlconfig =
            cpl::config<LQL, char>;

        constexpr extern meta::string lql_ignored_reg {"[ \\n\\r\\t]+"};
        constexpr extern meta::string lql_name_reg {"[a-zA-Z_]+"};
        constexpr extern meta::string lql_string_reg {"'.*'"};
        constexpr extern meta::string lql_number_reg {"[0-9]+(\\.{1}[0-9]+){0,1}"};
        constexpr extern meta::string lql_lbracket_reg {"\\("};
        constexpr extern meta::string lql_rbracket_reg {"\\)"};
        constexpr extern meta::string lql_lbrace_reg {"\\["};
        constexpr extern meta::string lql_rbrace_reg {"\\]"};

        using lql_name_t     = cpl::terminal<lqlconfig, LQL::name, lql_name_reg>;
        using lql_ignored_t  = cpl::terminal<lqlconfig, LQL::ignored, lql_ignored_reg>;
        using lql_string_t   = cpl::terminal<lqlconfig, LQL::string, lql_string_reg>;
        using lql_number_t   = cpl::terminal<lqlconfig, LQL::number, lql_number_reg>;
        using lql_lbracket_t = cpl::terminal<lqlconfig, LQL::lbracket, lql_lbracket_reg>;
        using lql_rbracket_t = cpl::terminal<lqlconfig, LQL::rbracket, lql_rbracket_reg>;
        using lql_lbrace_t   = cpl::terminal<lqlconfig, LQL::lbrace, lql_lbrace_reg>;
        using lql_rbrace_t   = cpl::terminal<lqlconfig, LQL::rbrace, lql_rbrace_reg>;

        using lql_expression_nt  = cpl::non_terminal<lqlconfig, LQL::expression>;
        using lql_expressions_nt = cpl::non_terminal<lqlconfig, LQL::expressions>;
        using lql_component_nt   = cpl::non_terminal<lqlconfig, LQL::component>;

        using lql_component   = cpl::production<cpl::production_type::OR, lql_component_nt, lql_number_t, lql_string_t, lql_expressions_nt>;
        using lql_expression  = cpl::production <cpl::production_type::AND, lql_expression_nt, lql_lbracket_t, lql_name_t, lql_component_nt, lql_rbracket_t>;
        using lql_expressions = cpl::production<cpl::production_type::LIST, lql_expressions_nt, lql_expression_nt>;

        using grammar = cpl::grammar<lqlconfig, lql_expressions, lql_expression, lql_expressions, lql_component>;
        using token_maker = cpl::token_maker<lqlconfig, lql_name_t, lql_string_t, lql_ignored_t, lql_number_t, lql_lbracket_t, lql_rbracket_t>;
        using node_maker = cpl::node_maker<grammar>;
        using lql_scanner = cpl::scanner<lqlconfig>;
        using lql_parser = cpl::parser<grammar>;


        struct scanner_test :
            public basic_test
        {


            public:
                virtual void test()
                {
                    std::string filename = "resources/test/test.lql";
                    logger<ROOT>::info("explored file ", filename);
                    lql_scanner scan;
                    cpl::tokens_<lqlconfig> tokens;
                    logger<ROOT>::info("begin scanning");
                    cpl::scanner<lqlconfig>::build_tokens<token_maker>(filename, tokens);
                    logger<ROOT>::info("end scanning");

                    for(const auto & token : tokens)
                        logger<scanner_test>::debug((long)token.symbol_id(), ' ', token.value());
                }

        };

        struct parser_test :
            public basic_test
        {
            template<typename type_t>
            using predicate =
                cpl::node_maker<grammar>::ids_equal_predicate<type_t>;

            virtual void test()
            {
                std::string filename = "resources/test/test.lql";
                lql_scanner scan;
                cpl::tokens_<lqlconfig> tokens;
                cpl::scanner<lqlconfig>::build_tokens<token_maker>(filename, tokens);
                node_maker::node_type node;
                cpl::parser<grammar>::build_node<node_maker>(tokens, node);
                std::cout << marshall<char, serialize::xml_format>(node) << std::endl;
                //cpl::node_displayer<lqlconfig>()(node);
            }

        };

        /*                 struct tree_maker_test :
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

                   }*/
    }
}

#endif
