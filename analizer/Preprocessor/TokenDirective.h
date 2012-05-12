
#pragma once
#include "TokenList.h"

class TokenDirective : public TokenList {
public:
	TokenDirective(const std::list<std::shared_ptr<Token>> &tokens);
	virtual std::string getText() const;

private:
	virtual void replaceToken(const TokenExpression &expression, 
		std::function<std::shared_ptr<Token> (const std::list<std::shared_ptr<Token>> &)> creator);
};
