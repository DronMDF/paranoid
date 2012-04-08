
#pragma once
#include "Expression.h"

class ExpressionIfDirective : public Expression {
public:
	ExpressionIfDirective(const std::list<std::shared_ptr<const Token>> &tokens);

	std::set<std::string> getUsedNames() const;
	std::set<std::string> getDeclaredNames() const;
};
