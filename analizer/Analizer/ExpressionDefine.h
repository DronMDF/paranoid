
#pragma once
#include "Expression.h"

class ExpressionDefine : public Expression {
public:
	ExpressionDefine(const std::list<std::shared_ptr<const Token>> &tokens);

	virtual std::set<std::string> getUsedNames() const;
	virtual std::set<std::string> getDeclaredNames() const;

private:
	std::set<std::string> getUsedNamesFromToken(const std::shared_ptr<const Token> &token) const;
};
