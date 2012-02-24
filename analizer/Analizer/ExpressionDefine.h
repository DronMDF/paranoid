
#pragma once
#include <Preprocessor/TokenList.h>

class ExpressionDefine : public TokenList {
public:
	ExpressionDefine(const std::list<std::shared_ptr<const Token>> &tokens);

	std::list<std::string> getUsedNamesFromToken(const std::shared_ptr<const Token> &token) const;
	std::list<std::string> getUsedNames() const;
};
