# MyJsonParser:AtomJson

> A simple JSON parser for C++ with DOM style API.

## Usage

### Simple example at a glance

This example parses a JSON string into a document (DOM), make a simple modification of the DOM, and finally stringify the DOM to a JSON string.

``` c++
#include "../AtomJson.hpp"

using namespace ajson;

int main() {
    Json json;
    char* jsonstr = "{\"first name\" : \"Yang\", \"last name\" : \"Zhong\", \"age\" : 20.5, \"parent\" : {\"last name\" : \"Zhong\", \"phone number\" : \"xxx - xxxx - xxxx\"}}";

    // 1. Parse a JSON string into DOM.
    json = parse(jsonstr);

    // 2. Modify it by DOM.
    json[age] = 21;
 
    // 3. Stringify the DOM
    String str = stringify(json);
 
    // 4. Output the str
    std::cout << str << std::endl;
    return 0;
}
```

The output is presented below.

``` txt
{
        "parent":
                {
                        "last name":"Zhong",
                        "phone number":"xxx - xxxx - xxxx"
                },
        "last name":"Zhong",
        "age":21,
        "first name":"Yang"
} 
```

More [examples](https://github.com/Zhytou/MyJsonParser/tree/master/example) are avaliable.

### Run test

Use the command below.

``` bash
mkdir build
cd build
cmake ..
ninja test
./test
```

The output is presented below.

``` txt
Running main() from ./build/_deps/googletest-src/googletest/src/gtest_main.cc
[==========] Running 12 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 6 tests from JsonParse
[ RUN      ] JsonParse.HandleNull
[       OK ] JsonParse.HandleNull (0 ms)
[ RUN      ] JsonParse.HandleBoolen
[       OK ] JsonParse.HandleBoolen (0 ms)
[ RUN      ] JsonParse.HandleNumber
[       OK ] JsonParse.HandleNumber (0 ms)
[ RUN      ] JsonParse.HandleString
[       OK ] JsonParse.HandleString (0 ms)
[ RUN      ] JsonParse.HandleArray
[       OK ] JsonParse.HandleArray (0 ms)
[ RUN      ] JsonParse.HandleObject
[       OK ] JsonParse.HandleObject (0 ms)
[----------] 6 tests from JsonParse (0 ms total)

[----------] 6 tests from JsonStringify
[ RUN      ] JsonStringify.HandleNull
[       OK ] JsonStringify.HandleNull (0 ms)
[ RUN      ] JsonStringify.HandleBoolen
[       OK ] JsonStringify.HandleBoolen (0 ms)
[ RUN      ] JsonStringify.HandleNumber
[       OK ] JsonStringify.HandleNumber (0 ms)
[ RUN      ] JsonStringify.HandleString
[       OK ] JsonStringify.HandleString (0 ms)
[ RUN      ] JsonStringify.HandleArray
[       OK ] JsonStringify.HandleArray (0 ms)
[ RUN      ] JsonStringify.HandleObject
[       OK ] JsonStringify.HandleObject (0 ms)
[----------] 6 tests from JsonStringify (1 ms total)

[----------] Global test environment tear-down
[==========] 12 tests from 2 test suites ran. (1 ms total)
[  PASSED  ] 12 tests.
```

## Implementation

According to the [ECMA JSON data syntax](https://www.ecma-international.org/publications-and-standards/standards/ecma-404/), a JSON value can be an object, array, number, string, true, false, or null. So, the AtomJson library defines a class called Value (alias：Json) to store the JSON data and offers several methods to access and modify the JSON data. More importantly, the AtomJson library also defines Parse and Stringify method to implement the conversion between Json class and stream.

### Value(alias: Json)

The `Value` is basically a union of `Number`, `String`, `Array` and `Object`, using a member variable called type to point out which is availiable.

#### Number

The `Number` is an object that can represent unsigned, integer and float point number.

#### String

The `String` is an object that represents sequence of characters.

#### Array

The `Array` is a dynamic size array, whose element should be a Value.

#### Object

The `Object` is basically a hashmap, whose item should be a Key(String) and Value pair.

### Parse

The AtomJson library defines `Value parse(char*)` to convert JSON literal to Value objects. The `Value parse(char* )` function only supports ASCII encoding. For numbers, it supports scientific notation, but it can only store numbers ranging in [-1.79769e+308, 1.79769e+308].

### Stringify

The AtomJson library defines `String stringify(const Value&)` to convert Value object to string. The `String stringify(const Value&)` function outputs string without spaces by default. Change the parameter to add indentations(prettification), use scientific notation , change floating point number percision or keep exscape characters in string.

## Structure

```bash
.
├── CMakeLists.txt
├── LICENSE.md
├── README.md
├── build
├── example
│   ├── CMakeLists.txt
│   ├── customizedStringify.cpp
│   ├── simple.cpp
│   └── value.cpp
├── src
│   ├── Array.cpp
│   ├── AtomJson.cpp
│   ├── CMakeLists.txt
│   ├── Number.cpp
│   ├── Object.cpp
│   ├── String.cpp
│   └── include
│       ├── Array.hpp
│       ├── AtomJson.hpp
│       ├── DoublyLinkedList.hpp
│       ├── Number.hpp
│       ├── Object.hpp
│       └── String.hpp
└── test
    ├── CMakeLists.txt
    └── test.cpp
```

## Installation

``` bash
git clone https://github.com/Zhytou/MyJsonParser.git
cd src
# then add your own files
vim main.cpp
```

## License

MIT License

Copyright (c) 2022 Yang Zhong

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## Reference

[RapidJson](https://miloyip.github.io/rapidjson/)

[LeptJson](https://github.com/miloyip/json-tutorial)
