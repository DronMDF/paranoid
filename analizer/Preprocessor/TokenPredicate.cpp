
#include "Token.h"
#include "TokenPredicate.h"

using namespace std;

TokenPredicate::TokenPredicate(const char *text)
	: text(text), except(false)
{
}

TokenPredicate::TokenPredicate(const TokenPredicate &predicate, bool except)
	: text(predicate.text), except(except)
{
}

TokenPredicate::~TokenPredicate() = default;

bool TokenPredicate::operator()(const shared_ptr<Token> &token) const
{
	if (except) {
		return token->getText() != text;
	}
	
	return token->getText() == text;
}

TokenPredicateNot::TokenPredicateNot(const TokenPredicate &pred)
	: TokenPredicate(pred, true)
{
}
