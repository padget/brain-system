#ifndef LANGUAGE_HPP_INCLUDED
#define LANGUAGE_HPP_INCLUDED

#include "../configuration/properties.hpp"
#include "../core.h"

namespace brain
{
    namespace lang
    {
        class language:
            public singleton<language>
        {
                using string_map = std::map<std::string, std::string>;
                using lang_map = std::map<std::string, string_map>;
                nat::property<lang_map> m_langs;

            public:
                language() = default;
                language(const language&) = default;
                language(language &&) = default;
                virtual ~language() = default;

            public:
                virtual language& operator=(const language&) = default;
                virtual language& operator=(language &&) = default;

            public:
                const auto& langs() const
                { return m_langs; }

            public:
                static std::string get(const std::string& key)
                {
                    static bool initialized = false;

                    if(fct::logic_not(initialized))
                    {
                        refresh();
                        fct::assign(initialized, true);
                    }

                    return std::regex_replace(single().m_langs[conf::brainproperties::get("default.lang")][key], std::regex("\""), "");
                }

                static void refresh()
                {
                    conf::props_scanner scan;
                    conf::props_parser pars;
                    conf::props_compiler comp;
                    conf::props_chain ch;

                    ch.subbilink( {&scan, &pars, &comp});

                    auto && langs_to_explore = conf::brainproperties::getsplitted("default.lang.list", ",");

                    for(const auto & lang_to_explore : langs_to_explore)
                    {
                        ch.init( {concat("resources/lang/lang.", lang_to_explore, ".properties")});
                        fct::assign(single().m_langs[lang_to_explore],
                                    std::map<std::string, std::string>());
                        ch.compile();
                        const auto& props = ch.result();

                        for(const auto & prop : props)
                            single().m_langs.at(lang_to_explore)[prop.first] = prop.second;

                    }
                }

                static void display_langs()
                {
                    for(const auto & lang : single().langs())
                    {
                        logger<language>::trace("Lang : ", lang.first);

                        for(const auto & str : lang.second)
                            logger<language>::trace("   |-- ", str.first, " = ", str.second);
                    }
                }

                static bool check()
                {
                    bool res = true;
                    std::set<std::string> strs;

                    for(const auto & lang : single().langs())
                        for(const auto & str : lang.second)
                            strs.insert(str.first);

                    for(const auto & lang : single().langs())
                        for(const auto & str : strs)
                            if(fct::equals(lang.second.count(str), 0u))
                            {
                                fct::assign(res, true);
                                logger<language>::warn("La traduction ",
                                                       str,
                                                       " n'est pas disponible pour la langue ",
                                                       lang.first);
                            }

                    return res;
                }
        };
    }
}
#endif // LANGUAGE_HPP_INCLUDED
