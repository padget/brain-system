#ifndef PROPERTIES_HPP_INCLUDED
#define PROPERTIES_HPP_INCLUDED

// Le system de properties est un compilateur de <filename>.properties.
// Il est donc une utilisation directe du système compiler !

#include "../compiler/supports.hpp"

namespace brain
{
    namespace conf
    {
        enum class properties
        {
            empty, ///0
            bullshit, ///1
            ignored, ///2
            properties, ///3
            property, ///4
            key, ///5
            value, ///6
            equals ///7
        };

        using propsconfig =
            cpl::config<properties, char>;

        extern constexpr meta::string
        props_equals_reg {"="};

        extern constexpr meta::string
        props_key_reg {"([a-zA-Z0-9_\\.])+"};

        extern constexpr meta::string
        props_value_reg {"\".*\""};

        extern constexpr meta::string
        props_ignored_reg {"[ \\t\\n\\r]+"};

        using props_ignored_t      = cpl::terminal<propsconfig, properties::ignored, props_ignored_reg>;
        using props_equals_t       = cpl::terminal<propsconfig, properties::equals, props_equals_reg>;
        using props_key_t          = cpl::terminal<propsconfig, properties::key, props_key_reg>;
        using props_value_t        = cpl::terminal<propsconfig, properties::value, props_value_reg>;

        using props_property_nt   = cpl::non_terminal<propsconfig, properties::property>;
        using props_properties_nt = cpl::non_terminal<propsconfig, properties::properties>;

        using props_property_rule   = cpl::production<cpl::production_type::AND, props_property_nt, props_key_t, props_equals_t, props_value_t>;
        using props_properties_rule = cpl::production<cpl::production_type::LIST, props_properties_nt, props_property_nt>;

        using props_grammar = cpl::grammar <
                              props_properties_rule,
                              props_property_rule,
                              props_properties_rule >;

        class props_property :
            public object
        {
            public:
                property<std::string> key;
                property<std::string> value;
        };


        class props_properties :
            public object
        {
            public:
                property<std::vector<props_property>> props;
        };





        class brainproperties :
            public singleton<brainproperties>
        {
            public:
                /*  static std::string get(const std::string& key)
                  {
                      static bool initialized {false};

                      if(not initialized)
                      {
                          refresh();
                         initialized = true;
                      }

                      return single().result().count(key) == 1u ?
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
                  }*/
        };
    }
}


#endif // PROPERTIES_HPP_INCLUDED
