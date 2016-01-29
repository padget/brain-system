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
            
            
    template<typename begin_t, 
            typename end_t, 
            typename pred_r>
    using count_if_ = 
        fold_< 
            begin_t, 
            end_t, 
            unsigned_<0>, 
            lazy::if_<
                bind_<pred_r, _1_>,
                lazy::inc_<_0_>, 
                _0_
            >>;
            
    template<typename begin_t, 
            typename end_t, 
            typename target_t>
    using count_ = 
        count_if_<
            begin_t, 
            end_t, 
            lambda<lazy::is_same_<target_t, lazy::item_<_0_>>>>;
            
    template<typename begin_t,
            typename end_t, 
            typename target_t>
    using contains_ = 
        greater_<count_<begin_t, end_t, target_t>, unsigned_<0>>;
        
    
    template<typename begin_t, 
            typename end_t, 
            typename func_r>
    using transform_ = 
        fold_<
            begin_t, 
            end_t, 
            pack<>, 
            lambda<lazy::push_back_<_0_, bind_<func_r, _1_>>>>;
        
        
    template<typename begin_t, 
            typename end_t,
            typename new_t, 
            typename pred_r>
    using replace_if_ =
        transform_<
            begin_t, 
            end_t, 
            lazy::if_<
                bind_<pred_r, _1_>, 
                new_t, 
                _1_>>;
                
                
    template<typename begin_t, 
            typename end_t,
            typename old_t, 
            typename new_t>
    using replace_ =
        replace_if_<
            begin_t, 
            end_t,
            new_t, 
            lambda<lazy::is_same_<old_t, lazy::item_<_1_>>>>;
            
    template<typename begin_t, 
            typename end_t, 
            typename pred_r>
    using remove_if_ =
        fold_<
            begin_t, 
            end_t, 
            pack<>, 
            lazy::if_<
                bind_<pred_r, _1_>, 
                _0_,
                lazy::push_back_<_0_, _1_>>>;
    

    template<typename begin_t, 
            typename end_t, 
            typename deleted_t>
    using remove_ = 
        remove_if_<
            begin_t, 
            end_t, 
            lambda<lazy::is_same_<deleted_t, _0_>>>;

    namespace lazy
    {
        template < typename begin_t,
                 typename nb_steps_t >
        struct advance_ :
                meta::function_<meta::advance_, begin_t, nb_steps_t>{};

        template < typename begin_t, 
                 typename end_t,
                 typename pred_r >
        struct find_if_ :
                meta::function_<meta::find_if_, begin_t, end_t, pred_r> {};

        template < typename begin_t, 
                 typename end_t,
                 typename type_t >
        struct find_ :
                meta::function_<meta::find_, begin_t, end_t, type_t> {};

        template<typename begin_t, 
                typename end_t, 
                typename pred_r>
        struct count_if_ :
                meta::function_<meta::count_if_, begin_t, end_t, pred_r>{};
                
         template<typename begin_t, 
                typename end_t, 
                typename target_t>
        struct count_ :
                meta::function_<meta::count_, begin_t, end_t, target_t>{};
                
         template<typename begin_t,
            typename end_t, 
            typename target_t>
        struct contains :
                meta::function_<meta::contains_, begin_t, end_t, target_t>{};
                
        template<typename begin_t, 
            typename end_t, 
            typename func_r>
        struct transform_ : 
                meta::function_<meta::transform_, begin_t, end_t, func_r>{};
    }
}

#endif
