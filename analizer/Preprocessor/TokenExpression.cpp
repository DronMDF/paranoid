
#include "TokenExpression.h"
#include "TokenPredicate.h"

using namespace std; 

TokenExpression::TokenExpression(const initializer_list<TokenPredicate> &expr)
	: predicates(expr.begin(), expr.end()), position(0), quantity(0)
{
}

unsigned TokenExpression::requiredPosition(const shared_ptr<const Token> &token, unsigned position) const
{
	if (predicates[position].isOptional() and position + 1 < predicates.size()) {
		auto rpos = requiredPosition(token, position + 1);
		if (rpos > position) {
			return rpos;
		}
	}
	
	if (predicates[position](token)) {
		return position;
	}
	
	return 0;
}

// This is not good solution, mutable state :(
// Need to keep state outside of expression...
bool TokenExpression::match(const shared_ptr<const Token> &token)
{
	if (position >= predicates.size()) {
		// This is successefull false
		return false;
	}
	
	auto rpos = requiredPosition(token, position);
	if (rpos > 0) {
		position = rpos;
		quantity = 0;
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

tuple<bool, TokenExpression::token_list_iterator> TokenExpression::match(
	const token_list_iterator &begin, const token_list_iterator &end) const
{
	return matchIn(begin, end, 0);
}

tuple<bool, TokenExpression::token_list_iterator> TokenExpression::matchIn(
	const token_list_iterator &begin, const token_list_iterator &end, unsigned psi) const
{
	token_list_iterator current = begin;
	unsigned matched = 0;
	for (unsigned i = psi; i < predicates.size();) {
		if (current == end) {
			return make_tuple(false, current);
		}
		
		auto &predicate = predicates[i];
		if (predicate.isOptional()) {
			if (predicate(*current)) {
				auto next = current;
				++next;
				auto result = matchIn(next, end, i);
				if (get<0>(result)) {
					return result;
				}
			}
			
			++i;
			continue;
		}
		
		if (!predicate(*current)) {
			if (matched == 0) {
				return make_tuple(false, current);
			}
			
			++i;
			matched = 0;
			++current;
			continue;
		}
		
		++current;
		++matched;
		if (!predicate.isSome()) {
			++i;
			matched = 0;
		}
	}
	
	return make_tuple(true, current);
}
