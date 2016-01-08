#ifndef REGISTRY_HPP_INCLUDED
#define REGISTRY_HPP_INCLUDED

#include "../core.h"
#include "../compiler/shortcut.hpp"
#include "../lang/language.hpp"

namespace brain
{
    namespace reg
    {
        enum class registry
        {
            declaration,//0
            connection,//1
            simpleconnection,//2
            dualconnection,//3
            line,//4
            lines,//5
            arrow,//6
            barrow,//7
            name,//8
            empty,//9
            bullshit,//10
            ignored,//11
            is,//12
            init,//13
            running,//14
            args//15
        };

        using registry_sc                 = brain::compiler::shortcut<registry>;

        constexpr char reg_arrow_reg[]              = "\\->";
        constexpr char reg_barrow_reg[]             = "<\\->";
        constexpr char reg_name_reg[]               = "([a-zA-Z0-9])+";
        constexpr char reg_ignored_reg[]            = "[ \\t\\n]+";
        constexpr char reg_is_reg[]                 = ":";
        constexpr char reg_init_reg[]               = "=";
        constexpr char reg_args_reg[]               = "\".*\"";


        using reg_arrow_t                 = registry_sc::declare_t<registry::arrow, reg_arrow_reg>;
        using reg_barrow_t                = registry_sc::declare_t<registry::barrow, reg_barrow_reg>;
        using reg_ignored_t               = registry_sc::declare_t<registry::ignored, reg_ignored_reg>;
        using reg_name_t                  = registry_sc::declare_t<registry::name, reg_name_reg>;
        using reg_connection_nt           = registry_sc::declare_nt<registry::connection>;
        using reg_simpleconnection_nt     = registry_sc::declare_nt<registry::simpleconnection>;
        using reg_dualconnection_nt       = registry_sc::declare_nt<registry::dualconnection>;
        using reg_declaration_nt          = registry_sc::declare_nt<registry::declaration>;
        using reg_empty_t                 = registry_sc::declare_empty<registry::empty>;
        using reg_is_t                    = registry_sc::declare_t<registry::is, reg_is_reg>;
        using reg_init_t                  = registry_sc::declare_t<registry::init, reg_init_reg>;
        using reg_args_t                  = registry_sc::declare_t<registry::args, reg_args_reg>;
        using reg_running_nt              = registry_sc::declare_nt<registry::running>;
        using reg_line_nt                 = registry_sc::declare_nt<registry::line>;
        using reg_lines_nt                = registry_sc::declare_nt<registry::lines>;


        using reg_connection              = registry_sc::or_rule<reg_connection_nt, reg_simpleconnection_nt, reg_dualconnection_nt>;
        using reg_simpleconnection        = registry_sc::and_rule<reg_simpleconnection_nt, reg_name_t, reg_arrow_t, reg_name_t>;
        using reg_dualconnection          = registry_sc::and_rule<reg_dualconnection_nt, reg_name_t, reg_barrow_t, reg_name_t>;
        using reg_declaration             = registry_sc::and_rule<reg_declaration_nt, reg_name_t, reg_is_t, reg_name_t>;
        using reg_running                 = registry_sc::and_rule<reg_running_nt, reg_name_t, reg_init_t, reg_args_t>;

        using reg_line                    = registry_sc::or_rule<reg_line_nt, reg_declaration_nt, reg_connection_nt, reg_running_nt>;
        using reg_lines                   = registry_sc::list_rule<reg_lines_nt, reg_line_nt>;


        using reg_grammar                 = registry_sc::grammar<reg_lines_nt, registry::ignored, reg_ignored_reg, registry::bullshit, registry::empty,
              reg_connection,
              reg_simpleconnection,
              reg_dualconnection,
              reg_declaration,
              reg_line,
              reg_running,
              reg_lines
              >;

        WITH_T(left)
        WITH_T(right)
        WITH_T(op)

        class instruction :
            public object,
            public with_left<std::string>,
            public with_right<std::string>,
            public with_op<std::string>
        {
            public:
                BRAIN_ALL_DEFAULT(instruction)

            public:
                inline virtual operator std::string() const noexcept
                { return left() + op() + right(); }
        };

        inline ostream& operator<< (ostream& out, const instruction& inst)
        {
            out << (string) inst;

            return out;
        }

        object_sptr build_instruction(const std::vector<object_sptr>& args)
        {
            object_sptr inst(new instruction());

            if(args.size() == 3)
            {
                shared_conv<instruction>(inst)->left((string)(*(shared_conv<native_string>(args[0]))));
                shared_conv<instruction>(inst)->right((string)(*(shared_conv<native_string>(args[2]))));
                shared_conv<instruction>(inst)->op((string)(*(shared_conv<native_string>(args[1]))));
            }

            return inst;
        }

        object_sptr running_cb(const vector<object_sptr>& args)
        { return build_instruction(args); }

        object_sptr connection_cb(const vector<object_sptr>& args)
        { return args[0]; }

        object_sptr simpleconnection_cb(const vector<object_sptr>& args)
        { return build_instruction(args); }

        object_sptr dualconnection_cb(const vector<object_sptr>& args)
        { return build_instruction(args); }

        object_sptr line_cb(const vector<object_sptr>& args)
        { return args[0]; }

        object_sptr declaration_cb(const vector<object_sptr>& args)
        { return build_instruction(args); }

        object_sptr lines_cb(const vector<object_sptr>& args)
        { return compiler::forward_args<instruction>(args); }

        using reg_binds = registry_sc::binds <
                registry_sc::bind<simpleconnection_cb, reg_simpleconnection_nt>,
                registry_sc::bind<connection_cb, reg_connection_nt>,
                registry_sc::bind<dualconnection_cb, reg_dualconnection_nt>,
                registry_sc::bind<declaration_cb, reg_declaration_nt>,
                registry_sc::bind<line_cb, reg_line_nt>,
                registry_sc::bind<lines_cb, reg_lines_nt>,
                registry_sc::bind<running_cb, reg_running_nt>
                >;


        using reg_scanner = registry_sc::scanner<reg_ignored_reg, reg_grammar>;
        using reg_parser = registry_sc::parser<reg_grammar>;
        using reg_executer = registry_sc::compiler<reg_grammar, reg_binds>;

        using instruction_sptr = std::shared_ptr<instruction>;

        auto reg_converter(object_sptr res)
        {
            std::vector<instruction_sptr> insts;
            auto insts_res = shared_conv<native_vector<std::shared_ptr<instruction>>>(res);

            for(const auto& inst : insts_res->value())
            { insts.push_back(shared_conv<instruction>(inst)); }

            return insts;
        }


        using reg_chain = registry_sc::chain<std::vector<instruction_sptr>, reg_converter>;
    }
}

#endif // REGISTRY_HPP_INCLUDED
