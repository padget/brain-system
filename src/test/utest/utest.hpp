#ifndef TESTCORE_HPP
#define TESTCORE_HPP

#include "../../core/core.hpp"

#include "../../compiler/supports.hpp"
#include "../../compiler/parser.hpp"
#include "../../compiler/scanner.hpp"
#include "../../compiler/utils.hpp"

namespace brain
{
    namespace meta
    {
        namespace test
        {
            /// Unitary test for
            /// member meta features
            struct member_test :
                public brain::test::basic_test
            {
                struct a_type
                {
                    using type = a_type;
                    static constexpr int value = 1;
                    static constexpr size_t size = 12;

                    template<typename ... args>
                    using return_ = a_type;
                };

                struct another_type {};

                virtual void test()
                {
                    add_step(v_<std::is_same<t_<a_type>, a_type>>,
                             "test of t_");
                    add_step(v_<a_type> == 1,
                             "test of v_");
                    add_step(v_<std::is_same<vt_<a_type>, const int>>,
                             "test of vt_");
                    add_step(size_<a_type> == 12,
                             "test of size_");
                    add_step(v_<std::is_same<return_<a_type, int>, a_type>>,
                             "test of return_");
                    add_step(v_<std::is_same<r_<a_type, int>, a_type>>,
                             "test of r_");
                }
            };


            /// Unitary test for
            /// literal meta features
            struct literal_test:
                public brain::test::basic_test
            {
                virtual void test()
                {
                    add_step(v_<bool_t_<true>> == true, "");
                    add_step(v_<short_t_<1>> == 1, "");
                    add_step(v_<ushort_t_<1>> == 1, "");
                    add_step(v_ < char_t_ < 'c' >> == 'c', "");
                    add_step(v_<int_t_<1>> == 1, "");
                    add_step(v_<long_t_<1>> == 1, "");
                    add_step(v_<longlong_t_<1>> == 1, "");
                    add_step(v_<unsigned_t_<1>> == 1, "");
                    add_step(v_<unsignedl_t_<1>> == 1, "");
                    add_step(v_<unsignedll_t_<1>> == 1, "");
                    add_step(v_<size_t_<1>> == 1, "");
                }
            };


            /// Unitary test for
            /// const keyword meta
            /// features
            struct constkw_test:
                public brain::test::basic_test
            {
                virtual void test()
                {
                    add_step(v_<sizeof_t_<int>> == sizeof(int), "");
                    add_step(v_<sizeof_pack_t_<int, double, int>> == 3, "");
                    add_step(v_<alignof_t_<int>> == alignof(int), "");
                }
            };


            /// Unitary test for
            /// pack meta features
            struct pack_test:
                public brain::test::basic_test
            {
                using a_list = list<int, float, double>;

                virtual void test()
                {
                    add_step(size_<a_list> == v_<sizeof_pack_t_<int, float, double>>, "");
                    add_step(v_<std::is_same<t_<a_list>, a_list>>, "");
                    add_step(v_<std::is_same<front_t<a_list>, int>>, "");
                    add_step(v_<std::is_same<back_t<a_list>, double>>, "");
                    add_step(v_<std::is_same<concat_t<list<int>, list<float, double>, list<>>, list<int, float, double>>>, "");
                    add_step(v_<std::is_same<at_t<unsigned_t<2>, a_list>, double>>, "");
                    add_step(v_<std::is_same<repeat_t<unsigned_t<3>, int>, list<int, int, int>>>, "");
                    add_step(v_<std::is_same<to_list_t<std::tuple<int, int>>, list<int, int>>>, "");
                }
            };


            /// Unitary test for
            /// meta function features
            struct function_test:
                public brain::test::basic_test
            {
                struct a_type
                {
                    template<typename ... args>
                    using return_ = int;

                    using type = int;
                };

                struct another_type
                {
                };

                using a_list = list<int, double>;
                using a_second_list = list<int>;

                virtual void test()
                {
                    /// TODO Unitary for compose
                    add_step(v_<std::is_same<always_r<void>, void>> , "");
                    add_step(v_<has_type_t<a_type>>, "");
                    add_step(!v_<has_type_t<another_type>>, "");
                    add_step(v_<has_return_t<a_type>>, "");
                    add_step(!v_<has_return_t<another_type>>, "");
                    add_step(v_<is_meta_function_t<a_type>>, "");
                    add_step(!v_<is_meta_function_t<another_type>>, "");
                    add_step(v_<std::is_same<expand_t<a_type, list<int, double>>, int>>, "");
                    add_step(v_<std::is_same<push_back_t<float, a_list>, list<int, double, float>>>, "");
                    add_step(v_<std::is_same<push_front_t<float, a_list>, list<float, int, double>>>, "");
                    add_step(v_<std::is_same<pop_back_t<a_list>, list<int>>>, "");
                    add_step(v_<std::is_same<pop_front_t<a_list>, list<double>>>, "");
                }
            };


