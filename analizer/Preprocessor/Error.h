
#pragma once

#include <memory>
#include <string>

class Token;

class Error {
public:
	Error(const std::shared_ptr<const Token> &token, const std::string &message);
	std::string what() const;
	
private:
	const std::shared_ptr<const Token> &token;
	const std::string message;
};
