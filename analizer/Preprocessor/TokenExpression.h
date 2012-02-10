
#pragma once

#include <initializer_list>
#include <memory>
#include <vector>

class Token;
class TokenPredicate;

class TokenExpression {
public:
	TokenExpression() = delete;
	TokenExpression(const std::initializer_list<TokenPredicate> &expr);
	
	bool match(const std::shared_ptr<const Token> &token);
	bool isMatched() const;
	void reset();
private:
	const std::vector<TokenPredicate> predicates;
	unsigned position;
	unsigned quantity;
};
