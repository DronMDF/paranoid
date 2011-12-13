
#pragma once

#include <list>
#include <memory>
#include <string>
#include "Location.h"

class Line;
class Preprocessor;
class Token;
class TokenInclude;

class File : public Location {
public:
	File(const std::string &filename);
	virtual ~File();
	
	void tokenize(std::function<void (const std::shared_ptr<TokenInclude> &)> include);
	
	virtual std::string getLocation() const;
	virtual void getTokens(std::function<void (const std::shared_ptr<const Token> &)> add_token) const;
	
	void includedFrom(const std::shared_ptr<const TokenInclude> &token);
	
private:
	const std::string filename;
	typedef std::list<std::shared_ptr<const Token>> tokens_list;
	typedef tokens_list::iterator tokens_iterator;
	
	tokens_list tokens;
	tokens_list included_from;
	
	virtual void forEachLine(std::function<void (const std::shared_ptr<const Line> &)> lineparser) const;
	void dropEscapedNewline();
	void tokenizeIncludes(std::function<void (const std::shared_ptr<TokenInclude> &)> include);
	
	void replaceTokens(tokens_iterator begin, tokens_iterator end, const std::shared_ptr<Token> &token);
};
