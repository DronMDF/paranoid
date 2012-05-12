
#pragma once
#include <memory>
#include <string>

class Token;

class TokenPredicateImpl {
public:
	virtual ~TokenPredicateImpl();
	virtual bool match(const std::shared_ptr<const Token> &token) const = 0;
	virtual bool isSome() const;
	virtual bool isOptional() const;
};

class TokenPredicate {
public:
	TokenPredicate() = delete;
	TokenPredicate(const TokenPredicate &predicate);
	TokenPredicate(const std::shared_ptr<TokenPredicateImpl> &impl);
	TokenPredicate(const char *text);
	
	bool operator()(const std::shared_ptr<const Token> &token) const;
	bool isSome() const;
	bool isOptional() const;

private:
	std::shared_ptr<TokenPredicateImpl> impl;
};

TokenPredicate Not(const TokenPredicate &predicate);
TokenPredicate Some(const TokenPredicate &predicate);
TokenPredicate Optional(const TokenPredicate &predicate);
TokenPredicate Or(const TokenPredicate &predicate1, const TokenPredicate &predicate2);

template<typename T>
class TokenPredicateTyped : public TokenPredicateImpl {
public:
	virtual bool match(const std::shared_ptr<const Token> &token) const {
		return bool(std::dynamic_pointer_cast<const T>(token));
	}
};

template <typename T>
TokenPredicate isType() {
	return TokenPredicate(std::make_shared<TokenPredicateTyped<T>>());
}

extern const TokenPredicate isSpace;
extern const TokenPredicate isWord;
extern const TokenPredicate isEol;
