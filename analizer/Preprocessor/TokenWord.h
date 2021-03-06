
#pragma once

#include <memory>
#include <string>
#include "Token.h"

class Line;

class TokenWord : public Token {
public:
	TokenWord(const std::shared_ptr<const Line> &line, 
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
