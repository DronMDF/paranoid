
#include <iostream>
#include "File.h"
#include "FileLine.h"

using namespace std;

File::File(istream &in)
	: lines()
{
	for (unsigned i = 1; !in.eof(); i++) {
		string line;
		getline(in, line);
		if (!line.empty()) {
			lines.push_back(shared_ptr<Line>(new FileLine(i, line, this)));
		}
	}
}

string File::getLocation() const
{
	return "<unknown>";
}

File::const_iterator File::begin() const
{
	return lines.begin();
}

File::const_iterator File::end() const
{
	return lines.end();
}
