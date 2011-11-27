
#pragma once
#include "TokenList.h"

class File;

class TokenInclude : public TokenList {
public:
	TokenInclude(const std::list<std::shared_ptr<const Token>> &tokens, const std::shared_ptr<const File> &file);

};
