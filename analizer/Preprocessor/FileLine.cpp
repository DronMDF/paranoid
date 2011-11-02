
#include <boost/lexical_cast.hpp>
#include "FileLine.h"
#include "File.h"

using namespace std;
using boost::lexical_cast;

FileLine::FileLine()
	: number(0), text(), file(0)
{
}

FileLine::FileLine(const FileLine &line)
	: number(line.number), text(line.text), file(line.file)
{
}

FileLine::FileLine(unsigned number, const string &text, const File *file)
	: number(number), text(text), file(file)
{
}

FileLine::~FileLine()
{
}

string FileLine::getText() const
{
	return text;
}

string FileLine::getLocation() const
{
	return (file != 0 ? file->getLocation() : "<unknown>") + 
		":" + lexical_cast<string>(number);
}
