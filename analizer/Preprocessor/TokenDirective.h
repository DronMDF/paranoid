
#pragma once
#include "TokenList.h"

class TokenDirective : public TokenList {
public:
	TokenDirective(const std::list<std::shared_ptr<const Token>> &tokens);
	virtual std::string getText() const;
};
