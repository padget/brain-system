
//#include "meta/core.hpp"
//#include "meta/fundamental.hpp"
//#include "meta/keywords.hpp"
//#include "meta/math.hpp"
//#include "configuration/properties.hpp"
//#include <iostream>

#include "meta/meta.hpp"
#include <iostream>
#include <typeinfo>
//#include "test/utest/utest.hpp"

using namespace brain;
using namespace std;


/// Main function for
/// C++ compiler.
int main()
{
    using a_list = meta::list<double, int, short, std::string>;
    using a_type = meta::advance_t<meta::begin_<a_list>, meta::unsigned_t<3>>;
    /// using at_2 = meta::at_t<a_list, meta::long_t<2>>;
    using a_second_list = meta::pop_front_t<a_list>;
    
    std::cout << typeid(a_type).name() << std::endl;
    
    ///static_assert(meta::v_<std::is_same<a_type, short>>, "");
    static_assert(meta::v_<std::is_same<meta::list<int, short, std::string>, a_second_list>>, "");


    return 0;
}
