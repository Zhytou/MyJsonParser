#include "../AtomJson.hpp"

using namespace ajson;

int main()
{
    // Value nickname Json
    Value v;
    std::cout << v << '\n';

    // Define v with Boolen
    v = true;
    std::cout << v << '\n';
    v = false;
    std::cout << v << '\n';

    // Define v with Number
    int i = 10;
    unsigned u = 20;
    long l = 100;
    float f = 0.1;
    double d = 0.234;

    v = i;
    std::cout << v << '\n';

    v = u;
    std::cout << v << '\n';
    v = l;
    std::cout
        << v << '\n';

    v = f;
    std::cout << v << '\n';
    v = d;
    std::cout << v << '\n';

    // Define v with char*\std::string\AtomJson::String
    v = "123";
    std::cout << std::endl;
}