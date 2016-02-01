#ifndef __BRAIN_META_SEQUENCE_MAP_HPP__
# define __BRAIN_META_SEQUENCE_MAP_HPP__

namespace meta
{
    template < typename key_t,
             typename value_t >
    struct pair:
            list<key_t, value_t>
    {
        using key = key_t;
        using value = value_t;
    };

    template <typename ... pairs_t>
    struct map:
            list<pairs_t...>
    {
    };
}

#endif
