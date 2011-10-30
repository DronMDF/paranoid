
#include <boost/assert.hpp>
#include "Token.h"
#include "Line.h"

using namespace std;

Token::Token()
	: line(), offset(0), length(0)
{
}

Token::Token(const shared_ptr<const Line> &line, unsigned offset, unsigned length)
	: line(line), offset(offset), length(length)
{
	BOOST_ASSERT(offset + length <= line->getText().size());
}

string Token::getText() const
{
	if (!line) {
		return " ";
	}
	
	return string(line->getText(), offset, length);
}

string Token::getLocation() const
{
	return line->getLocation();
}

string Token::getTextInString(const string &begin_marker, const string &end_marker) const
{
	string text = line->getText();
	text.insert(offset + length, end_marker);
	text.insert(offset, begin_marker);
	return text;
}
