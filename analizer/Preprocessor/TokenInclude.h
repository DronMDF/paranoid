
#pragma once
#include "TokenList.h"

class File;

class TokenInclude : public TokenList {
public:
	explicit TokenInclude(const std::list<std::shared_ptr<Token>> &tokens);

	void include(const std::shared_ptr<const File> &file);
	std::shared_ptr<const File> getIncludedFile() const;
		
	bool isSystem() const;
	std::string getHeaderName() const;
	
private:
	std::shared_ptr<const File> file;

	virtual void replaceToken(const TokenExpression &expression, 
		std::function<std::shared_ptr<Token> (const std::list<std::shared_ptr<Token>> &)> creator);
};
