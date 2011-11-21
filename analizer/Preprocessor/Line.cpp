
#include <boost/lexical_cast.hpp>
#include "Line.h"
#include "File.h"

using namespace std;
using boost::lexical_cast;

Line::Line(unsigned number, const string &text, const Location *file)
	: number(number), text(text), file(file)
{
}

Line::~Line()
{
}

string Line::getText() const
{
	return text;
}

string Line::getLocation() const
{
	return (file != 0 ? file->getLocation() : "<unknown>") + 
		":" + lexical_cast<string>(number);
}
