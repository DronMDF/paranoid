
#pragma once

#include <initializer_list>
#include <memory>
#include <vector>
#include <list>
#include <boost/foreach.hpp>
#include "TokenPredicate.h"

class Token;

class TokenExpression {
public:
	TokenExpression() = delete;
	TokenExpression(const std::initializer_list<TokenPredicate> &expr);
	
	bool match(const std::shared_ptr<const Token> &token);
	bool isMatched() const;
	void reset();
	
	std::tuple<bool, std::list<std::shared_ptr<Token>>::iterator> match(
		const std::list<std::shared_ptr<Token>>::iterator &begin, 
		const std::list<std::shared_ptr<Token>>::iterator &end) const 
	{
		std::list<std::shared_ptr<Token>>::iterator current = begin;
		BOOST_FOREACH(auto &predicate, predicates) {
			if (current == end) {
				return make_tuple(false, current);
			}
			
			if (!predicate(*current)) {
				if (predicate.isOptional()) {
					continue;
				}
				return make_tuple(false, current);
			}
			
			do {
				++current;
			} while (predicate.isSome() and current != end and predicate(*current));
		}
		return make_tuple(true, current);
	}
private:
	const std::vector<TokenPredicate> predicates;
	unsigned position;
	unsigned quantity;
	
	unsigned requiredPosition(const std::shared_ptr<const Token> &token, unsigned position) const;
};
