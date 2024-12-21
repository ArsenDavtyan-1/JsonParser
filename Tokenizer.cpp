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
    size_t temp = pos;
    while (temp < input.size() && isspace(input[temp])) temp++;
    return temp < input.size();
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

Tokenizer::Token Tokenizer::parseString() 
{
    if (input[pos] != '"') {
        throw std::runtime_error("Expected string opening quote");
    }
    pos++; // Skip opening quote
    std::string result;

    while (pos < input.size() && input[pos] != '"') {
        if (input[pos] == '\\') {
            pos++; // Handle escape sequences
            if (pos < input.size()) {
                char escaped = input[pos];
                switch (escaped) {
                case '"': result += '"'; break;
                case '\\': result += '\\'; break;
                case '/': result += '/'; break;
                case 'b': result += '\b'; break;
                case 'f': result += '\f'; break;
                case 'n': result += '\n'; break;
                case 'r': result += '\r'; break;
                case 't': result += '\t'; break;
                default:
                    throw std::runtime_error("Invalid escape sequence");
                }
            }
        }
        else {
            result += input[pos];
        }
        pos++;
    }

    if (pos == input.size() || input[pos] != '"') {
        throw std::runtime_error("Expected closing quote for string");
    }
    //pos++; // Skip closing quote - maybe we don't need it
    return { TokenType::String, result };
}


Tokenizer::Token Tokenizer::parseNumber()
{
    size_t start = pos;
    if (input[pos] == '-') pos++; // Negative sign

    while (pos < input.size() && isdigit(input[pos])) pos++; // Integer part

    if (pos < input.size() && input[pos] == '.') {
        pos++; // Decimal point
        while (pos < input.size() && isdigit(input[pos])) pos++; // Fractional part
    }

    if (pos < input.size() && (input[pos] == 'e' || input[pos] == 'E')) {
        pos++; // Exponent
        if (pos < input.size() && (input[pos] == '+' || input[pos] == '-')) pos++; // Sign
        while (pos < input.size() && isdigit(input[pos])) pos++; // Exponent digits
    }

    return { TokenType::Number, input.substr(start, pos - start) };
}

Tokenizer::Token Tokenizer::parseBoolean() 
{
    if (input.compare(pos, 4, "true") == 0) {
        pos += 4;
        return { TokenType::Boolean, "true" };
    }
    else if (input.compare(pos, 5, "false") == 0) {
        pos += 5;
        return { TokenType::Boolean, "false" };
    }
    throw std::runtime_error("Invalid boolean value");
}

Tokenizer::Token Tokenizer::parseNull() 
{
    if (input.compare(pos, 4, "null") == 0) {
        pos += 4;
        return { TokenType::Null, "null" };
    }
    throw std::runtime_error("Invalid null value");
}
