
#include "Error.h"
#include "Token.h"

using namespace std;

Error::Error(const Token &token, const string &message)
	: locator()
{
	token.determoneLocation(&locator);
}

string Error::what() const 
{
	return locator.toString();
}
