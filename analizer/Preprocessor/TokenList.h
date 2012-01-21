
#pragma once
#include <list>
#include <memory>
#include "Token.h"

class TokenList : public Token {
public:	
	TokenList(const std::list<std::shared_ptr<const Token>> &tokens);
	
	virtual std::string getText() const;
	virtual std::string getLocation() const;
	virtual std::string getFileName() const;
	virtual std::shared_ptr<const Line> getLine() const;
	virtual size_t getBeginPos() const;
	virtual size_t getEndPos() const;

protected:
	const std::list<std::shared_ptr<const Token>> tokens;
};
