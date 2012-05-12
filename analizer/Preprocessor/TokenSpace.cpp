
#include <boost/assert.hpp>
#include "Line.h"
#include "TokenSpace.h"

using namespace std;

TokenSpace::TokenSpace(const shared_ptr<const Line> &line, 
		       string::size_type begin, string::size_type end)
	: line(line), begin(begin), end(end)
{
	if (this->end == string::npos) {
		BOOST_ASSERT(line);
		this->end = line->getText().size();
	}
}

string TokenSpace::getText() const
{
	return " ";
}

string TokenSpace::getLocation() const
{
	return line->getLocation();
}

string TokenSpace::getFileName() const
{
	return line->getFileName();
}

shared_ptr<const Line> TokenSpace::getLine() const
{
	return line;
}

size_t TokenSpace::getBeginPos() const
{
	return begin;
}

size_t TokenSpace::getEndPos() const
{
	return end;
}
