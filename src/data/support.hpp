#ifndef  __LQL_SUPPORT_H__
#define __LQL_SUPPORT_H__

#include "../core/functionnal.hpp"

namespace brain
{
    namespace data
    {
        class string:
            public cpl::semantic_object,
            public with_value<std::string>
        {
            public:
                BRAIN_ALL_DEFAULT(string)
            public:

                virtual void init(std::vector<std::shared_ptr<semantic_object>>& args)
                {
                    this->value(shared_conv<cpl::string>(args[0])->value());
                }

                inline virtual operator std::string() noexcept
                { return value(); }
        };

        class name:
            public cpl::semantic_object,
            public with_value<std::string>
        {
            public:
                BRAIN_ALL_DEFAULT(name)
            public:
                virtual void init(std::vector<std::shared_ptr<semantic_object>>& args)
                {
                    this->value(shared_conv<cpl::string>(args[0])->value());
                }

                inline virtual operator std::string() noexcept
                { return value(); }
        };

        class integer:
            public cpl::semantic_object,
            public with_value<int>
        {
            public:
                BRAIN_ALL_DEFAULT(integer)
            public:
                virtual void init(std::vector<std::shared_ptr<semantic_object>>& args)
                {
                    this->value(str2conv<int>::conv(shared_conv<cpl::string>(args[0])->value()));
                }

                inline virtual operator std::string() noexcept
                { return literal2str(value()); }
        };

        class number:
            public cpl::semantic_object,
            public with_value<double>
        {
            public:
                virtual void init(std::vector<std::shared_ptr<semantic_object>>& args)
                {
                    this->value(str2conv<double>::conv(shared_conv<cpl::string>(args[0])->value()));
                }

                BRAIN_ALL_DEFAULT(number)

                inline virtual operator std::string() noexcept
                { return concat(value()); }
        };

        class component:
            public cpl::semantic_object,
            public with_value<cpl::semobject_sptr>
        {
            public:
                virtual void init(std::vector<std::shared_ptr<semantic_object>>& args)
                {
                    this->value(args[0]);
                }

                BRAIN_ALL_DEFAULT(component)

                inline virtual operator std::string() noexcept
                { return std::string(*value()); }
        };


        class expression:
            public cpl::semantic_object,
            public with_name<data::name>
        {
            public:
                virtual void init(std::vector<std::shared_ptr<semantic_object>>& args)
                {
                    logger<expression>::debug("expression args size ", args.size());
                    logger<expression>::debug("expression args 1 : ", typeid(*args[1]).name());
                    logger<expression>::debug("expression args 2 : ", typeid(*args[2]).name());
                    logger<expression>::debug("expression : ", std::string(*args[1]), std::string(*args[2]));
                }

                BRAIN_ALL_DEFAULT(expression)

            public:
                virtual std::shared_ptr<expression> eval()
                { return std::make_shared<expression>(); }
        };

        using expression_sptr = std::shared_ptr<expression>;

        class expressions:
            public cpl::semantic_object,
            public with_value<std::list<expression_sptr>>
        {
            public:
                BRAIN_ALL_DEFAULT(expressions)
            public:
                virtual void init(std::vector<std::shared_ptr<semantic_object>>& args)
                {
                    logger<expressions>::debug("expressions");

                    for(const auto & exp : args)
                        value().push_back(shared_conv<expression>(exp));
                }

                inline virtual operator std::string() noexcept
                {
                    std::string result;
                    logger<expressions>::debug("Expressions -> string");
                    logger<expressions>::debug("Expressions size ", value().size());

                    for(const auto & exp : value())
                        result += fct::not_null(exp) ?
                        (std::string)(*exp.get()) :
                        "nullptr";

                    return result;
                }
        };

        class factory
        {
            public:
                template<typename type_t>
                static auto make(const std::string& val)
                {
                    std::shared_ptr<type_t> val_ptr {new type_t()};
                    val_ptr->value(str2conv<typename type_t::value_type>::conv(val));
                    return val_ptr;
                }

                static auto make_expressions(const std::vector<object_sptr> vals)
                {
                    std::shared_ptr<data::expressions> exps {new expressions()};

                    for(const auto & exp : vals)
                        exps->value().push_back(shared_conv<expression>(exp));

                    return exps;
                }
        };

        template<typename binary_sfunctor>
        class _binary_op_expression
        {
            public:
                template<typename left_t, typename right_t>
                inline auto operator()(left_t && left, right_t && right) const
                {
                    return binary_sfunctor::single()(std::forward(left.value()),
                                                     std::forward(right.value()));
                }
        };

        /*template<typename result_t>
        using add_expression = single_functor<_binary_op_expression<brain::plus<result_t>>>;

        template<typename result_t>
        using minus_expression = single_functor<_binary_op_expression<brain::minus<result_t>>>;

        template<typename result_t>
        using divides_expression = single_functor<_binary_op_expression<brain::divides<result_t>>>;

        template<typename result_t>
        using multiplies_expression = single_functor<_binary_op_expression<brain::multiplies<result_t>>>;

        using concatenates_expression = single_functor<_binary_op_expression<brain::concatenates>>;*/
    }
}

#endif
