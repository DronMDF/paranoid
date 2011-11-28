
#pragma once
#include "TokenList.h"

class File;

class TokenInclude : public TokenList {
public:
	explicit TokenInclude(const std::list<std::shared_ptr<const Token>> &tokens);

	void include(const std::shared_ptr<const File> &file);
};
