
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
    using foo = list<int, short, double>;
    
    using fii = advance_<begin_<foo>, unsigned_<1>>;

    /// static_assert(v_<is_same_<res, true_>>, "");
    std::cout << typeid(fii).name() << std::endl;

    return 0;
}
