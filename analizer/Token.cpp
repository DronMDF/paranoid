
#include <boost/assert.hpp>
#include "Token.h"
#include "Preprocessor/Line.h"

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

void Token::determoneLocation(Locator *locator) const
{
}
