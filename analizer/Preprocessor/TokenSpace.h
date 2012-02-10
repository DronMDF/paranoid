
#pragma once
#include "Token.h"

class TokenSpace : public Token {
public:
	TokenSpace(const std::shared_ptr<const Line> &line, 
		  std::string::size_type begin, std::string::size_type end);
	
	virtual std::string getText() const;
	virtual std::string getLocation() const;
	virtual std::string getFileName() const;
	virtual std::shared_ptr<const Line> getLine() const;
	virtual size_t getBeginPos() const;
	virtual size_t getEndPos() const;

private:
	const std::shared_ptr<const Line> line;
	std::string::size_type begin;
	std::string::size_type end;
};
