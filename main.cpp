#include <iostream>
#include <variant>
#include <fstream>
#include "readJson.h"

int main() {
    std::string filename = "example.json";
    std::string file = readFile(filename);
    std::cout << file << std::endl;
    return 0;
}

