#include <iostream>
#include <variant>
#include <fstream>
#include "readJson.h"
#include "JsonValue.h"
#include "Tokenizer.h"



int main() 
{
    std::string json = R"({"key": "value", "number": 123, "array": [true, false, null]})";

    Tokenizer tokenizer(json);

    while (tokenizer.hasNextToken()) {
        auto token = tokenizer.nextToken();
        std::cout << "Type: " << static_cast<int>(token.type) << ", Value: " << token.value << std::endl;
    }

    return 0;
}


