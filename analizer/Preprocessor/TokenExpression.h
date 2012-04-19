
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
	
private:
	typedef std::list<std::shared_ptr<Token>>::iterator token_list_iterator;
	
public:
	std::tuple<bool, token_list_iterator> match(const token_list_iterator &begin,
		const token_list_iterator &end) const;
private:
	const std::vector<TokenPredicate> predicates;

	std::tuple<bool, token_list_iterator> matchIn(const token_list_iterator &begin,
		const token_list_iterator &end, unsigned psi) const;
};
