
#include <boost/assert.hpp>
#include "Token.h"
#include "Line.h"

using namespace std;

Token::Token()
	: line(0), offset(0), length(0)
{
}

Token::Token(const Line *line, unsigned offset, unsigned length)
	: line(line), offset(offset), length(length)
{
	BOOST_ASSERT(offset + length <= line->getText().size());
}

string Token::getText() const
{
	if (line == 0) {
		return " ";
	}
	
	return string(line->getText(), offset, length);
}
