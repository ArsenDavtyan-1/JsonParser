#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <iostream>
#include <string>


class Tokenizer
{
public:
	enum class TokenType 
	{
		String,
		Number,
		Boolean,
		Null,
		Comma,        // ,
		Colon,        // :
		LeftBrace,    // {
		RightBrace,   // }
		LeftBracket,  // [
		RightBracket, // ]
		EndOfFile
	};

	struct Token {
		TokenType type;
		std::string value;
	};

	explicit Tokenizer(const std::string& input);

	bool hasNextToken() const;
	Token nextToken();
private:
	std::string input;
	size_t pos;

	void skipWhitespace();
	Token parseString();
	Token parseNumber();
	Token parseBoolean();
	Token parseNull();
};





#endif !TOKENIZER_H_
