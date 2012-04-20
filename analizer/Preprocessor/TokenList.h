
#pragma once
#include <list>
#include <memory>
#include "Token.h"
#include "TokenExpression.h"

class TokenList : public Token {
private:
	typedef std::shared_ptr<Token> token_ptr;
	
public:	
	explicit TokenList(const std::list<token_ptr> &tokens);
	
	virtual std::string getText() const;
	virtual std::string getLocation() const;
	virtual std::string getFileName() const;
	virtual std::shared_ptr<const Line> getLine() const;
	virtual size_t getBeginPos() const;
	virtual size_t getEndPos() const;

	virtual void replaceToken(const TokenExpression &expression, 
		std::function<token_ptr (const std::list<token_ptr> &)> creator);
	
	void forEachToken(std::function<void (const std::shared_ptr<const Token> &)> func) const;
	
protected:
	std::list<token_ptr> tokens;
	
private:
	void replaceTokens(std::list<token_ptr>::iterator begin, 
		std::list<token_ptr>::iterator end, const token_ptr &token);
	bool replaceTokenPass(const TokenExpression &expression, 
		std::function<token_ptr (const std::list<token_ptr> &)> creator);
};
