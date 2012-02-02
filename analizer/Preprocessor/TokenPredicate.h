
#pragma once
#include <memory>

class Token;

class TokenPredicate {
public:
	TokenPredicate(const char *text);
	virtual ~TokenPredicate();
	
	virtual bool operator()(const std::shared_ptr<Token> &token) const;
};
