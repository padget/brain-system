
//#include "meta/core.hpp"
//#include "meta/fundamental.hpp"
//#include "meta/keywords.hpp"
//#include "meta/math.hpp"
//#include "configuration/properties.hpp"
//#include <iostream>

#include <vector>
#include "meta/meta.hpp"
#include <typeinfo>
#include <iostream>
//#include "test/utest/utest.hpp"

using namespace brain::meta;
using namespace std;


/// Main function for
/// C++ compiler.
int main()
{

    std::cout << typeid(type_<impl::bind<lazy::is_same_<_0_, _1_>, int, float>>).name() << std::endl;
    
    return 0;
}
