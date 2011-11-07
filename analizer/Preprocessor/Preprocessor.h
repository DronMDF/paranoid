
#pragma once

#include <list>
#include "Token.h"

class File;
class Line;

// Preprocessor is main class for parse raw source
class Preprocessor {
public:
	typedef std::list<Token>::const_iterator const_iterator __attribute__((deprecated));

	// TODO: construct with include/sysinclude paths and one source file name
	explicit Preprocessor(const File &file) __attribute__((deprecated));
	virtual ~Preprocessor();

	const_iterator begin() const __attribute__((deprecated));
	const_iterator end() const __attribute__((deprecated));
	
protected:
	Preprocessor() __attribute__((deprecated));
	
	void addToken(Token token) __attribute__((deprecated));
	
private:
	// TODO: Keep map of files by full name
	// TODO: Pass this in every file
	
	std::list<Token> tokens __attribute__((deprecated));
};
