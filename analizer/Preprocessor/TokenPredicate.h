
#pragma once
#include <memory>
#include <string>

class Token;

class TokenPredicate {
public:
	TokenPredicate() = delete;
	TokenPredicate(const char *text);
	virtual ~TokenPredicate();
	
	bool operator()(const std::shared_ptr<Token> &token) const;
	
protected:
	TokenPredicate(const TokenPredicate &predicate, bool except);
	
	const std::string text;
	const bool except;
};

class TokenPredicateNot : public TokenPredicate {
public:
	TokenPredicateNot() = delete;
	TokenPredicateNot(const TokenPredicate &pred);
};
