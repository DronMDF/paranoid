
#pragma once

#include <string>

class Error {
public:
	Error(const Token &/*token*/, const std::string &/*message*/) {}
	std::string what() const { return std::string(); } 
};
