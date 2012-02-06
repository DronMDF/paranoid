
#pragma once

#include <list>
#include <memory>
#include <vector>

class Token;
class TokenPredicate;

class TokenExpression {
public:
	TokenExpression() = delete;
	TokenExpression(const TokenExpression &) = delete;
	TokenExpression(const std::list<TokenPredicate> &expr);
	
	bool match(const std::shared_ptr<const Token> &token);
	bool isMatched() const;
	void reset();
private:
	const std::vector<TokenPredicate> predicates;
	unsigned position;
};
