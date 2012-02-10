
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
	bool isSome() const;
	bool isOptional() const;

private:
	std::shared_ptr<TokenPredicateImpl> impl;
};

TokenPredicate Not(const TokenPredicate &predicate);
TokenPredicate Some(const TokenPredicate &predicate);
TokenPredicate Optional(const TokenPredicate &predicate);

extern const TokenPredicate isSpace;
extern const TokenPredicate isWord;
extern const TokenPredicate isEol;
