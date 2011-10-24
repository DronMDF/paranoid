
#pragma once

#include <string>

class Token;

class Error {
public:
	Error(const Token &/*token*/, const std::string &/*message*/);
	std::string what() const;
};
