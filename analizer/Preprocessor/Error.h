
#pragma once

#include <string>
#include <stdexcept>

class Token;

class Error : public std::exception {
public:
	Error(const Token &token, const std::string &message);
	virtual ~Error() throw();
	const char *what() const throw();
	
private:
	std::string location;
	std::string message;
	std::string text;
	std::string whatstr;
};
