
#pragma once
#include <set>
#include <Preprocessor/TokenList.h>

class Expression : public TokenList {
public:
	Expression(const std::list<std::shared_ptr<Token>> &tokens)
		: TokenList(tokens)
	{
	}
	
	virtual std::set<std::string> getUsedNames() const = 0;
	virtual std::set<std::string> getDeclaredNames() const = 0;
};
