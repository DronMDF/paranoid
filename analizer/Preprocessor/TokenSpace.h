
#pragma once

#include <string>
#include "Token.h"

class TokenSpace : public Token {
public:
	virtual std::string getText() const;
	virtual std::string getLocation() const;
	virtual std::string getTextInString(const std::string &begin_marker = std::string(), 
				    const std::string &end_marker = std::string()) const;
};
