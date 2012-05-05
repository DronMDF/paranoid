
#pragma once
#include <list>
#include <memory>
#include "IncludeUsageProxy.h"

class Token;

class AnalizeInclude {
public:
	AnalizeInclude();

	void checkToken(const std::shared_ptr<const Token> &token, 
		const std::shared_ptr<const IncludedFile> &file);
	std::list<std::shared_ptr<const Token>> getUnused() const;
	
private:
	std::list<IncludeUsageProxy> includes;
};
