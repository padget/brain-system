#ifndef __DATA_FACTORY_HPP
#define __DATA_FACTORY_HPP

namespace brain{namespace data{
 class factory: singleton<factory>
        {
            public:
                template <typename str_t, typename = brain::enable_if_stringable_t<str_t>>
                static set createSet(str_t && name)
                { return set(name); }

            public:
                template <typename str_t, typename = brain::enable_if_stringable_t<str_t>>
                static type createType(str_t && name)
                { return type(name); }

                template <typename str_t, typename = brain::enable_if_stringable_t<str_t>>
                static type createType(str_t && name, unsigned min, unsigned max)
                { return type(name, min, max); }

            public:
                template < typename str_t, typename = brain::enable_if_stringable_t<str_t>>
                static column createColumn(str_t& name, type& t)
                { return column(name, t); }

            public:
                template < typename str_t, typename = brain::enable_if_stringable_t<str_t>>
                static lambda createLambda(str_t && name, type && t)
                { return lambda(name, t); }

                /* public:
                     template <typename ... args>
                     static event_sptr createEvent(args && ... argsvalue)
                     { return std::make_shared<event>(std::forward<args>(argsvalue)...)); }
                */
            public:

                template <typename basic, typename = enable_if_basiclambda<basic>>
                static lambda_sptr createBasicLambda()
                { return std::make_shared<basic>(); }

                template <typename basic, typename = enable_if_basiclambda<basic>>
                static lambda_sptr createBasicLambda(const list_sptr& arg)
                { return std::make_shared<basic>(arg); }

                template <typename basic, typename = enable_if_basiclambda<basic>>
                static lambda_sptr createBasicLambda(list_sptr && arg)
                { return std::make_shared<basic>(arg); }

                template <typename basic, typename = enable_if_basiclambda<basic>>
                static lambda_sptr createBasicLambda(std::initializer_list<expression_sptr> && values)
                { return std::make_shared<basic>(values); }
        };
}

}


#endif