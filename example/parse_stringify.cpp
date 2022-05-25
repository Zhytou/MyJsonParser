#include "../AtomJson.hpp"
#include <sstream>

using namespace ajson;

int main()
{

    Json json;
    Object o, o1;

    json = parse("{\"first name\" : \"Yang\", \"last name\" : \"Zhong\", \"age\" : 20.5, \"parent\" : {\"last name\" : \"Zhong\", \"phone number\" : \"xxx - xxxx - xxxx\"}}");

    o["first name"] = "Yang";
    o["last name"] = "Zhong";
    o["age"] = 20.5;
    o1["last name"] = "Zhong";
    o1["phone number"] = "xxx - xxxx - xxxx";
    o["parent"] = o1;

    std::cout << stringify(json) << '\n';
    //<< stringify(o) << std::endl;

    Array keys = o.keys();
    for (size_t i = 0; i < keys.length(); i++)
    {
        String key = keys[i].getString();
        std::cout << "json.exist = " << json.exist(key) << '\n'
                  << "json[key] = " << json[key] << '\n'
                  << "o[key] = " << o[key] << '\n'
                  << "equal or not? " << (json[key] == o[key]) << '\n';
    }
    std::cout << std::endl;

    json = parse("[1,2,3,1.0,2.5,4.8]");
    String str = "[1,2,3,1.0,2.5,4.8]";
    std::cout << stringify(json, false) << '\n'
              << str << '\n';

    json = parse("[]");
    std::cout << "isArray() " << json.isArray() << "\nthe array is " << json << '\n';

    json = parse("[true, false]");
    std::cout << "isArray() " << json.isArray() << "\nthe array is " << json << '\n';
    std::cout << "stringify without prettify " << stringify(json, false) << '\n';

    json = parse("{}");
    std::cout << "isObject() " << json.isArray() << "\nthe object is " << json;

    json = parse("\"\\\" \\\\ \\/ \\b \\f \\n \\r \\t\"");
    str = stringify(json);
    std::cout << "string keep escape character is " << str << '\n';

    std::cout
        << std::endl;
}
