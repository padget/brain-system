#ifndef __BRAIN_META_SEQUENCE_ALGORITHM_HPP_
# define __BRAIN_META_SEQUENCE_ALGORITHM_HPP_

# include "sequence.hpp"
# include "view.hpp"

namespace meta
{
    namespace seq
    {
        template < typename sequence_t,
                 typename pred_r >
        using find_if_ =
            meta::find_if_ <
            meta::begin_<sequence_t>,
            meta::end_<sequence_t>,
            pred_r >;


        template < typename sequence_t,
                 typename target_t >
        using find_ =
            meta::find_ <
            meta::begin_<sequence_t>,
            meta::end_<sequence_t>,
            target_t >;


        template < typename sequence_t,
                 typename pred_r >
        using count_if_ =
            meta::count_if_ <
            meta::begin_<sequence_t>,
            meta::end_<sequence_t>,
            pred_r >;


        template < typename sequence_t,
                 typename target_t >
        using count_ =
            meta::count_ <
            meta::begin_<sequence_t>,
            meta::end_<sequence_t>,
            target_t >;

        template <typename sequence_t,
                 typename target_t >
        using contains_ =
            meta::contains_ <
            meta::begin_<sequence_t>,
            meta::end_<sequence_t>,
            target_t >;

        template <typename sequence_t,
                 typename func_r >
        using transform_ =
            meta::clone_<sequence_t, meta::transform_ <
            meta::begin_<sequence_t>,
            meta::end_<sequence_t>,
            func_r >>;

        template <typename sequence_t,
                 typename new_t,
                 typename pred_r >
        using replace_if_ =
            meta::clone_<sequence_t, meta::replace_if_ <
            meta::begin_<sequence_t>,
            meta::end_<sequence_t>,
            new_t,
            pred_r >>;

        template < typename sequence_t,
                 typename old_t,
                 typename new_t >
        using replace_ =
            meta::clone_<sequence_t, meta::replace_ <
            meta::begin_<sequence_t>,
            meta::end_<sequence_t>,
            old_t,
            new_t >>;

        template < typename sequence_t,
                 typename pred_r >
        using remove_if_ =
            meta::clone_<sequence_t, meta::remove_if_ <
            meta::begin_<sequence_t>,
            meta::end_<sequence_t>,
            pred_r >>;

        template <typename sequence_t,
                 typename deleted_t >
        using remove_ =
            meta::clone_<sequence_t, meta::remove_ <
            meta::begin_<sequence_t>,
            meta::end_<sequence_t>,
            deleted_t >>;
    }
}
#endif
