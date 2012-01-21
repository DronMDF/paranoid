
#include "Error.h"
#include "Token.h"

using namespace std;

Error::Error(const shared_ptr<const Token> &token, const string &message)
	: token(token), message(message)
{
}

string Error::what() const
{
	return token->getLocation() + " error: " + message + "\n" + token->getTextInString("", "");
}
