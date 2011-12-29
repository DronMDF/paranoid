
#include <boost/assert.hpp>
#include "Error.h"
#include "Token.h"
#include "Line.h"

using namespace std;

Error::Error(const Token &token, const string &message)
	: whatstr(token.getLocation() + " error: " + message + "\n" + token.getTextInString("", ""))
{
}

Error::Error(const Line &line, string::size_type begin, string::size_type end, const string &message)
	: whatstr(line.getLocation() + " error: " + message + "\n")
{
	BOOST_ASSERT(end == string::npos || begin < end);
	BOOST_ASSERT(begin < line.getText().size());
	BOOST_ASSERT(end == string::npos || end <= line.getText().size());
	
	whatstr += line.getText();
}

Error::~Error() throw()
{
}

const char *Error::what() const throw()
{
	return whatstr.c_str();
}
