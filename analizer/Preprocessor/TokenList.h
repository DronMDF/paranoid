
#pragma once
#include <list>
#include <memory>
#include "Token.h"
#include "TokenExpression.h"

class TokenList : public Token {
public:	
	explicit TokenList(const std::list<std::shared_ptr<Token>> &tokens);
	
	virtual std::string getText() const;
	virtual std::string getLocation() const;
	virtual std::string getFileName() const;
	virtual std::shared_ptr<const Line> getLine() const;
	virtual size_t getBeginPos() const;
	virtual size_t getEndPos() const;

	virtual void replaceToken(const TokenExpression &expression, 
		std::function<std::shared_ptr<Token> (const std::list<std::shared_ptr<Token>> &)> creator);
	
	void forEachToken(std::function<void (const std::shared_ptr<const Token> &)> func) const;
	
protected:
	std::list<std::shared_ptr<Token>> tokens;
	
private:
	void replaceTokens(std::list<std::shared_ptr<Token>>::iterator begin, 
		std::list<std::shared_ptr<Token>>::iterator end,
		const std::shared_ptr<Token> &token);
};
