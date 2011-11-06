
#include <iostream>
#include "File.h"
#include "FileLine.h"

using namespace std;

File::File(const Preprocessor *pp, const string &filename)
	: filename(filename)
{
}


File::File(istream &in)
	: filename("<unknown>"), lines()
{
	for (unsigned i = 1; !in.eof(); i++) {
		string line;
		getline(in, line);
		if (!line.empty()) {
			lines.push_back(shared_ptr<Line>(new FileLine(i, line, this)));
		}
	}
}

void File::tokenize()
{
}

string File::getLocation() const
{
	return filename;
}

File::const_iterator File::begin() const
{
	return lines.begin();
}

File::const_iterator File::end() const
{
	return lines.end();
}

void File::getTokens(function<void (const shared_ptr<const Token> &)> add_token) const
{
	const shared_ptr<const Line> line(new FileLine(10, "012345", this));
	const shared_ptr<const Token> token(new Token(line, 0, 6));
	add_token(token);
}
