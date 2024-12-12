#include "Tokenizer.h"

Tokenizer::Tokenizer(const std::string& input) : input(input), pos(0)
{}


void Tokenizer::skipWhitespace()
{
	while (pos < input.size() && input[pos] == ' ')
		++pos;
	return;
}


bool Tokenizer::hasNextToken() const
{
	

}

Tokenizer::Token Tokenizer::nextToken()
{
	skipWhitespace();
	
	if (pos >= input.size())
		return { TokenType::EndOfFile, "" };

    char current = input[pos];

    if (current == '{') {
        pos++;
        return { TokenType::LeftBrace, "{" };
    }
    else if (current == '}') {
        pos++;
        return { TokenType::RightBrace, "}" };
    }
    else if (current == '[') {
        pos++;
        return { TokenType::LeftBracket, "[" };
    }
    else if (current == ']') {
        pos++;
        return { TokenType::RightBracket, "]" };
    }
    else if (current == ':') {
        pos++;
        return { TokenType::Colon, ":" };
    }
    else if (current == ',') {
        pos++;
        return { TokenType::Comma, "," };
    }
    else if (current == '"') {
        return parseString();
    }
    else if (isdigit(current) || current == '-') {
        return parseNumber();
    }
    else if (input.compare(pos, 4, "true") == 0 || input.compare(pos, 5, "false") == 0) {
        return parseBoolean();
    }
    else if (input.compare(pos, 4, "null") == 0) {
        return parseNull();
    }

    throw std::runtime_error("Unexpected character in JSON input");
}
