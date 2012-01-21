
#pragma once
#include <memory>
#include <string>

class Token;

class Error {
public:
	Error(const std::shared_ptr<const Token> &token, const std::string &message);

	// Field are accessible
	const std::shared_ptr<const Token> token;
	const std::string message;
};
