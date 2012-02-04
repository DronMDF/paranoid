
#include "Token.h"
#include "TokenPredicate.h"

using namespace std;

// TokenPredicateImpl
class TokenPredicateImpl {
public:
	TokenPredicateImpl(const char *text);
	bool match(const std::shared_ptr<Token> &token) const;
	
protected:
	const std::string text;
};

TokenPredicateImpl::TokenPredicateImpl(const char *text)
	: text(text)
{
}
	
bool TokenPredicateImpl::match(const std::shared_ptr<Token> &token) const
{
	return token->getText() == text;
}

// TokenPredicate
TokenPredicate::TokenPredicate(const char *text)
	: predicate(shared_ptr<TokenPredicateImpl>(new TokenPredicateImpl(text)))
{
}

bool TokenPredicate::operator()(const shared_ptr<Token> &token) const
{
	return predicate->match(token);
}

// TokenPredicate generators
TokenPredicate Not(const TokenPredicate &pred)
{
	return TokenPredicate("noop");
}
