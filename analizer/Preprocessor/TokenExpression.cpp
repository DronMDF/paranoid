
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

// opt	some	match	action
// f	f	f	fail
// f	t	f	mc ? tok++ : fail
// t	t	f	mc ? recur(tok++, pred) or pred++ : tok++
// t	f	f	pred++
// 
// t	f	t	recur(tok++, pred++) or pred++
// f	f	t	tok++, pred++
// t	t	t	mc++, recur(tok++, pred) or tok++
// f	t	t	mc++, tok++
// 
// at pred end: success
// at tok end: fail

tuple<bool, TokenExpression::token_list_iterator> TokenExpression::matchIn(
	const token_list_iterator &begin, const token_list_iterator &end, unsigned psi) const
{
	token_list_iterator current = begin;
	unsigned mc = 0;
	for (unsigned i = psi; i < predicates.size();) {
		const auto predicate = predicates[i];
		const bool is_optional = predicate.isOptional();
		const bool is_some = predicate.isSome();
		if (current == end) {
			if (is_optional or (is_some and mc > 0)) {
				++i;
				continue;
			}
			return make_tuple(false, current);
		}

		const bool is_match = predicate(*current);
		if (is_optional) {
			if (is_match or (!is_match and is_some and mc > 0)) {
				// Check next or this predicate on next token
				auto next = current;
				auto result = matchIn(++next, end, (!is_some) ? i + 1 : i);
				if (get<0>(result)) {
					return result;
				}
			}
			
			// Next predicate on this token
			++i;
			mc = 0;
			continue;
		}
		
		if (!is_match and !is_optional and (!is_some or mc == 0)) {
			return make_tuple(false, current);
		}
		
		if (is_match) {
			++current;
		}
		
		if (is_match and is_some) {
			++mc;
		} else {
			mc = 0;
			++i;
		}
	}
	
	return make_tuple(true, current);
}
