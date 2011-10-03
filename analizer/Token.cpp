
#include "Token.h"

using namespace std;

Token::Token(const std::string &token)
	: token(token)
{
}

string Token::getText() const
{
	return token;
}
