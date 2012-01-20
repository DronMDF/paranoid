
#include "Line.h"
#include "TokenNewline.h"

using namespace std;

TokenNewline::TokenNewline(const std::shared_ptr<const Line> &line)
	: line(line)
{
}
	
string TokenNewline::getText() const
{
	return "\n";
}

string TokenNewline::getLocation() const
{
	return line->getLocation();
}

string TokenNewline::getTextInString(const string &begin_marker __attribute__((unused)),
				     const string &end_marker __attribute__((unused))) const
{
	return line->getText();
}

string TokenNewline::getFileName() const
{
	return line->getFileName();
}

shared_ptr<const Line> TokenNewline::getLine() const
{
	return line;
}

size_t TokenNewline::getBeginPos() const
{
	return line->getText().size();
}

size_t TokenNewline::getEndPos() const
{
	return line->getText().size();
}
