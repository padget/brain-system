#ifndef TESTCORE_HPP
#define TESTCORE_HPP

#include "../../core/core.hpp"

//#include "../../compiler/supports.hpp"
//#include "../../compiler/parser.hpp"
//#include "../../compiler/scanner.hpp"
//#include "../../compiler/utils.hpp"

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

                virtual bool test()
                {
                    static_assert(v_<std::is_same<t_<a_type>, a_type>>, "");
                    static_assert(v_<a_type> == 1, "");
                    static_assert(v_<std::is_same<vt_<a_type>, const int>>, "");
                    static_assert(size_<a_type> == 12, "");
                    static_assert(v_<std::is_same<return_<a_type, int>, a_type>>, "");
                    static_assert(v_<std::is_same<r_<a_type, int>, a_type>>, "");

                    return v_<std::true_type>;
                }
            };


            /// Unitary test for
            /// literal meta features
            struct literal_test:
                public brain::test::basic_test
            {
                virtual bool test()
                {
                    static_assert(v_<bool_t_<true>> == true, "");
                    static_assert(v_<short_t_<1>> == 1, "");
                    static_assert(v_<ushort_t_<1>> == 1, "");
                    static_assert(v_ < char_t_ < 'c' >> == 'c', "");
                    static_assert(v_<int_t_<1>> == 1, "");
                    static_assert(v_<long_t_<1>> == 1, "");
                    static_assert(v_<longlong_t_<1>> == 1, "");
                    static_assert(v_<unsigned_t_<1>> == 1, "");
                    static_assert(v_<unsignedl_t_<1>> == 1, "");
                    static_assert(v_<unsignedll_t_<1>> == 1, "");
                    static_assert(v_<size_t_<1>> == 1, "");

                    return v_<std::true_type>;
                }
            };


            /// Unitary test for
            /// const keyword meta
            /// features
            struct constkw_test:
                public brain::test::basic_test
            {
                virtual bool test()
                {
                    static_assert(v_<sizeof_t_<int>> == sizeof(int), "");
                    static_assert(v_<sizeof_pack_t_<int, double, int>> == 3, "");
                    static_assert(v_<alignof_t_<int>> == alignof(int), "");
                    return v_<std::true_type>;
                }
            };


            /// Unitary test for
            /// pack meta features
            struct pack_test:
                public brain::test::basic_test
            {
                using a_list = list<int, float, double>;

                virtual bool test()
                {
                    static_assert(size_<a_list> == v_<sizeof_pack_t_<int, float, double>>, "");
                    static_assert(v_<std::is_same<t_<a_list>, a_list>>, "");
                    static_assert(v_<std::is_same<front_t<a_list>, int>>, "");
                    static_assert(v_<std::is_same<back_t<a_list>, double>>, "");
                    static_assert(v_<std::is_same<concat_t<list<int>, list<float, double>, list<>>, list<int, float, double>>>, "");
                    static_assert(v_<std::is_same<at_t<unsigned_t<2>, a_list>, double>>, "");
                    static_assert(v_<std::is_same<repeat_t<unsigned_t<3>, int>, list<int, int, int>>>, "");
                    static_assert(v_<std::is_same<to_list_t<std::tuple<int, int>>, list<int, int>>>, "");
                    return v_<std::true_type>;
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

                virtual bool test()
                {
                    /// TODO Unitary for compose
                    static_assert(v_<std::is_same<always_r<void>, void>> , "");
                    static_assert(v_<has_type_t<a_type>>, "");
                    static_assert(!v_<has_type_t<another_type>>, "");
                    static_assert(v_<has_return_t<a_type>>, "");
                    static_assert(!v_<has_return_t<another_type>>, "");
                    static_assert(v_<is_meta_function_t<a_type>>, "");
                    static_assert(!v_<is_meta_function_t<another_type>>, "");
                    /// TODO Unitary for bind_front
                    /// TODO Unitary for bind_back
                    static_assert(v_<std::is_same<expand_t<a_type, list<int, double>>, int>>, "");

                    static_assert(v_<std::is_same<push_back_t<float, a_list>, list<int, double, float>>>, "");
                    static_assert(v_<std::is_same<push_front_t<float, a_list>, list<float, int, double>>>, "");
                    static_assert(v_<std::is_same<pop_back_t<a_list>, list<int>>>, "");
                    static_assert(v_<std::is_same<pop_front_t<a_list>, list<double>>>, "");

                    return v_<std::true_type>;
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

                virtual bool test()
                {
                    static_assert(v_<std::is_same<t_<defer<a_type, int, double>>, void>>, "");
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
                {};

                virtual bool test()
                {
                    static_assert(v_<std::is_same<r_<quote_r_<a_type>, int, float, double>, a_type<int, float, double>>> , "");
                    return v_<std::true_type>;
                }
            };


            /// Unitary test for
            /// math features
            struct math_test:
                public brain::test::basic_test
            {
                virtual bool test()
                {
                    static_assert(v_<inc_t_<unsigned_t_<0>>> == 1, "");
                    static_assert(v_<dec_t_<unsigned_t_<1>>> == 0, "");
                    static_assert(v_<plus_t<unsigned_t_<1>, unsigned_t_<1>>> == 2, "");
                    static_assert(v_<minus_t_<unsigned_t_<1>, unsigned_t_<1>>> == 0, "");
                    static_assert(v_<multiplies_t_<unsigned_t_<2>, unsigned_t_<2>>> == 4, "");
                    static_assert(v_<divides_t_<unsigned_t_<4>, unsigned_t_<2>>> == 2, "");
                    static_assert(v_<negate_t_<int_t_<1>>> == -1, "");
                    static_assert(v_<modulus_t_<unsigned_t_<5>, unsigned_t_<2>>> == 1, "");

                    static_assert(v_<equal_to_t_<int_t_<1>, int_t_<1>>>, "");
                    static_assert(!v_<not_equal_to_t_<int_t_<1>, int_t_<1>>>, "");
                    static_assert(v_<greater_t_<int_t_<2>, int_t_<1>>>, "");
                    static_assert(v_<less_t_<int_t_<1>, int_t_<2>>>, "");
                    static_assert(v_<greater_equal_t_<int_t_<2>, int_t_<1>>>, "");
                    static_assert(v_<less_equal_t_<int_t_<1>, int_t_<2>>>, "");
                    static_assert(v_<greater_equal_t_<int_t_<1>, int_t_<1>>>, "");
                    static_assert(v_<less_equal_t_<int_t_<1>, int_t_<1>>>, "");

                    /// TODO Unitary test for bit operators
                    return v_<std::true_type>;
                }
            };


            ///
            struct conditional_test:
                public brain::test::basic_test
            {
                virtual bool test()
                {
                    static_assert(v_<std::is_same<if_c<true, int, double>, int>>, "");
                    static_assert(v_<std::is_same<if_c<false, int, double>, double>>, "");
                    static_assert(v_<std::is_same<if_t<bool_t_<true>, int, double>, int>>, "");
                    static_assert(v_<std::is_same<if_t<bool_t_<false>, int, double>, double>>, "");
                    static_assert(v_<std::is_same<select_c<true, int, double>, int>>, "");
                    static_assert(v_<std::is_same<select_c<false, int, double>, double>>, "");
                    static_assert(v_<std::is_same<select_t<bool_t_<true>, int, double>, int>>, "");
                    static_assert(v_<std::is_same<select_t<bool_t_<false>, int, double>, double>>, "");
                    static_assert(v_<std::is_same<std::true_type, and_t<bool_t_<true>, bool_t_<true>>>>, "");
                    static_assert(v_<std::is_same<std::false_type, and_t<bool_t_<false>, bool_t_<true>>>>, "");
                    static_assert(v_<std::is_same<std::true_type, or_t<bool_t_<false>, bool_t_<true>>>>, "");
                    static_assert(v_<std::is_same<std::false_type, or_t<bool_t_<false>, bool_t_<false>>>>, "");
                    static_assert(!v_<not_t<bool_t_<true>>>, "");
                    return v_<std::true_type>;
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

                virtual bool test()
                {

                    static_assert(v_<std::is_same<filter_t<a_list, is_int>, list<int, int>>>, "");
                    return v_<std::true_type>;
                }
            };
        }
    }


    namespace test
    {
        struct object_test:
            public basic_test
        {
            bool virtual test()
            {
                bool res = true;

                object o1;
                object o2 {o1};

                /// o1.id and o2.id must
                /// be different because
                /// automatic increment
                /// of object::s_id on
                /// copy constructor
                res &= (o1.id != o2.id);

                object o3;

                /// o3.id must be different
                /// from the other ox.id due
                /// to the auto increment of
                /// s_id in default constructor
                res &= (o1.id != o3.id && o2.id != o3.id);

                o3 = o1;

                /// o1.id and o3.id must
                /// must be different
                /// because of auto increment
                /// into copy assignement
                res &= (o1.id != o3.id);

                object o5;
                auto o5_id = o5.id;

                object o6 {std::move(o5)};

                /// o5.id must be equal to
                /// o6.id because of the
                /// copy of id in move
                /// assignement
                res &= o5_id == o6.id;


                auto o6_id = o6.id;
                object o7 {std::move(o6)};

                /// o7.id must be equal to
                /// o6_id because of the
                /// copy of id in move
                /// constructor
                res &= o7.id == o6_id;

                return res;
            }
        };
        

        struct reference_test :
            public basic_test
        {
            virtual bool test()
            {
                bool res = true;

                object o1;
                reference<object> ro1 {o1};
                
                /// The both id must be
                /// equal because of 
                /// the reference ro1 is
                /// on o1 (no copy).
                res &= (brain::get(ro1).id == o1.id);
                
                object o2;
                brain::set(ro1, o2);
                
                /// 
                res &= (brain::get(ro1).id == o2.id);
                
                object o3;
                brain::set(ro1, std::move(o3));
                
                /// 
                res &= (brain::get(ro1).id == o3.id);
                
                
                return res;
            }
        };


        struct property_test :
            public basic_test
        {
                struct a_type
                {
                    monomorphe<int> an_int = default_v<int>;
                };


                template<int _max>
                struct less_politic:
                    public brain::politic<int>
                {
                    virtual bool operator()(
                        const int& value) const
                    {
                        return value < _max ?
                               true :
                               throw invalid_data("less politic");
                    }

                    virtual bool operator()(
                        int && value) const
                    {
                        return value < _max ?
                               true :
                               throw invalid_data("less politic");
                    }
                };

                template<int _max>
                using less_p = less_politic<_max>;

                struct another_type
                {
                    monomorphe<int, less_p<12>> an_int = default_v<int>;
                };

                struct another_type2
                {
                    monomorphe<std::shared_ptr<int>> an_int = std::make_shared<int>(default_v<int>);
                };


                virtual bool test()
                {
                    auto res = true;

                    try
                    {
                        a_type instance;
                        res &= instance.an_int == default_v<int>;
                        res &= instance.an_int + 1 == default_v<int> + 1;
                        res &= (instance.an_int += 1) == default_v<int> + 1;
                        res &= instance.an_int == default_v<int> + 1;

                        another_type instance2;
                        res &= instance2.an_int == default_v<int>;
                        int an = 11;
                        instance2.an_int = (long)an;
                        res &= instance2.an_int == 11;
                        res &= instance2.an_int + instance2.an_int == 22;
                        res &= (instance.an_int = instance2.an_int) == 11;
                        res &= instance.an_int == 11;
                        std::cout << static_cast<int>(instance2.an_int) << std::endl;

                        another_type2 instance3;
                        std::cout << instance3.an_int << std::endl;
                    }

                    catch(std::exception& ex)
                    {
                        std::cout << ex.what() << std::endl;
                        res = meta::v_<std::false_type>;
                    }


                    {
                        int i = 13;
                        reference<int> a_ref;
                        a_ref = i;
                    } /// must display the log of destructor

                    {

                        int i = 12;
                        reference<int> a_ref, a_ref2 {i};
                        std::cout << a_ref2 << std::endl;

                        a_ref = i;
                        std::cout << a_ref << std::endl;
                        int i2 = 25;
                        a_ref2 = i2;
                        std::cout << a_ref2 << std::endl;
                        a_ref = a_ref2;
                        std::cout << a_ref << std::endl;
                        a_ref = 4;
                        std::cout << a_ref << std::endl;

                        using object_derived =
                            meta::inherit<object>;

                        object_derived d;

                        reference<object> a_ref3 = d;
                        std::cout << a_ref3.get().id
                                  << std::endl;

                        reference<object> a_ref4;

                        object_derived d2;
                        a_ref4 = d2;
                        std::cout << a_ref4.get().id
                                  << std::endl;

                        a_ref3 = a_ref4;
                        std::cout << a_ref3.get().id
                                  << std::endl;
                    }

                    {
                        object obj1;
                        std::cout << "obj1 "
                                  << obj1.id
                                  << std::endl;

                        component<object> a_comp(obj1);

                        std::cout << "a_comp "
                                  << a_comp.get().id
                                  << std::endl;

                    }

                    return res;
                }
        };

    }



    /*  namespace test
      {

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
          };*/

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

    }*/
}

#endif
