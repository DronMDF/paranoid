
#pragma once
#include <list>
#include <memory>
#include "Token.h"

class TokenList : public Token {
public:	
	TokenList(const std::list<std::shared_ptr<const Token>> &tokens);
	
	virtual std::string getText() const;
	virtual std::string getLocation() const;
	virtual std::string getTextInString(const std::string &begin_marker = std::string(), 
				    const std::string &end_marker = std::string()) const;
};
