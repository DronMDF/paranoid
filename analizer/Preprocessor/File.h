
#pragma once
#include <list>
#include <memory>
#include <string>
#include "TokenExpression.h"
#include "TokenList.h"

class Line;
class Preprocessor;
class Token;
class TokenInclude;

// TODO: protected inheritance cause error in FileStub
class File : protected TokenList {
public:
	File(const std::string &filename);
	virtual ~File();
	
	void tokenize();
	
	virtual std::string getLocation() const;
	virtual std::string getFileName() const;
	
	void includedFrom(const std::shared_ptr<const TokenInclude> &token);

	using TokenList::replaceToken;
	// TODO: перенести в TokenList
	virtual void forEachToken(std::function<void (const std::shared_ptr<const Token> &)> func) const;
	
private:
	const std::string filename;
	std::list<std::shared_ptr<const Token>> included_from;
	
	virtual void forEachLine(std::function<void (const std::shared_ptr<const Line> &)> lineparser) const;
};