            /// Unitary test for
            /// deferring feature
            /*struct deferring_test:
                public brain::test::basic_test
            {
                template<typename ... args_t>
                struct a_type
                {
                    using type = void;
                };

                virtual void test()
                {
                    add_step(v_<std::is_same<t_<defer<a_type, int, double>>, void>>, "");
                    return v_<std::true_type>;
                }
            };*/


            /// Unitary test for
            /// quote feature
            struct quote_test:
                public brain::test::basic_test
            {
                template<typename ... args_t>
                struct a_type
                {
                };

                virtual void test()
                {
                    add_step(v_<std::is_same<r_<quote_r_<a_type>, int, float, double>, a_type<int, float, double>>> , "");
                }
            };


            /// Unitary test for
            /// math features
            struct math_test:
                public brain::test::basic_test
            {
                virtual void test()
                {
                    add_step(v_<inc_t_<unsigned_t_<0>>> == 1, "");
                    add_step(v_<dec_t_<unsigned_t_<1>>> == 0, "");
                    add_step(v_<plus_t<unsigned_t_<1>, unsigned_t_<1>>> == 2, "");
                    add_step(v_<minus_t_<unsigned_t_<1>, unsigned_t_<1>>> == 0, "");
                    add_step(v_<multiplies_t_<unsigned_t_<2>, unsigned_t_<2>>> == 4, "");
                    add_step(v_<divides_t_<unsigned_t_<4>, unsigned_t_<2>>> == 2, "");
                    add_step(v_<negate_t_<int_t_<1>>> == -1, "");
                    add_step(v_<modulus_t_<unsigned_t_<5>, unsigned_t_<2>>> == 1, "");

                    add_step(v_<equal_to_t_<int_t_<1>, int_t_<1>>>, "");
                    add_step(!v_<not_equal_to_t_<int_t_<1>, int_t_<1>>>, "");
                    add_step(v_<greater_t_<int_t_<2>, int_t_<1>>>, "");
                    add_step(v_<less_t_<int_t_<1>, int_t_<2>>>, "");
                    add_step(v_<greater_equal_t_<int_t_<2>, int_t_<1>>>, "");
                    add_step(v_<less_equal_t_<int_t_<1>, int_t_<2>>>, "");
                    add_step(v_<greater_equal_t_<int_t_<1>, int_t_<1>>>, "");
                    add_step(v_<less_equal_t_<int_t_<1>, int_t_<1>>>, "");
                }
            };


            ///
            struct conditional_test:
                public brain::test::basic_test
            {
                virtual void test()
                {
                    add_step(v_<std::is_same<if_c<true, int, double>, int>>, "");
                    add_step(v_<std::is_same<if_c<false, int, double>, double>>, "");
                    add_step(v_<std::is_same<if_t<bool_t_<true>, int, double>, int>>, "");
                    add_step(v_<std::is_same<if_t<bool_t_<false>, int, double>, double>>, "");
                    add_step(v_<std::is_same<select_c<true, int, double>, int>>, "");
                    add_step(v_<std::is_same<select_c<false, int, double>, double>>, "");
                    add_step(v_<std::is_same<select_t<bool_t_<true>, int, double>, int>>, "");
                    add_step(v_<std::is_same<select_t<bool_t_<false>, int, double>, double>>, "");
                    add_step(v_<std::is_same<std::true_type, and_t<bool_t_<true>, bool_t_<true>>>>, "");
                    add_step(v_<std::is_same<std::false_type, and_t<bool_t_<false>, bool_t_<true>>>>, "");
                    add_step(v_<std::is_same<std::true_type, or_t<bool_t_<false>, bool_t_<true>>>>, "");
                    add_step(v_<std::is_same<std::false_type, or_t<bool_t_<false>, bool_t_<false>>>>, "");
                    add_step(!v_<not_t<bool_t_<true>>>, "");
                }
            };


