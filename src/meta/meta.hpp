#ifndef __META_BRAIN_HPP
#define __META_BRAIN_HPP


/*
#include "function.hpp"
#include "lambda.hpp"
#include "algorithm.hpp"
#include "list.hpp"
#include "map.hpp"
#include "runtime.hpp"
#include "standart.hpp"
#include "state.hpp"
#include "string.hpp"
*/
#include "core.hpp"
/// #include "sequence.hpp"
/// #include "lambda.hpp"
/// #include "view.hpp"

namespace brain
{
    /// Inspired by https://github.com/ericniebler/meta
    /// (author https://github.com/ericniebler)
    ///
    /// This library contains tow main principles :
    ///  - list<types_t...>
    ///  - meta function return_<>;
    ///
    /// The public metas functions (with return_)
    /// will present in ft namespace
    /// For all struct / using that returns 'type'
    /// an '_t_' will be added to end of its name.
    /// For all using that encapsulate t_<type_t>
    /// '_t' will be added to its name.
    /// Same things for metafunction with return_
    /// by adding '_r_'(and '_r')
    namespace meta
    {
        template<typename ... types_t>
        struct inherits:
            public types_t ...
        {
        };
    }
}


#endif
