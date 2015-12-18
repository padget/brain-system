#ifndef __LQL_LAMBDA_H__
#define __LQL_LAMBDA_H__

#include "support.hpp"
#include "../core/template.hpp"
#include "../core/functionnal.hpp"

namespace brain
{
    namespace data
    {
        /*WITH_T(arg)

        template <const char* lambda_name_str>
        class basic_lambda:
            public lambda,
            public with_arg<list_sptr>
        {
                static std::string lambda_name;
                static data::type lambda_type;

            public:
                basic_lambda() :
                    lambda(basic_lambda<lambda_name_str>::lambda_name,
                           basic_lambda<lambda_name_str>::lambda_type)
                {
                }

                basic_lambda(const list_sptr& arg) :
                    lambda(basic_lambda<lambda_name_str>::lambda_name,
                           basic_lambda<lambda_name_str>::lambda_type),
                    with_arg<list_sptr>(arg)
                {
                }

                basic_lambda(list_sptr && arg) :
                    lambda(basic_lambda<lambda_name_str>::lambda_name,
                           basic_lambda<lambda_name_str>::lambda_type),
                    with_arg<list_sptr>(arg)
                {
                }

                basic_lambda(std::initializer_list<expression_sptr> && values) :
                    lambda(basic_lambda<lambda_name_str>::lambda_name,
                           basic_lambda<lambda_name_str>::lambda_type),
                    with_arg<list_sptr>(new list(values))
                {
                }

                basic_lambda(const basic_lambda<lambda_name_str>& other) :
                    lambda(other),
                    with_arg<list_sptr>(other.arg())
                {
                }

                basic_lambda(basic_lambda<lambda_name_str> && other) :
                    lambda(other),
                    with_arg<list_sptr>(move(other.arg()))
                {
                }

                virtual ~basic_lambda()
                {
                }

            public:
                basic_lambda<lambda_name_str>& operator=(const basic_lambda<lambda_name_str>& other)
                {
                    if(this != &other)
                    {
                        this->lambda::operator=(other);
                        this->with_arg<list_sptr>::operator=(other.arg());
                    }

                    return *this;
                }

                basic_lambda<lambda_name_str>& operator=(basic_lambda<lambda_name_str> && other)
                {
                    if(this != &other)
                    {
                        this->lambda::operator=(other);
                        this->with_arg<list_sptr>::operator=(other.arg());
                    }

                    return *this;
                }

                virtual expression_sptr eval();
        };

        template <const char* lambda_name_str>
        std::string basic_lambda<lambda_name_str>::lambda_name = lambda_name_str;

        template <typename basic>
        using enable_if_basiclambda = std::enable_if_t<std::is_same<basic_lambda<basic::ID>, brain::rem_ref_cv_t<basic>>::value, basic>;

        template <typename lambda_sptr>
        using enable_if_lambda_sptr_t = brain::enable_if_specific_shared_ptr_t<lambda_sptr, lambda_sptr>;

        constexpr char plus_str[] = "+";
        constexpr char minus_str[] = "-";
        constexpr char div_str[] = "/";
        constexpr char mult_str[] = "*";
        constexpr char mod_str[] = "%";
        constexpr char sup_str[] = ">";
        constexpr char inf_str[] = "<";
        constexpr char inf_equal_str[] = "<=";
        constexpr char sup_equal_str[] = ">=";
        constexpr char equal_equal_str[] = "==";
        constexpr char diff_str[] = "!=";
        constexpr char plus_plus_str[] = "++";
        constexpr char minus_minus_str[] = "--";

        using bti_Plus       = basic_lambda<plus_str>;
        using bti_Minus      = basic_lambda<minus_str>;
        using bti_Mult       = basic_lambda<mult_str>;
        using bti_Div        = basic_lambda<div_str>;
        using bti_Mod        = basic_lambda<mod_str>;

        using bti_PlusPlus   = basic_lambda<plus_plus_str>;
        using bti_MinusMinus = basic_lambda<minus_minus_str>;

        using bti_EqualEqual = basic_lambda<equal_equal_str>;
        using bti_Diff       = basic_lambda<diff_str>;
        using bti_InfEqual   = basic_lambda<inf_equal_str>;
        using bti_SupEqual   = basic_lambda<sup_equal_str>;
        using bti_Inf        = basic_lambda<inf_str>;
        using bti_Sup        = basic_lambda<sup_str>;


        template<typename allocates_sfunctor = brain::allocates>
        class if_type_allocate
        {
            public:
                template<typename result_t, typename right_t>
                inline auto operator()(result_t && result, right_t && right)
                {
                    return brain::if_t<equals, allocates_sfunctor>::single()(
                               std::forward_as_tuple(typeid(result), typeid(right)),
                               std::forward_as_tuple(result, right));
                }
        };

        template<typename binary_sfunctor>
        class allocates_with_binary
        {
            public:
                template<typename result_t, typename right_t>
                inline auto& operator()(result_t && result, right_t && right)
                {
                    return brain::allocates_single(std::forward(result),
                                                   std::move(std::forward(binary_sfunctor::single(data::integer::value(result),
                                                           data::integer::value(right)))));

                }
        };

        template<typename binary_sfunctor>
        using if_type_allocate_with_binary = single_functor<if_type_allocate<allocates_with_binary<binary_sfunctor>>>;


        // [REGION] : bti_Plus
        */
        /*
         template <>
        data::type bti_Plus::lambda_type("expression", 1, 1);

        template <>
        expression_sptr bti_Plus::eval()
        {
            expression_sptr result;

            if(true)
            {
                int i = 0;

                for(auto & value : arg()->value())
                {
                    auto && value_eval = value->eval();

                    if(i == 0)
                    {
                        result = value_eval;
                    }

                    else
                    {
                        if_type_allocate_with_binary<brain::plus<data::integer>>::single();
                    }
                }
            }

            return expression_sptr();
        }*/
    }
}

#endif
