
#pragma once

#include <list>
#include <memory>
#include <functional>

class Token;
class TokenPredicate;

class TokenExpression {
public:
	enum class status {
		error = 0
	};
	
	TokenExpression() = delete;
	TokenExpression(const TokenExpression &) = delete;
	TokenExpression(const std::list<TokenPredicate> &expr);
	
	status match(const std::shared_ptr<const Token> &token);
};