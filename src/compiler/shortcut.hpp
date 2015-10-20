#ifndef COMPILER_SHORTCUT_HPP_INCLUDED
#define COMPILER_SHORTCUT_HPP_INCLUDED

#include "scanner.hpp"
#include "event.hpp"
#include "supports.hpp"
#include "parser.hpp"
#include "compiler.hpp"
#include "chain.hpp"

namespace brain
{
    namespace cpl
    {
        template<typename enum_t>
        class shortcut
        {
            public:

                template <enum_t ID, const char* reg>
                using declare_tni     = cpl::declare_t<enum_t, ID, reg, false>;

                template <enum_t ID, const char* reg>
                using declare_ti    = cpl::declare_t<enum_t, ID, reg, true>;

                using declare_empty = cpl::declare_empty<enum_t>;

                template <const char* reg>
                using declare_ignored = cpl::declare_ignored<enum_t, reg>;

                template <enum_t ID>
                using declare_ntni    = cpl::declare_nt<enum_t, ID, false>;

                template <enum_t ID>
                using declare_nti    = cpl::declare_nt<enum_t, ID, true>;

                template <enum_t id, typename ... defs_t>
                using or_rule       = cpl::or_rule<enum_t, id, defs_t...>;

                template <enum_t id, typename ... defs_t>
                using and_rule      = cpl::and_rule<enum_t, id, defs_t...>;

                template <enum_t id, typename ... defs_t>
                using list_rule     = cpl::list_rule<enum_t, id, defs_t...>;
                
                template<typename root_rule_t>
                using root_rule = cpl::root_rule<root_rule_t>;

                template<typename object_t, typename declare_t>
                using bind          = cpl::bind<object_t, declare_t>;

                template<typename ... binds_t>
                using binds         = cpl::binds<enum_t, binds_t... >;

                template <typename declare_ignored_t, typename root_t, typename ... rules_t>
                using grammar       = cpl::grammar<enum_t, declare_ignored_t, root_t, rules_t... >;

                template<typename grammar_t, typename binds_t>
                using executer      = cpl::executer<enum_t, grammar_t, binds_t>;

                template<typename grammar_t>
                using scanner       = cpl::scanner<enum_t, grammar_t>;

                template<typename grammar_t>
                using parser        = cpl::parser<enum_t, grammar_t>;

                template<typename converter_t>
                using chain         = cpl::chain<enum_t, converter_t>;
        };
    }
}

#endif // COMPILER_SHORTCUT_HPP_INCLUDED
