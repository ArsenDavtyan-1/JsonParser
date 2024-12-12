#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <iostream>
#include <variant>
#include <string>
#include <map>
#include <vector>


class JsonValue;


using JsonObject = std::map < std::string, JsonValue>;
using JsonArray = std::vector<JsonValue>;
using JsonValueType = std::variant<std::nullptr_t, bool, double, std::string, JsonArray, JsonObject>;


class JsonValue
{
	JsonValueType value;
	
	JsonValue() : value(nullptr) {}
	JsonValue(std::nullptr_t) : value(nullptr) {}
	JsonValue(bool b) : value(b) {}
	JsonValue(double numb) : value(numb) {}
	JsonValue(std::string& str) : value(str) {}
	JsonValue(JsonObject& obj) : value(obj) {}
	JsonValue(JsonArray& arr) : value(arr) {}

	bool isNull() const { return std::holds_alternative<std::nullptr_t>(value); }
	bool isBool() const { return std::holds_alternative<bool>(value); }
	bool isNumber() const { return std::holds_alternative<double>(value); }
	bool isString() const { return std::holds_alternative<std::string>(value); }
	bool isArray() const { return std::holds_alternative<JsonArray>(value); }
	bool isObject() const { return std::holds_alternative<JsonObject>(value); }
};


#endif ! JSON_VALUE_H
