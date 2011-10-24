
#include "Error.h"

using namespace std;

Error::Error(const Token &/*token*/, const string &/*message*/)
{
}

string Error::what() const 
{
	return string();
} 