
#pragma once

#include <list>
#include <memory>
#include <string>
#include "TokenExpression.h"

class Line;
class Preprocessor;
class Token;
class TokenInclude;

class File {
public:
	File(const std::string &filename);
	virtual ~File();
	
	void tokenize();
	
	virtual std::string getLocation() const;
	virtual std::string getFileName() const;
	virtual void forEachToken(std::function<void (const std::shared_ptr<const Token> &)> func) const;
	
	void includedFrom(const std::shared_ptr<const TokenInclude> &token);
	
	void replaceToken(TokenExpression expression,
		std::function<std::shared_ptr<Token> (const std::list<std::shared_ptr<Token>> &)> creator);
	
private:
	const std::string filename;

	typedef std::list<std::shared_ptr<Token>>::iterator tokens_iterator;
	std::list<std::shared_ptr<Token>> tokens;
	std::list<std::shared_ptr<const Token>> included_from;
	
	virtual void forEachLine(std::function<void (const std::shared_ptr<const Line> &)> lineparser) const;
	void replaceTokens(tokens_iterator begin, tokens_iterator end, const std::shared_ptr<Token> &token);
};
