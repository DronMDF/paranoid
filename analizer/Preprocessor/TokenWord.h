
#pragma once

#include "Token.h"

class TokenWord : public Token {
public:
	TokenWord(const std::shared_ptr<const Line> &line, unsigned begin, unsigned end);
};
