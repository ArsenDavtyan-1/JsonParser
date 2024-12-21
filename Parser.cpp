#include <iostream>
#include "Tokenizer.h"
#include "JsonValue.h"
#include <string>



// this function should read the name
// of json value, and continue reading
// until the collon appearance, also 
// should move until to value
std::string nameReader(std::string input, size_t& pos)
{
	std::string		name;
	
	if (pos >= input.size() || input[pos] != '"') {
		throw std::runtime_error("Expected opening quote for value name");
	}

	++pos;
	while (pos < input.size() && input[pos] != '"') {
		name.push_back(input[pos]);
		++pos;
	}

	while (pos < input.size() && input[pos] != ':')
		++pos;
	if (pos >= input.size())
		throw std::runtime_error("Expected closing quote for value name");

	return name;
}



// it will expect a colon as a 
// start char input, and will read
// value writen after it
JsonValue jsonValueReader(std::string input, size_t& pos)
{
	Tokenizer::TokenType	token;
	std::string				value;

	if (pos >= input.size() || input[pos] != ':') {
		throw std::runtime_error("Expected colon for value");
	}

	++pos;
	while (std::isspace(input[pos]))
		++pos;
	
}



void JsonToObject(JsonObject& jsonObj, std::string& input)
{
	Tokenizer			strJson(input);
	Tokenizer::Token	token;

	do {
		if (!strJson.hasNextToken())
			break;
		token = strJson.nextToken();

		if (token.type == Tokenizer::TokenType::String) {
			
		}
	} 
	while (token.type != Tokenizer::TokenType::EndOfFile);
}