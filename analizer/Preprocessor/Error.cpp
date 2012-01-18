
#include <boost/assert.hpp>
#include "Error.h"
#include "Token.h"
#include "Line.h"

using namespace std;

Error::Error(const shared_ptr<const Token> &token, const string &message)
	: token(token), message(message)
{
}

Error::~Error() throw()
{
}

const char *Error::what() const throw()
{
	static string fm = token->getLocation() + " error: " + message + "\n" + token->getTextInString("", "");
	return fm.c_str();
}
