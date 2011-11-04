
#pragma once

#include <list>
#include "Token.h"

class File;
class Line;

// Preprocessor is main class for parse raw source
class Preprocessor {
public:
	typedef std::list<Token>::const_iterator const_iterator;

	// TODO: construct with include/sysinclude paths and one source file name
	explicit Preprocessor(const File &file);
	virtual ~Preprocessor();

	const_iterator begin() const;
	const_iterator end() const;
	
protected:
	Preprocessor();
	
	void addToken(Token token);
	
private:
	// TODO: Keep map of files by full name
	// TODO: Pass this in every file
	
	std::list<Token> tokens;
};
