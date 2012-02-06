
#include "TokenExpression.h"
#include "TokenPredicate.h"

using namespace std; 

TokenExpression::TokenExpression(const list<TokenPredicate> &expr)
	: predicates(expr.begin(), expr.end()), position(0)
{
}
	
bool TokenExpression::match(const shared_ptr<const Token> &token)
{
	if (position >= predicates.size()) {
		// This is successefull false
		return false;
	}
	
	if (predicates[position](token)) {
		position++;
		return true;
	}
	
	return false;
}
