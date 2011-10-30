
#include "Error.h"
#include "Token.h"

using namespace std;

Error::Error(const Token &token, const string &message)
	: whatstr(token.getLocation() + " error: " + message + "\n" + 
		token.getTextInString("\033[1;31m", "\033[0m"))
{
}

Error::~Error() throw()
{
}

const char *Error::what() const throw()
{
	return whatstr.c_str();
}
