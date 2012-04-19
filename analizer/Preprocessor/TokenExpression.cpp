
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
		const auto is_optional = predicate.isOptional();
		if (current == end) {
			if (is_optional) {
				++i;
				continue;
			}
			return make_tuple(false, current);
		}

		const auto is_match = predicate(*current);
		const auto is_some = predicate.isSome();

		if (!is_match) {
			if (!is_optional) {
				if (!is_some or mc == 0) {
					return make_tuple(false, current);
				}
			} else {
				if (is_some) {
					if (mc == 0) {
						mc = 0;
						++i;
						continue;
					}
					
					auto next = current;
					auto result = matchIn(++next, end, i);
					if (get<0>(result)) {
						return result;
					}
				} 
			}
			mc = 0;
			++i;
			continue;
		}
		
		if (!is_some) {
			if (is_optional) {
				auto next = current;
				auto result = matchIn(++next, end, i + 1);
				if (get<0>(result)) {
					return result;
				}
			} else {
				++current;
			}
			mc = 0;
			++i;
			continue;
		}
		
		if (is_optional) {
			auto next = current;
			auto result = matchIn(++next, end, i);
			if (get<0>(result)) {
				return result;
			}
			
			mc = 0;
			++i;
			continue;
		}
		
		++mc;
		++current;
	}
	
	return make_tuple(true, current);
}
