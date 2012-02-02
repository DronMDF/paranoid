
#include "TokenExpression.h"

using namespace std; 

TokenExpression::TokenExpression(const list<TokenPredicate> &expr)
{
}
	
TokenExpression::status TokenExpression::match(const shared_ptr<const Token> &token)
{
	return status::error;
}
