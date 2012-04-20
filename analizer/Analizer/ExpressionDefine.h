
#pragma once
#include "Expression.h"

class ExpressionDefine : public Expression {
public:
	ExpressionDefine(const std::list<std::shared_ptr<Token>> &tokens);

	virtual std::set<std::string> getUsedNames() const;
	virtual std::set<std::string> getDeclaredNames() const;

private:
	std::set<std::string> getUsedNamesFromToken(const std::shared_ptr<const Token> &token) const;

	virtual void replaceToken(const TokenExpression &expression, 
		std::function<std::shared_ptr<Token> (const std::list<std::shared_ptr<Token>> &)> creator);
};
