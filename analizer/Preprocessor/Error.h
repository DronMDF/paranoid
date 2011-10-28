
#pragma once

#include <string>
#include "Locator.h"

class Token;

class Error {
public:
	Error(const Token &token, const std::string &message);
	std::string what() const;
	
private:
	std::string location;
	std::string message;
	std::string text;
};
