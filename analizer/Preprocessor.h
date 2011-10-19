
#pragma once

#include <list>
#include "Token.h"

class File;
class Line;

class Preprocessor {
public:
	typedef std::list<Token>::const_iterator const_iterator;

	explicit Preprocessor(const File &file);
	virtual ~Preprocessor();

	const_iterator begin() const;
	const_iterator end() const;
	
protected:
	Preprocessor();
	
	void addToken(Token token);
	
private:
	std::list<Token> tokens;
	
	virtual void parseLine(const Line &line);
};
