#ifndef __BRAIN_META_MACRO_HPP__
# define __BRAIN_META_MACRO_HPP__



/// Macro defining the
/// way to dermine if
/// a class has name
/// inner its definition

#  define has_(name) \
    template < typename, \
    typename = void > \
    struct has_##name##_member : std::false_type \
    { \
    }; \
    \
    template <typename type_t> \
    struct has_##name##_member < type_t, \
            void_ < typename \
            type_t::name > > : std::true_type\
    { \
    };

#  define access_(name) \
    template<typename type_t> \
    using name##_ = \
                    typename type_t::name;

#  define lazy_(name) \
    namespace lazy \
    { \
        template<typename type_t> \
        struct has_##name##_member : \
                                    function_<meta::has_##name##_member, type_t>{}; \
        \
        template<typename type_t> \
        struct name##_ : \
                        function_<meta::name##_, type_t>{}; \
    }


#  define member_(name) \
    has_(name) \
    access_(name) \
    lazy_(name)

#endif
