
#include "Token.h"
#include "Line.h"

using namespace std;

Token::Token()
	: line(0), offset(0), lenght(0)
{
}

Token::Token(const Line *line, unsigned offset, unsigned len)
	: line(line), offset(offset), lenght(len)
{
}

string Token::getText() const
{
	if (line == 0) {
		return " ";
	}
	
	return string(line->getText(), offset, lenght);
}
