#ifndef PROPERTIES_HPP_INCLUDED
#define PROPERTIES_HPP_INCLUDED

// Le system de properties est un compilateur de <filename>.properties.
// Il est donc une utilisation directe du système compiler !

#include "../compiler/shortcut.hpp"
#include "../core/functionnal.hpp"

namespace brain
{
    namespace conf
    {
        enum class properties
        {
            properties,//0
            monomorphe,//1
            key,//2
            value,//3
            equals,//4
            empty,//5
            bullshit,//6
            ignored,//7
        };

        using properties_sc                   = brain::cpl::shortcut<properties>;

        constexpr char props_equals_reg[]     = "=";
        constexpr char props_key_reg[]        = "([a-zA-Z0-9_\\.])+";
        constexpr char props_value_reg[]      = "\".*\"";
        constexpr char props_ignored_reg[]    = "[ \\t\\n\\r]+";

        using props_ignored_t      = properties_sc::declare_ignored<props_ignored_reg>;
        using props_empty_t        = properties_sc::declare_empty;
        using props_equals_t       = properties_sc::declare_ti<properties::equals, props_equals_reg>;
        using props_key_t          = properties_sc::declare_tni<properties::key, props_key_reg>;
        using props_value_t        = properties_sc::declare_tni<properties::value, props_value_reg>;
        using props_property_nt    = properties_sc::declare_ntni<properties::monomorphe>;
        using props_properties_nt  = properties_sc::declare_ntni<properties::properties>;

        using props_property_rule       = properties_sc::and_rule<properties::monomorphe, props_key_t, props_equals_t, props_value_t>;
        using props_properties_rule     = properties_sc::list_rule<properties::properties, props_property_nt>;

        using props_root_rule = properties_sc::root_rule<props_properties_rule>;

        using props_grammar = properties_sc::grammar <
                              props_ignored_t,
                              props_root_rule,
                              props_property_rule,
                              props_properties_rule
                              >;

        class monomorphe :
            public cpl::semantic_object,
            public with_key<cpl::string>,
            public with_value<cpl::string>
        {
            public:
                BRAIN_ALL_DEFAULT(monomorphe)
            public:
                virtual void init(std::vector<cpl::semobject_sptr>& args)
                {
                    if(fct::equals(args.size(), 3u))
                    {
                        key(shared_conv<cpl::string>(args[0])->value());
                        value(shared_conv<cpl::string>(args[2])->value());
                    }
                }

                inline virtual operator std::string() noexcept
                { return concat(key().value(), "=", value().value()); }
        };

        using property_sptr = std::shared_ptr<monomorphe>;

        WITH_T(props)

        class properties_list :
            public cpl::semantic_object,
            public with_props<std::vector<property_sptr>>
        {
            public:
                BRAIN_ALL_DEFAULT(properties_list)
            public:
                virtual void init(std::vector<cpl::semobject_sptr>& args)
                {
                    for(auto & prop : args)
                        props().push_back(shared_conv<monomorphe>(prop));
                }
        };

        using properties_list_sptr = std::shared_ptr<properties_list>;

        class properties_converter
        {
            public:
                using res_type = std::map<std::string, std::string>;
                using arg_type = properties_list;

            public:
                auto operator()(std::shared_ptr<arg_type> props_list)
                {
                    res_type res;

                    for(const auto & prop : props_list->props())
                        res[prop->key().value()] = prop->value().value();

                    return res;
                }

        };


        using props_binds = properties_sc::binds <
                            properties_sc::bind<props_property_nt, monomorphe>,
                            properties_sc::bind<props_properties_nt, properties_list>
                            >;

        using props_scanner  = properties_sc::scanner<props_grammar>;
        using props_parser   = properties_sc::parser<props_grammar>;
        using props_compiler = properties_sc::executer<props_grammar, props_binds>;
        using props_chain    = properties_sc::chain<properties_converter>;

        class brainproperties :
            public props_chain,
            public singleton<brainproperties>
        {
            public:
                static std::string get(const std::string& key)
                {
                    static bool initialized {false};

                    if(not initialized)
                    {
                        refresh();
                        fct::assign(initialized, true);
                    }

                    return fct::equals(single().result().count(key), 1u) ?
                           std::regex_replace(single().result().at(key), std::regex("\""), "") :
                           "undefined";
                }

                static std::vector<std::string> getsplitted(
                    const std::string& key,
                    const std::string& regexdelim)
                {
                    std::string && value {get(key)};
                    std::vector<std::string> result;

                    if(not fct::empty(value))
                    {
                        std::regex rgx(regexdelim);
                        std::sregex_token_iterator iter(value.begin(), value.end(), rgx, -1);
                        result.assign(iter, std::sregex_token_iterator());
                    }

                    return result;
                }

                static void refresh()
                {
                    props_scanner scan;
                    props_parser pars;
                    props_compiler exec;

                    single().subbilink( {&scan, &pars, &exec});

                    single().init( {"resources/conf/brain.properties"});
                    single().compile();

                    single().subsystems().clear();
                }
        };
    }
}


#endif // PROPERTIES_HPP_INCLUDED
