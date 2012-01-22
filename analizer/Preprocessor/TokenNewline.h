
#pragma once

#include <string>
#include <memory>
#include "Token.h"

class Line;

class TokenNewline : public Token {
public:
	TokenNewline(const std::shared_ptr<const Line> &line);
	
	virtual std::string getText() const;
	virtual std::string getLocation() const;
	virtual std::string getFileName() const;
	virtual std::shared_ptr<const Line> getLine() const;
	virtual size_t getBeginPos() const;
	virtual size_t getEndPos() const;
	
private:
	const std::shared_ptr<const Line> line;
};
