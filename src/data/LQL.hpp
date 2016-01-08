#ifndef __LQL_H__
#define __LQL_H__

#include <string>
#include "../compiler/shortcut.hpp"
#include "support.hpp"

#include <vector>
#include <memory>
#include <type_traits>

namespace brain
{
    namespace data
    {
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

        using lql_sc = brain::cpl::shortcut<LQL>;

        constexpr char lql_ignored_reg[] = "[ \\n\\r\\t]+";
        constexpr char lql_name_reg[] = "[a-zA-Z_]+";
        constexpr char lql_string_reg[] = "'.*'";
        constexpr char lql_number_reg[] = "[0-9]+(\\.{1}[0-9]+){0,1}";
        constexpr char lql_lbracket_reg[] = "\\(";
        constexpr char lql_rbracket_reg[] = "\\)";
        constexpr char lql_lbrace_reg[] = "\\[";
        constexpr char lql_rbrace_reg[] = "\\]";

        using lql_empty_t        = lql_sc::declare_empty;
        using lql_name_t         = lql_sc::declare_tni<LQL::name, lql_name_reg>;
        using lql_ignored_t      = lql_sc::declare_ti<LQL::ignored, lql_ignored_reg>;
        using lql_string_t       = lql_sc::declare_tni<LQL::string, lql_string_reg>;
        using lql_number_t       = lql_sc::declare_tni<LQL::number, lql_number_reg>;
        using lql_lbracket_t     = lql_sc::declare_ti<LQL::lbracket, lql_lbracket_reg>;
        using lql_rbracket_t     = lql_sc::declare_ti<LQL::rbracket, lql_rbracket_reg>;
        using lql_lbrace_t       = lql_sc::declare_ti<LQL::lbrace, lql_lbrace_reg>;
        using lql_rbrace_t       = lql_sc::declare_ti<LQL::rbrace, lql_rbrace_reg>;
        using lql_expression_nt  = lql_sc::declare_ntni<LQL::expression>;
        using lql_expressions_nt = lql_sc::declare_ntni<LQL::expressions>;
        using lql_component_nt       = lql_sc::declare_ntni<LQL::component>;

        using lql_component = lql_sc::or_rule<LQL::component, lql_number_t, lql_string_t, lql_expressions_nt>;
        using lql_expression = lql_sc::and_rule<LQL::expression, lql_lbracket_t, lql_name_t, lql_component_nt, lql_rbracket_t>;
        using lql_expressions = lql_sc::list_rule<LQL::expressions, lql_expression_nt>;

        using lql_root_rule = lql_sc::root_rule<lql_expression>;

        using lql_grammar = lql_sc::grammar <
                            lql_ignored_t,
                            lql_root_rule,
                            lql_expression,
                            lql_expressions,
                            lql_component >;

        using lql_binds = lql_sc::binds < lql_sc::bind<lql_number_t, number>,
              lql_sc::bind<lql_name_t, name>,
              lql_sc::bind<lql_string_t, string>,
              lql_sc::bind<lql_component_nt, data::component>,
              lql_sc::bind<lql_expression_nt, expression>,
              lql_sc::bind<lql_expressions_nt, expressions >>;

        using lql_scanner  = lql_sc::scanner<lql_grammar>;
        using lql_parser   = lql_sc::parser<lql_grammar>;
        using lql_executer = lql_sc::executer<lql_grammar, lql_binds>;

        class lql_converter
        {
            public:
                using arg_type = expressions;
                using res_type = std::shared_ptr<arg_type>;

            public:
                auto operator()(std::shared_ptr<arg_type> exps)
                { return exps; }
        };

        using lql_chain = lql_sc::chain<lql_converter>;
    }
}

#endif //__LQL_H__
