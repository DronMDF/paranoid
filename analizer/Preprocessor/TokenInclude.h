
#pragma once
#include "TokenList.h"

class File;

class TokenInclude : public TokenList {
public:
	explicit TokenInclude(const std::list<std::shared_ptr<const Token>> &tokens);

	void include(const std::shared_ptr<const File> &file);
	std::shared_ptr<const File> getIncludedFile() const;
		
	bool isSystem() const;
	std::string getHeaderName() const;
	
private:
	std::shared_ptr<const File> file;
};
