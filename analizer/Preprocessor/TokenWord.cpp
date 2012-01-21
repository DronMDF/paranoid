
#include <iostream>
#include <boost/assert.hpp>
#include "TokenWord.h"
#include "Line.h"

using namespace std;

TokenWord::TokenWord(const shared_ptr<const Line> &line, std::string::size_type begin, std::string::size_type end)
	: line(line), begin(begin), end(end)
{
	BOOST_ASSERT(line);
	if (this->end == string::npos) {
		this->end = line->getText().size();
	}
	BOOST_ASSERT(begin < this->end);
	BOOST_ASSERT(this->end <= line->getText().size());
}

string TokenWord::getText() const
{
	return string(line->getText(), begin, end - begin);
}

string TokenWord::getLocation() const
{
	return line->getLocation();
}

string TokenWord::getFileName() const
{
	return line->getFileName();
}

shared_ptr<const Line> TokenWord::getLine() const
{
	return line;
}

size_t TokenWord::getBeginPos() const
{
	return begin;
}

size_t TokenWord::getEndPos() const
{
	return end;
}
