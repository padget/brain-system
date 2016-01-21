#ifndef __BRAIN_META_STRING_HPP__
# define __BRAIN_META_STRING_HPP__

#include <type_traits>
#include <stdexcept>

namespace brain
{
    namespace meta
    {
        /// /////////////////// ///
        /// Compile time string ///
        /// /////////////////// ///


        /// Compile time string
        /// definition
        template<typename char_t>
        class basic_string
        {
            private:
                /// Inner value
                const char_t* const m_value;


                /// Size of the m_value
                const std::size_t m_size;


            public:
                /// Constructor taking
                /// a literal string
                template<std::size_t N>
                constexpr basic_string(
                    const char_t(&a)[N]) :
                    m_value(a),
                    m_size(N - 1)
                {
                }

                /// Overload of
                /// operator[]
                constexpr char_t operator[](
                    std::size_t n)
                {
                    return n < m_size ?
                           m_value[n] :
                           throw std::out_of_range("");
                }


                /// Returns the size
                /// of m_value;
                constexpr std::size_t size()
                {
                    return m_size;
                }


                /// Returns the
                /// m_value pointer
                constexpr const char_t * const get() const
                {
                    return m_value;
                }
        };


        /// String alias for
        /// basic_string<char>
        using string =
            basic_string<char>;


        /// WString alias for
        /// basic_string<wchar_t>
        using wstring =
            basic_string<wchar_t>;


        /// WString alias for
        /// basic_string<char16_t>
        using u16string	 =
            basic_string<char16_t>;


        /// WString alias for
        /// basic_string<char32_t>
        using u32string =
            basic_string<char32_t>;
    }
}

#endif
