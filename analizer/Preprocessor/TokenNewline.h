
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
	virtual std::string getTextInString(const std::string &begin_marker = std::string(), 
				    const std::string &end_marker = std::string()) const;
};
