#ifndef __BRAIN__PATTERN_HPP
#define __BRAIN__PATTERN_HPP

#include <type_traits>
#include <string>
#include <memory>

namespace brain
{
    /// /////////////////////////// ///
    /// Pattern Tags Identification ///
    /// /////////////////////////// ///


    /// Returns true if
    /// type_t implements
    /// a specific pattern
    /// pattern_tag_t
    template < typename pattern_tag_t,
             typename type_t >
    using implements_pattern_t =
        std::is_base_of<pattern_tag_t, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// factory pattern
        struct factory {};
    }


    /// Returns true if
    /// type_t implements
    /// factory pattern
    template<typename type_t>
    using implements_factory_t =
        implements_pattern_t<pattag::factory, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// abstract_factory pattern
        struct abstract_factory {};
    }


    /// Returns true if
    /// type_t implements
    /// abstract_factory pattern
    template<typename type_t>
    using implements_abstract_factory_t =
        implements_pattern_t<pattag::abstract_factory, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// adapter pattern
        struct adapter {};
    }


    /// Returns true if
    /// type_t implements
    /// adapter pattern
    template<typename type_t>
    using implements_adapter_t =
        implements_pattern_t<pattag::adapter, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// bridge pattern
        struct bridge {};
    }


    /// Returns true if
    /// type_t implements
    /// bridge pattern
    template<typename type_t>
    using implements_bridge_t =
        implements_pattern_t<pattag::bridge, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// chain of responsability
        /// pattern
        struct chain_of_resp {};
    }


    /// Returns true if
    /// type_t implements
    /// chain_of_resp pattern
    template<typename type_t>
    using implements_chain_of_resp_t =
        implements_pattern_t<pattag::chain_of_resp, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// command pattern
        struct command {};
    }


    /// Returns true if
    /// type_t implements
    /// command pattern
    template<typename type_t>
    using implements_command_t =
        implements_pattern_t<pattag::command, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// composite pattern
        struct composite {};
    }


    /// Returns true if
    /// type_t implements
    /// composite pattern
    template<typename type_t>
    using implements_composite_t =
        implements_pattern_t<pattag::composite, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// decorator pattern
        struct decorator {};
    }


    /// Returns true if
    /// type_t implements
    /// decorator pattern
    template<typename type_t>
    using implements_decorator_t =
        implements_pattern_t<pattag::decorator, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// facade pattern
        struct facade {};
    }


    /// Returns true if
    /// type_t implements
    /// facade pattern
    template<typename type_t>
    using implements_facade_t =
        implements_pattern_t<pattag::facade, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// flyweight pattern
        struct flyweight {};
    }


    /// Returns true if
    /// type_t implements
    /// flyweight pattern
    template<typename type_t>
    using implements_flyweight_t =
        implements_pattern_t<pattag::flyweight, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// interpreter pattern
        struct interpreter {};
    }


    /// Returns true if
    /// type_t implements
    /// interpreter pattern
    template<typename type_t>
    using implements_interpreter_t =
        implements_pattern_t<pattag::interpreter, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// iterator pattern
        struct iterator {};
    }


    /// Returns true if
    /// type_t implements
    /// iterator pattern
    template<typename type_t>
    using implements_iterator_t =
        implements_pattern_t<pattag::iterator, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// mediator pattern
        struct mediator {};
    }


    /// Returns true if
    /// type_t implements
    /// mediator pattern
    template<typename type_t>
    using implements_mediator_t =
        implements_pattern_t<pattag::mediator, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// memento pattern
        struct memento {};
    }


    /// Returns true if
    /// type_t implements
    /// memento pattern
    template<typename type_t>
    using implements_memento_t =
        implements_pattern_t<pattag::memento, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// observer pattern
        struct observer {};
    }


    /// Returns true if
    /// type_t implements
    /// observer pattern
    template<typename type_t>
    using implements_observer_t =
        implements_pattern_t<pattag::observer, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// politic pattern
        struct politic {};
    }


    /// Returns true if
    /// type_t implements
    /// politic pattern
    template<typename type_t>
    using implements_politic_t =
        implements_pattern_t<pattag::politic, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// prototype pattern
        struct prototype {};
    }


    /// Returns true if
    /// type_t implements
    /// prototype pattern
    template<typename type_t>
    using implements_prototype_t =
        implements_pattern_t<pattag::prototype, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// proxy pattern
        struct proxy {};
    }


    /// Returns true if
    /// type_t implements
    /// proxy pattern
    template<typename type_t>
    using implements_proxy_t =
        implements_pattern_t<pattag::proxy, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// singleton pattern
        struct singleton {};
    }


    /// Returns true if
    /// type_t implements
    /// singleton pattern
    template<typename type_t>
    using implements_singleton_t =
        implements_pattern_t<pattag::singleton, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// state pattern
        struct state {};
    }


    /// Returns true if
    /// type_t implements
    /// state pattern
    template<typename type_t>
    using implements_state_t =
        implements_pattern_t<pattag::state, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// strategy pattern
        struct strategy {};
    }


    /// Returns true if
    /// type_t implements
    /// strategy pattern
    template<typename type_t>
    using implements_strategy_t =
        implements_pattern_t<pattag::strategy, type_t>;


    namespace pattag
    {
        /// Tag identifying
        /// visitor pattern
        struct visitor {};
    }


    /// Returns true if
    /// type_t implements
    /// visitor pattern
    template<typename type_t>
    using implements_visitor_t =
        implements_pattern_t<pattag::visitor, type_t>;


    /// ///////////////////////// ///
    /// Basic Concepts / Patterns ///
    /// ///////////////////////// ///


    /// Declare that an
    /// object can be
    /// transformed into
    /// a string_t
    template<typename string_t>
    struct basic_stringable
    {
        /// Default virtual destructor
        /// for polymorphic inheritance
        virtual ~basic_stringable() = default;

        /// Operator string_t() for
        /// explicit casting operation
        /// Must be override for
        /// inheritance to provide cast
        virtual operator string_t() noexcept = 0;
    };


    /// Alias for basic_stringable
    /// of std::string
    using stringable =
        basic_stringable<std::string>;


    /// Alias for basic_stringable
    /// of std::wstring
    using wstringable =
        basic_stringable<std::wstring>;


    /// Design pattern Singleton.
    /// Initiate the singleton
    /// at the first invocation
    /// and keep it all over the
    /// execution of the program
    template <typename type_t>
    struct singleton :
            pattag::singleton
    {
        /// Lazy loading of
        /// the singleton
        static type_t& single() noexcept
        {
            static type_t obj;
            return obj;
        }
    };


    /// Returns true if
    /// type_t is derived
    /// from singleton<type_t>
    template<typename type_t>
    using is_singleton =
        std::is_base_of<singleton<type_t>, type_t>;


    /// Accessor for single()
    /// member of singleton_t
    template<typename singleton_t>
    const auto& single =
        singleton_t::single();


    /// Design pattern prototype
    /// Provides a pure clone methode
    template<typename type_t>
    struct prototype:
            pattag::prototype
    {
        /// Alias for
        /// unique_ptr<type_t>
        using type_ptr =
            std::unique_ptr<type_t>;


        /// Clone method that
        /// returns a copy of
        /// the prototype object
        virtual type_ptr clone() = 0;
    };


    /// Alias for
    /// prototype pattern
    template<typename type_t>
    using cloneable =
        prototype<type_t>;


    /// Returns true if
    /// type_t inherits from
    /// cloneable<type_t>
    template<typename type_t>
    using is_clonable =
        std::is_base_of<cloneable<type_t>, type_t>;
}
#endif
