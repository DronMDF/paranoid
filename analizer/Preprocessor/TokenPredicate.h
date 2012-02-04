
#pragma once
#include <memory>
#include <string>

class Token;
class TokenPredicateImpl;

class TokenPredicate {
public:
	TokenPredicate() = delete;
	TokenPredicate(const char *text);
	
	bool operator()(const std::shared_ptr<Token> &token) const;

private:
	std::shared_ptr<TokenPredicateImpl> predicate;
};

TokenPredicate Not(const TokenPredicate &predicate);
