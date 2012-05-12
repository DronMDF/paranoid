
#include "Token.h"
#include "TokenNewline.h"
#include "TokenPredicate.h"
#include "TokenSpace.h"
#include "TokenWord.h"

using namespace std;

/// TokenPredicateImpl
TokenPredicateImpl::~TokenPredicateImpl() = default;

bool TokenPredicateImpl::isSome() const {
	return false;
}

bool TokenPredicateImpl::isOptional() const {
	return false;
}

/// TokenPredicateEqual
class TokenPredicateEqual : public TokenPredicateImpl {
private:
	const string text;
public:
	TokenPredicateEqual(const char *text) : text(text) {
	}

	virtual bool match(const shared_ptr<const Token> &token) const {
		return token->getText() == text;
	}
};

/// TokenPredicateNot
class TokenPredicateNot : public TokenPredicateImpl {
private:
	const TokenPredicate predicate;
public:
	TokenPredicateNot(const TokenPredicate &predicate) : predicate(predicate) {
	}

	virtual bool match(const shared_ptr<const Token> &token) const {
		return !predicate(token);
	}
};

/// TokenPredicateSome
class TokenPredicateSome : public TokenPredicateImpl {
private:
	const TokenPredicate predicate;
public:
	TokenPredicateSome(const TokenPredicate &predicate) : predicate(predicate) {
	}

	virtual bool match(const shared_ptr<const Token> &token) const {
		return predicate(token);
	}

	virtual bool isSome() const {
		return true;
	}

	virtual bool isOptional() const {
		return predicate.isOptional();
	}
};

/// TokenPredicateOptional
class TokenPredicateOptional : public TokenPredicateImpl {
private:
	const TokenPredicate predicate;
public:
	TokenPredicateOptional(const TokenPredicate &predicate) : predicate(predicate) {
	}

	virtual bool match(const shared_ptr<const Token> &token) const {
		return predicate(token);
	}

	virtual bool isSome() const {
		return predicate.isSome();
	}

	virtual bool isOptional() const {
		return true;
	}
};

/// TokenPredicateOr
class TokenPredicateOr : public TokenPredicateImpl {
private:
	const TokenPredicate predicate1;
	const TokenPredicate predicate2;
public:
	TokenPredicateOr(const TokenPredicate &predicate1, const TokenPredicate &predicate2)
		: predicate1(predicate1), predicate2(predicate2)
	{
	}

	virtual bool match(const shared_ptr<const Token> &token) const {
		if (predicate1(token)) { return true; }
		return predicate2(token);
	}

	virtual bool isSome() const {
		return predicate1.isSome() and predicate2.isSome();
	}

	virtual bool isOptional() const {
		return predicate1.isOptional() and predicate2.isOptional();
	}
};

/// TokenPredicate
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

bool TokenPredicate::isSome() const {
	return impl->isSome();
}

bool TokenPredicate::isOptional() const {
	return impl->isOptional();
}

/// TokenPredicate generators
TokenPredicate Not(const TokenPredicate &predicate) {
	return TokenPredicate(make_shared<TokenPredicateNot>(predicate));
}

TokenPredicate Some(const TokenPredicate &predicate) {
	return TokenPredicate(make_shared<TokenPredicateSome>(predicate));
}

TokenPredicate Optional(const TokenPredicate &predicate) {
	return TokenPredicate(make_shared<TokenPredicateOptional>(predicate));
}

TokenPredicate Or(const TokenPredicate &predicate1, const TokenPredicate &predicate2) {
	return TokenPredicate(make_shared<TokenPredicateOr>(predicate1, predicate2));
}


const TokenPredicate isSpace = isType<TokenSpace>();
const TokenPredicate isWord = isType<TokenWord>();
const TokenPredicate isEol = isType<TokenNewline>();
