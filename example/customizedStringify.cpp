#include "../AtomJson.hpp"
#include <sstream>

using namespace ajson;

int main()
{
    Json json;

    json = parse("{\"first name\" : \"Yang\", \"last name\" : \"Zhong\", \"age\" : 20.5, \"parent\" : {\"last name\" : \"Zhong\", \"phone number\" : \"xxx - xxxx - xxxx\"}}");

    // Stringify with prettificaton
    std::cout << stringify(json, true) << '\n';

    // Stringify without prettification
    std::cout << stringify(json, false) << '\n';

    json = parse("[1,2,3,1.01,2.5783,4.87814]");
    // Use scientific notation
    std::cout << stringify(json, true, true) << '\n';

    // Customize the float number percision
    std::cout << stringify(json, true, false, 3) << '\n';

    json = parse("\"John said: What a nice day\\n\\tLet's hang out!\"");
    std::cout << stringify(json, false) << '\n';

    // Keep the escape character in String
    std::cout << stringify(json, false, false, 0, true) << '\n';

    std::cout << std::endl;
}
