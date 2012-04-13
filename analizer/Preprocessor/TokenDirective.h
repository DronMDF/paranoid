
#pragma once
#include "TokenList.h"

class TokenDirective : public TokenList {
public:
	TokenDirective(const std::list<std::shared_ptr<Token>> &tokens);
	virtual std::string getText() const;
};
