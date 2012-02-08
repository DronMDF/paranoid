
#include "TokenExpression.h"
#include "TokenPredicate.h"

using namespace std; 

TokenExpression::TokenExpression(const initializer_list<TokenPredicate> &expr)
	: predicates(expr.begin(), expr.end()), position(0)
{
}

// This is not good solution, mutable state :(
// Need to keep state outside of expression...
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

bool TokenExpression::isMatched() const
{
	return position >= predicates.size();
}

void TokenExpression::reset()
{
	position = 0;
}
