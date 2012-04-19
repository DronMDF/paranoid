
#include "TokenExpression.h"
#include "TokenPredicate.h"

using namespace std; 

TokenExpression::TokenExpression(const initializer_list<TokenPredicate> &expr)
	: predicates(expr.begin(), expr.end())
{
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
				auto result = matchIn(++next, end, is_some ? i : i + 1);
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
