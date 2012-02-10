
#include "Token.h"
#include "TokenNewline.h"
#include "TokenPredicate.h"
#include "TokenSpace.h"
#include "TokenWord.h"

using namespace std;

class TokenPredicateImpl {
public:
	virtual ~TokenPredicateImpl();
	virtual bool match(const std::shared_ptr<const Token> &token) const = 0;

	virtual bool isSome() const{
		return false;
	}

	virtual bool isOptional() const{
		return false;
	}
};

TokenPredicateImpl::~TokenPredicateImpl() = default;

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

class TokenPredicateSome : public TokenPredicateImpl {
private:
	const TokenPredicate predicate;
public:
	TokenPredicateSome(const TokenPredicate &predicate) : predicate(predicate) {
	}

	virtual bool match(const shared_ptr<const Token> &token) const {
		return predicate(token);
	}

	virtual bool isSome() const{
		return true;
	}

	virtual bool isOptional() const{
		return predicate.isOptional();
	}
};

class TokenPredicateOptional : public TokenPredicateImpl {
private:
	const TokenPredicate predicate;
public:
	TokenPredicateOptional(const TokenPredicate &predicate) : predicate(predicate) {
	}

	virtual bool match(const shared_ptr<const Token> &token) const {
		return predicate(token);
	}

	virtual bool isSome() const{
		return predicate.isSome();
	}

	virtual bool isOptional() const{
		return true;
	}
};

template<typename T>
class TokenPredicateTyped : public TokenPredicateImpl {
public:
	virtual bool match(const std::shared_ptr<const Token> &token) const {
		return dynamic_cast<const T *>(token.get()) != 0;
	}
};

// TokenPredicate impl
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

// TokenPredicate generators
TokenPredicate Not(const TokenPredicate &predicate) {
	return TokenPredicate(make_shared<TokenPredicateNot>(predicate));
}

TokenPredicate Some(const TokenPredicate &predicate) {
	return TokenPredicate(make_shared<TokenPredicateSome>(predicate));
}

TokenPredicate Optional(const TokenPredicate &predicate) {
	return TokenPredicate(make_shared<TokenPredicateOptional>(predicate));
}

const TokenPredicate isSpace(make_shared<TokenPredicateTyped<TokenSpace>>());
const TokenPredicate isWord(make_shared<TokenPredicateTyped<TokenWord>>());
const TokenPredicate isEol(make_shared<TokenPredicateTyped<TokenNewline>>());
