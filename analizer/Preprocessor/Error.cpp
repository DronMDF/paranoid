
#include "Error.h"
#include "Token.h"

using namespace std;

Error::Error(const Token &token, const string &message)
	: location(token.getLocation()), message(message), text(token.getTextInString()), whatstr()
{
	whatstr = location + " error: " + message + "\n" + text;
}

Error::~Error() throw()
{
}

const char *Error::what() const throw()
{
	return whatstr.c_str();
}
