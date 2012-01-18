
#pragma once

#include <memory>
#include <string>
#include <stdexcept>

class Token;
class Line;

class Error : public std::exception {
public:
	Error(const std::shared_ptr<const Token> &token, const std::string &message);
	virtual ~Error() throw();
	const char *what() const throw();
	
private:
	const std::shared_ptr<const Token> &token;
	const std::string message;
};
