#include "../AtomJson.hpp"

using namespace ajson;

int main()
{
    Json json;
    char jsonstr[] = "{\"name\" : \"zhytou\", \"age\" : 20.5}";

    // 1. Parse a JSON string into DOM.
    json = parse(jsonstr);

    // 2. Modify it by DOM.
    json["age"] = 23;

    // 3. Stringify the DOM
    String str = stringify(json);

    // 4. Output the str
    std::cout << str << std::endl;

    return 0;
}