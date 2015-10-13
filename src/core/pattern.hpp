#ifndef __BRAIN__PATTERN_HPP
#define __BRAIN__PATTERN_HPP

namespace brain
{
    namespace pattern
    {
        /**
         * @class stringable
         * @author bmathieu
         * @date 18/09/2015
         * @file pattern.hpp
         * @brief Enable to a class to be convertible to std::string
         */
        class stringable
        {
            public:
                virtual ~stringable() noexcept = default;
                virtual operator std::string() noexcept = 0;
        };

        template <typename t>
        inline std::ostream& append(std::ostream& out, t && o) noexcept
        { return out << o; }

        template <typename t, typename ... T>
        inline std::ostream& append(std::ostream& out, t && o, T && ... os) noexcept
        {
            out << o;
            return append(out, os...);
        }

        template <typename str>
        std::string concat(str && ch1)
        {
            std::stringstream stream;
            stream << ch1;
            return stream.str();
        }

        template <typename str1, typename ... str2>
        std::string concat(str1 && ch1, str2 && ... ch2)
        { return concat(ch1) + concat(ch2...); }



        /**
         * @class singleton
         * @author bmathieu
         * @date 18/09/2015
         * @file pattern.hpp
         * @brief Enable to generate a singleton.
         *
         * Warning : Don't forbidden to instanciate
         * other than the singleton.
         */
        template <typename T>
        class singleton
        {
            public:
                static T& single() noexcept
                {
                    static T obj;
                    return obj;
                }
        };

        template<typename type_t>
        class is_singleton :
            public std::integral_constant < bool,
            std::is_base_of<pattern::singleton<type_t>, type_t>::value >
        {
        };

        template<typename single_t>
        const auto& single = single_t::single();

        /**
         * @class cloneable
         * @author bmathieu
         * @date 18/09/2015
         * @file pattern.hpp
         * @brief Enable the clone method for a class
         */
        template<typename type_t>
        class cloneable
        {
                using type_ptr = std::unique_ptr<type_t>;
            public:
                virtual type_ptr clone() = 0;
        };

        template<typename type_t>
        using prototype = cloneable<type_t>;

        template<typename type_t>
        class is_clonable :
            public std::integral_constant < bool,
            std::is_base_of<pattern::cloneable<type_t>, type_t>::value >
        {
        };

    }
}
#endif
