
#include <iostream>
#include "File.h"

using namespace std;

File::File(istream &in)
	: lines()
{
	for (unsigned i = 1; !in.eof(); i++) {
		string line;
		getline(in, line);
		lines.push_back(Line(i, line, this));
	}
}

File::const_iterator File::begin() const
{
	return lines.begin();
}

File::const_iterator File::end() const
{
	return lines.end();
}
