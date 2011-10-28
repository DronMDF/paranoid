
#include "Error.h"
#include "Token.h"

using namespace std;

Error::Error(const Token &token, const string &message)
	: location(token.getLocation()), message(message), text(token.getTextInString())
{
}

string Error::what() const 
{
	return location + " error: " + message + "\n" + text;
}
