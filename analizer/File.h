
#pragma once

#include <iosfwd>
#include <list>
#include "FileLine.h"

class File {
public:
	typedef std::list<FileLine>::const_iterator const_iterator;

	explicit File(std::istream &in);

	const_iterator begin() const;
	const_iterator end() const;
	
private:
	std::list<FileLine> lines;
};
