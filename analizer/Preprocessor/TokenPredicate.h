
#pragma once
#include <memory>
#include <string>

class Token;
class TokenPredicateImpl;

class TokenPredicate {
public:
	TokenPredicate() = delete;
	TokenPredicate(const TokenPredicate &predicate);
	TokenPredicate(const std::shared_ptr<TokenPredicateImpl> &impl);
	TokenPredicate(const char *text);
	
	bool operator()(const std::shared_ptr<const Token> &token) const;

private:
	std::shared_ptr<TokenPredicateImpl> impl;
};

TokenPredicate Not(const TokenPredicate &predicate);

TokenPredicate createIsSpace();
static const TokenPredicate isSpace = createIsSpace();
