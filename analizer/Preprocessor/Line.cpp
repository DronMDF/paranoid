
#include <boost/lexical_cast.hpp>
#include "Line.h"
#include "File.h"

using namespace std;
using boost::lexical_cast;

Line::Line(unsigned number, const string &text, const File *file)
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
	return (file != 0 ? file->getLocation() : "unknown") + 
		":" + lexical_cast<string>(number);
}

string Line::getFileName() const
{
	return file != 0 ? file->getFileName() : "unknown";
}
