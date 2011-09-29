
#include "Line.h"

using namespace std;

Line::Line(unsigned number, const string &text)
	: number(number), text(text)
{
}

unsigned Line::getNumber() const
{
	return number;
}

string Line::getText() const
{
	return text;
}
