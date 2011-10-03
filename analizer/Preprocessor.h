
#pragma once

#include <list>
#include "Token.h"

class File;

class Preprocessor {
public:
	typedef std::list<Token>::const_iterator const_iterator;

	explicit Preprocessor(const File &file);

	const_iterator begin() const;
	const_iterator end() const;
	
private:
	std::list<Token> tokens;
};
