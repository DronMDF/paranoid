
#pragma once

#include <initializer_list>
#include <memory>
#include <vector>
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
	
	// stateless api
	template<typename TI>
	std::tuple<bool, TI> match(TI begin, const TI &end) const {
		BOOST_FOREACH(auto &predicate, predicates) {
			if (begin == end) {
				return make_tuple(false, begin);
			}
			
			if (!predicate(*begin)) {
				if (predicate.isOptional()) {
					continue;
				}
				return make_tuple(false, begin);
			}
			
			do {
				++begin;
			} while (predicate.isSome() and begin != end and predicate(*begin));
		}
		return make_tuple(true, begin);
	}
private:
	const std::vector<TokenPredicate> predicates;
	unsigned position;
	unsigned quantity;
	
	unsigned requiredPosition(const std::shared_ptr<const Token> &token, unsigned position) const;
};
