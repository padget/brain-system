#ifndef __BRAIN_MACRO_HPP
#define __BRAIN_MACRO_HPP

namespace brain
{
// [REGION] : Macro
#define BRAIN_DEFAULT_CONSTRUCT(classname) \
    classname() = default;

#define BRAIN_DEFAULT_DESTRUCTOR(classname) \
    virtual ~classname() = default;

#define BRAIN_COPYABLE_DEFAULT_CONSTRUCT(classname) \
    classname(const classname&) = default;

#define BRAIN_COPYABLE_DEFAULT_ASSIGN(classname) \
    classname& operator= (const classname&) = default;

#define BRAIN_MOVEABLE_DEFAULT_CONSTRUCT(classname) \
    classname(classname&&) = default;

#define BRAIN_MOVEABLE_DEFAULT_ASSIGN(classname) \
    classname& operator= (classname&&) = default;

#define BRAIN_COPYABLE_DEFAULT(classname) \
    BRAIN_COPYABLE_DEFAULT_CONSTRUCT(classname) \
    BRAIN_COPYABLE_DEFAULT_ASSIGN(classname)

#define BRAIN_MOVEABLE_DEFAULT(classname) \
    BRAIN_MOVEABLE_DEFAULT_CONSTRUCT(classname) \
    BRAIN_MOVEABLE_DEFAULT_ASSIGN(classname)

#define BRAIN_ALL_DEFAULT(classname) \
    BRAIN_DEFAULT_CONSTRUCT(classname) \
    BRAIN_DEFAULT_DESTRUCTOR(classname) \
    BRAIN_COPYABLE_DEFAULT(classname) \
    BRAIN_MOVEABLE_DEFAULT(classname)

// DELETE

#define BRAIN_DELETE_CONSTRUCT(classname) \
    classname() = delete;

#define BRAIN_DELETE_DESTRUCTOR(classname) \
    virtual ~classname() = delete;

#define BRAIN_COPYABLE_DELETE_CONSTRUCT(classname) \
    classname(const classname&) = delete;

#define BRAIN_COPYABLE_DELETE_ASSIGN(classname) \
    classname& operator= (const classname&) = delete;

#define BRAIN_MOVEABLE_DELETE_CONSTRUCT(classname) \
    classname(classname&&) = delete;

#define BRAIN_MOVEABLE_DELETE_ASSIGN(classname) \
    classname& operator= (classname&&) = delete;

#define BRAIN_COPYABLE_DELETE(classname) \
    BRAIN_COPYABLE_DELETE_CONSTRUCT(classname) \
    BRAIN_COPYABLE_DELETE_ASSIGN(classname)

#define BRAIN_MOVEABLE_DELETE(classname) \
    BRAIN_MOVEABLE_DELETE_CONSTRUCT(classname) \
    BRAIN_MOVEABLE_DELETE_ASSIGN(classname)

#define BRAIN_ALL_DELETE(classname) \
    BRAIN_DELETE_CONSTRUCT(classname) \
    BRAIN_DELETE_DESTRUCTOR(classname) \
    BRAIN_COPYABLE_DELETE(classname) \
    BRAIN_MOVEABLE_DELETE(classname)

#define BRAIN_GETTER_CONST(propertyname, propertytype) \
    inline const propertytype& propertyname() const noexcept {return m_##propertyname;}

#define BRAIN_GETTER(propertyname, propertytype) \
    inline propertytype& propertyname() noexcept {return m_##propertyname;}

#define BRAIN_SETTER_LVAL(propertyname, propertytype) \
    inline void propertyname(const propertytype& val) noexcept {m_##propertyname = val;}

#define BRAIN_SETTER_RVAL(propertyname, propertytype) \
    inline void propertyname(propertytype&& val) noexcept {m_##propertyname = val;}

#define BRAIN_GETTER_SETTER(propertyname, propertytype) \
    BRAIN_GETTER(propertyname, propertytype) \
    BRAIN_GETTER_CONST(propertyname, propertytype) \
    BRAIN_SETTER_LVAL(propertyname, propertytype) \
    BRAIN_SETTER_RVAL(propertyname, propertytype) \
     
// WITH_
#define WITH_T(propertyname) \
    template<typename propertyname##_t> \
    class with_##propertyname \
    { \
            propertyname##_t m_##propertyname; \
            \
        public: \
            with_##propertyname() {} \
            ~with_##propertyname() {} \
            with_##propertyname(const propertyname##_t& propertyname):m_##propertyname(propertyname) {}\
            with_##propertyname(propertyname##_t&& propertyname):m_##propertyname(propertyname) {}\
        with_##propertyname(const with_##propertyname<propertyname##_t>& other) noexcept: m_##propertyname(other.m_##propertyname){}\
        with_##propertyname(with_##propertyname<propertyname##_t>&& other) noexcept: m_##propertyname(std::move(other.m_##propertyname)){}\
            with_##propertyname<propertyname##_t>& operator=(const with_##propertyname<propertyname##_t>& other) noexcept {if (this not_eq &other){m_##propertyname = other.m_##propertyname;} return *this;} \
            with_##propertyname<propertyname##_t>& operator=(with_##propertyname<propertyname##_t>&& other) noexcept {if (this not_eq &other){m_##propertyname = std::move(other.m_##propertyname);} return *this;} \
        public: \
            BRAIN_GETTER_CONST(propertyname, propertyname##_t) \
            BRAIN_GETTER(propertyname, propertyname##_t) \
            BRAIN_SETTER_RVAL(propertyname, propertyname##_t) \
            BRAIN_SETTER_LVAL(propertyname, propertyname##_t) \
        public:\
            using propertyname##_type =  propertyname##_t;\
    };

// WITH_
#define WITH_T_DEFAULTED(propertyname) \
    template<typename propertyname##_t, propertyname##_t def> \
    class with_##propertyname \
    { \
            propertyname##_t m_##propertyname = def; \
            \
        public: \
            with_##propertyname() {} \
            ~with_##propertyname() {} \
        with_##propertyname(const with_##propertyname<propertyname##_t, def>& other) noexcept: m_##propertyname(other.m_##propertyname){}\
        with_##propertyname(with_##propertyname<propertyname##_t, def>&& other) noexcept: m_##propertyname(std::move(other.m_##propertyname)){}\
            with_##propertyname<propertyname##_t, def>& operator=(const with_##propertyname<propertyname##_t, def>& other) noexcept {if (this not_eq &other){m_##propertyname = other.m_##propertyname;} return *this;} \
            with_##propertyname<propertyname##_t, def>& operator=(with_##propertyname<propertyname##_t, def>&& other) noexcept {if (this not_eq &other){m_##propertyname = std::move(other.m_##propertyname);} return *this;} \
        public: \
            BRAIN_GETTER_CONST(propertyname, propertyname##_t) \
            BRAIN_GETTER(propertyname, propertyname##_t) \
            BRAIN_SETTER_RVAL(propertyname, propertyname##_t) \
            BRAIN_SETTER_LVAL(propertyname, propertyname##_t) \
    };

    namespace to_suppress
    {
        WITH_T(value)
        WITH_T(key)
        WITH_T(name)
        WITH_T(type)
        WITH_T(message)
    }
}
#endif