            struct accumulate_test:
                public brain::test::basic_test
            {
                struct is_int
                {
                    template<typename type_t>
                    using return_ =
                        bool_t_<v_<std::is_same<type_t, int>>>;
                };

                using a_list = list<int, double, float, int>;

                virtual void test()
                {

                    add_step(v_<std::is_same<filter_t<a_list, is_int>, list<int, int>>>, "");
                }
            };


            struct runtime_test :
                public brain::test::basic_test
            {
                struct accum_test
                {
                    bool operator()(
                        bool && l,
                        bool && r)
                    {
                        return l or r;
                    }
                };

                template<typename type_t>
                struct func_test
                {
                    bool operator()()
                    {
                        return v_<std::is_same<type_t, int>>;
                    }
                };

                virtual void test()
                {
                    using a_list =
                        list<int, double, std::string>;

                    add_step(loop_rt<a_list, func_test, accum_test>()(),
                             "Test of loop_rt Runtime with true case");
                    add_step(!loop_rt<list<double, std::string>, func_test, accum_test>()(),
                             "Test of loop_rt Runtime with false case");
                }
            };
        }
    }


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



        /*        struct server_ptr_test :
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

                        using derived  = meta::inherit<object>;

                    public:
                        virtual void test()
                        {
                            server_ptr<object> server {new derived()};

                            server_ptr<object>::client clt(server);

                            if(clt)
                                logger<ROOT>::debug("clt est OK ", clt->foo());

                            else
                                logger<ROOT>::debug("clt est KO");

                            {
                                myptr server2 = fct::mv(server);
                                logger<ROOT>::debug(" serveur ", bool(server2));
                            }

                            if(clt)
                                logger<ROOT>::debug("clt est OK ", clt->foo());

                            else
                                logger<ROOT>::debug("clt est KO");
                        }
                };*/
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

        class component_obj :
            public object
        {
            public:
                property<object*, managing::unique> value;
        };

        class expression_obj :
            public object
        {
            public:
                property<std::string> name;
                property<component_obj> component;
        };

        class expressions_obj :
            public object
        {
            public:
                property<std::vector<expression_obj>> expressions;
        };

        using lql_expression_nt  = cpl::non_terminal<lqlconfig, LQL::expression>;
        using lql_expressions_nt = cpl::non_terminal<lqlconfig, LQL::expressions>;
        using lql_component_nt   = cpl::non_terminal<lqlconfig, LQL::component>;

        using lql_component   = cpl::production<lqlconfig, cpl::production_type::OR, lql_component_nt, lql_number_t, lql_string_t, lql_expressions_nt>;
        using lql_expression  = cpl::production<lqlconfig, cpl::production_type::AND, lql_expression_nt, lql_lbracket_t, lql_name_t, lql_component_nt, lql_rbracket_t>;
        using lql_expressions = cpl::production<lqlconfig, cpl::production_type::LIST, lql_expressions_nt, lql_expression_nt>;

        using grammar = cpl::grammar<lqlconfig, lql_expressions, lql_component, lql_expression, lql_expressions>;
        using token_maker = cpl::token_maker<lqlconfig, lql_name_t, lql_string_t, lql_ignored_t, lql_number_t, lql_lbracket_t, lql_rbracket_t>;
        using node_maker = cpl::node_maker<lqlconfig, grammar::root_production_type, grammar::productions_list>;
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
                    std::vector<cpl::token<lqlconfig>> tokens;
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
            virtual void test()
            {
                std::string filename = "resources/test/test.lql";
                lql_scanner scan;
                std::vector<cpl::token<lqlconfig>> tokens;
                cpl::scanner<lqlconfig>::build_tokens<token_maker>(filename, tokens);

                for(const auto & token : tokens)
                    logger<scanner_test>::debug((long) token.symbol_id(), ' ', token.value);

                node_maker::node_type node;
                cpl::parser<grammar>::build_node<node_maker>(tokens, node);
                cpl::node_displayer<lqlconfig>()(node);
            }

        };
        /*
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

                        }*/
    }
}

#endif
