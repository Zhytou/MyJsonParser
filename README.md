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

### Run test

Use the command below.

``` bash
cmake --build ./build --config Debug --target test --
./build/test
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
/mnt/d/ZhY/WorkSpace/MyJsonParser/test.cpp:188: Failure
Expected equality of these values:
  stringify(json, false) == str
    Which is: false
  true
[  FAILED  ] JsonStringify.HandleArray (0 ms)
[ RUN      ] JsonStringify.HandleObject
[       OK ] JsonStringify.HandleObject (0 ms)
[----------] 6 tests from JsonStringify (0 ms total)

[----------] Global test environment tear-down
[==========] 12 tests from 2 test suites ran. (0 ms total)
[  PASSED  ] 11 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] JsonStringify.HandleArray

 1 FAILED TEST
```

## Implementation

According to the [ECMA JSON data syntax](https://www.ecma-international.org/publications-and-standards/standards/ecma-404/), a JSON value can be an object, array, number, string, true, false, or null. So, AtomJson libirary consistes of 4 main classes and 2 main function.

### Number

### String

### Array

### Object

## Installation

``` bash
cd ./your-proj
mkdir include
cd ./include
git clone https://github.com/Zhytou/MyJsonParser.git
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
