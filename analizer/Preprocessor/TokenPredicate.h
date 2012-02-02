
#pragma once
#include <memory>
#include <string>

class Token;

class TokenPredicate {
public:
	TokenPredicate(const char *text);
	virtual ~TokenPredicate();
	
	virtual bool operator()(const std::shared_ptr<Token> &token) const;
	
private:
	const std::string text;
};
