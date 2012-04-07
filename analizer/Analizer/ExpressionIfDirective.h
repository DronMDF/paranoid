
#pragma once
#include <set>
#include <Preprocessor/TokenList.h>

class ExpressionIfDirective : public TokenList {
public:
	ExpressionIfDirective(const std::list<std::shared_ptr<const Token>> &tokens);

	std::set<std::string> getUsedNames() const;
	std::set<std::string> getDeclaredNames() const;
};
