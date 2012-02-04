
#include "Token.h"
#include "TokenPredicate.h"

using namespace std;

// TokenPredicateImpl
class TokenPredicateImpl {
public:
	virtual ~TokenPredicateImpl();
	virtual bool match(const std::shared_ptr<Token> &token) const = 0;
};

TokenPredicateImpl::~TokenPredicateImpl() = default;

// TokenPredicateText
class TokenPredicateEqual : public TokenPredicateImpl {
public:
	TokenPredicateEqual(const char *text);
	virtual bool match(const std::shared_ptr<Token> &token) const;
	
protected:
	const std::string text;
};

TokenPredicateEqual::TokenPredicateEqual(const char *text)
	: text(text)
{
}
	
bool TokenPredicateEqual::match(const std::shared_ptr<Token> &token) const
{
	return token->getText() == text;
}

// TokenPredicateNot
class TokenPredicateNot : public TokenPredicateImpl {
public:
	TokenPredicateNot(const TokenPredicate &predicate);
	bool match(const std::shared_ptr<Token> &token) const;
private:
	const TokenPredicate predicate;
};

TokenPredicateNot::TokenPredicateNot(const TokenPredicate &predicate)
	: predicate(predicate)
{
}

bool TokenPredicateNot::match(const std::shared_ptr<Token> &token) const
{
	return !predicate(token);
}

// TokenPredicate
TokenPredicate::TokenPredicate(const TokenPredicate &predicate)
	: impl(predicate.impl)
{
}

TokenPredicate::TokenPredicate(const shared_ptr<TokenPredicateImpl> &impl)
	: impl(impl)
{
}

TokenPredicate::TokenPredicate(const char *text)
	: impl(shared_ptr<TokenPredicateImpl>(new TokenPredicateEqual(text)))
{
}

bool TokenPredicate::operator()(const shared_ptr<Token> &token) const
{
	return impl->match(token);
}

// TokenPredicate generators
TokenPredicate Not(const TokenPredicate &predicate)
{
	return TokenPredicate(shared_ptr<TokenPredicateImpl>(new TokenPredicateNot(predicate)));
}
