
#pragma once
#include <set>
#include <Preprocessor/TokenList.h>

class ExpressionDefine : public TokenList {
public:
	ExpressionDefine(const std::list<std::shared_ptr<const Token>> &tokens);

	std::set<std::string> getUsedNames() const;

private:
	std::set<std::string> getUsedNamesFromToken(const std::shared_ptr<const Token> &token) const;
};
