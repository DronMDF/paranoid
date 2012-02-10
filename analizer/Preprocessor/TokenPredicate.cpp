
#include "Token.h"
#include "TokenNewline.h"
#include "TokenPredicate.h"
#include "TokenSpace.h"

using namespace std;

// TokenPredicateImpl
class TokenPredicateImpl {
public:
	virtual ~TokenPredicateImpl();
	virtual bool match(const std::shared_ptr<const Token> &token) const = 0;
};

TokenPredicateImpl::~TokenPredicateImpl() = default;

// TokenPredicateText
class TokenPredicateEqual : public TokenPredicateImpl {
private:
	const std::string text;
public:
	TokenPredicateEqual(const char *text) : text(text) {
	}

	virtual bool match(const std::shared_ptr<const Token> &token) const {
		return token->getText() == text;
	}
};

// TokenPredicateNot
class TokenPredicateNot : public TokenPredicateImpl {
private:
	const TokenPredicate predicate;
public:
	TokenPredicateNot(const TokenPredicate &predicate) : predicate(predicate) {
	}

	bool match(const shared_ptr<const Token> &token) const {
		return !predicate(token);
	}
};

// TokenPredicateSome
class TokenPredicateSome : public TokenPredicateImpl {
private:
	const TokenPredicate predicate;
public:
	TokenPredicateSome(const TokenPredicate &predicate) : predicate(predicate) {
	}

	bool match(const shared_ptr<const Token> &token) const {
		return predicate(token);
	}
};

// TokenPredicateTyped
template<typename T>
class TokenPredicateTyped : public TokenPredicateImpl {
public:
	virtual bool match(const std::shared_ptr<const Token> &token) const {
		return dynamic_cast<const T *>(token.get()) != 0;
	}
};

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
	: impl(make_shared<TokenPredicateEqual>(text))
{
}

bool TokenPredicate::operator()(const shared_ptr<const Token> &token) const {
	return impl->match(token);
}

// TokenPredicate generators
TokenPredicate Not(const TokenPredicate &predicate) {
	return TokenPredicate(make_shared<TokenPredicateNot>(predicate));
}

TokenPredicate Some(const TokenPredicate &predicate) {
	return TokenPredicate(make_shared<TokenPredicateSome>(predicate));
}

const TokenPredicate isSpace(make_shared<TokenPredicateTyped<TokenSpace>>());
const TokenPredicate isEol(make_shared<TokenPredicateTyped<TokenNewline>>());
