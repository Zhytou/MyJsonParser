#include "../AtomJson.hpp"

// AtomJson namespace nikename ajson
using namespace ajson;

int main()
{
    // Value nickname Json
    Value v;

    // Define v by default, which should be null
    std::cout << v << '\n';

    // Define v with bool
    v = true;
    std::cout << v << '\n';
    v = false;
    std::cout << v << '\n';

    // Define v with ajson::Number
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
    std::cout << v << '\n';

    v = f;
    std::cout << v << '\n';
    v = d;
    std::cout << v << '\n';

    // Define v with char*\std::string\AtomJson::String
    v = "defined by char*";
    std::cout << v << '\n';

    v = std::string("defined by std::string");
    std::cout << v << '\n';

    v = String("defined by ajson::String");
    std::cout << v << '\n';

    // Define v with ajson::Array
    Array a, a1;
    a.append(true);
    a.append(false);
    a.append(1);
    a.append(2.34);
    a.append("string");
    a1.append(5);
    a1.append(6.78);
    a1.append("string2");
    a.append(a1);
    v = a;
    std::cout << v << '\n';

    // Define v with ajson::Object
    Object o, o1;
    o["male"] = true;
    o["female"] = false;
    o["age"] = 21;
    o["height"] = 188.5;
    o["name"] = "zhytou";
    o1["rank"] = "rookie";
    o1["company name"] = "xxx";
    o["job"] = o1;
    o["other information"] = a;
    v = o;
    std::cout << v << '\n';

    // use getXXX function to get a copy of the things contained in Value

    // use setXXX function to change the type and the contents of Value

    // use index operator [] to access the element in Value object when it is an Array or Object

    std::cout << std::endl;
}