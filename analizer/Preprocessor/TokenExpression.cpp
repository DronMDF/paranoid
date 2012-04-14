
#include "TokenExpression.h"
#include "TokenPredicate.h"

using namespace std; 

TokenExpression::TokenExpression(const initializer_list<TokenPredicate> &expr)
	: predicates(expr.begin(), expr.end()), position(0), quantity(0)
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
		quantity++;
		if (!predicates[position].isSome()) {
			position++;
			quantity = 0;
		}
		
		return true;
	} else {
		if (quantity > 0) {
			position++;
			quantity = 0;
			return match(token);
		}

		if (predicates[position].isOptional()) {
			position++;
			return match(token);
		}
	}
	
	return false;
}

bool TokenExpression::isMatched() const
{
	unsigned last_position = position;
	while (last_position < predicates.size() && predicates[last_position].isOptional()) {
		last_position++;
	}
	
	return last_position >= predicates.size();
}

void TokenExpression::reset()
{
	position = 0;
	quantity = 0;
}
