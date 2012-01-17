
#include <boost/assert.hpp>
#include "Error.h"
#include "Token.h"
#include "Line.h"

using namespace std;

Error::Error(const Token &token, const string &message)
	: whatstr(token.getLocation() + " error: " + message + "\n" + token.getTextInString("", ""))
{
}

Error::~Error() throw()
{
}

const char *Error::what() const throw()
{
	return whatstr.c_str();
}
