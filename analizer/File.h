
#pragma once

#include <iosfwd>
#include <list>
#include "Line.h"

class File {
public:
	typedef std::list<Line>::const_iterator const_iterator;

	explicit File(std::istream &in);

	const_iterator begin() const;
	const_iterator end() const;
	
private:
	std::list<Line> lines;
};
