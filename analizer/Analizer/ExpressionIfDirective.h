
#pragma once
#include "Expression.h"

class ExpressionIfDirective : public Expression {
public:
	ExpressionIfDirective(const std::list<std::shared_ptr<Token>> &tokens);

	virtual std::set<std::string> getUsedNames() const;
	virtual std::set<std::string> getDeclaredNames() const;
	
	std::string getDirective() const;
};
