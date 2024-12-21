#ifndef PARSER_H_
#define PARSER_H_

#include "JsonValue.h"
#include "Tokenizer.h"




std::string nameReader(std::string input, size_t& pos);
void JsonToObject(JsonObject& jsonObj, std::string& input);



#endif !PARSER_H_
