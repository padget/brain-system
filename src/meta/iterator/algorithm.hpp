#ifndef __BRAIN_META_ITERATOR_ALGORITHM_HPP__
# define  __BRAIN_META_ITERATOR_ALGORITHM_HPP__

# include "forward.hpp"
# include "bidirectionnal.hpp"
# include "iteration.hpp"

namespace meta
{

    template < typename begin_t,
             typename nb_steps_t >
    using advance_ =
        fold_ <
            begin_t,
            next_<last_valid_<begin_t>>,
            begin_t,
            lazy::if_ <
                lazy::less_ <
                    lazy::distance_<begin_t, _1_>,
                    nb_steps_t > ,
                lazy::next_<_1_>,
                _0_ >>;


    template < typename begin_t,
             typename end_t,
             typename pred_r >
    using find_if_ = 
        fold_<
            begin_t, 
            end_t,
            end_t, 
            lazy::if_<
                bind_<pred_r, _0_>, 
                _0_,
                lazy::if_<
                    bind_<pred_r, _1_>, 
                    _1_, 
                    _0_
                >>>;
                
    template<typename begin_t, 
            typename end_t, 
            typename target_t>
    using find_ = 
        find_if_<
            begin_t, 
            end_t, 
            lambda<lazy::is_same_<target_t, lazy::item_<_0_>>> >;
    


    namespace lazy
    {
        template < typename begin_t,
                 typename nb_steps_t >
        struct advance_ :
                meta::function_<meta::advance_, begin_t, nb_steps_t>{};

        template < typename sequence_t,
                 typename pred_r >
        struct find_if_ :
                function_<meta::find_if_, sequence_t, pred_r> {};

        template < typename sequence_t,
                 typename type_t >
        struct find_ :
                function_<meta::find_, sequence_t, type_t> {}; 
    }
}

#endif
