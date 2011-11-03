
#include <boost/assert.hpp>
#include "Error.h"
#include "Token.h"
#include "Line.h"

using namespace std;

Error::Error(const Token &token, const string &message)
	: whatstr(token.getLocation() + " error: " + message + "\n" + 
		token.getTextInString("\033[1;31m", "\033[0m"))
{
}

Error::Error(const Line &line, string::size_type begin, string::size_type end, const string &message)
	: whatstr(line.getLocation() + " error: " + message + "\n")
{
	BOOST_ASSERT(end == string::npos || begin < end);
	BOOST_ASSERT(begin < line.getText().size());
	BOOST_ASSERT(end == string::npos || end <= line.getText().size());
	
	string text = line.getText();
	if (end == string::npos) {
		text.append("\033[0m");
	} else {
		text.insert(end, "\033[0m");
	}
	text.insert(begin, "\033[1;31m");
	whatstr += text;
}

Error::~Error() throw()
{
}

const char *Error::what() const throw()
{
	return whatstr.c_str();
}
