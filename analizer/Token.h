
#pragma once

#include <string>

class Token {
public:
	explicit Token(const std::string &tok);
	std::string getText() const;
	
private:
	std::string token;
};
