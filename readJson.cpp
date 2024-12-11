#include "readJson.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


std::string readFile(std::string fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: " + fileName);
	}

	std::ostringstream ss;
	ss << file.rdbuf();
	return ss.str();
}