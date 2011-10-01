
#include "Line.h"

using namespace std;

Line::Line(const Line &line)
	: number(line.number), text(line.text), file(line.file)
{
}

Line::Line(unsigned number, const string &text, const File *file)
	: number(number), text(text), file(file)
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

const File *Line::getFile() const
{
	return file;
}
