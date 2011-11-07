
#include <iostream>
#include <boost/foreach.hpp>
#include "File.h"
#include "FileLine.h"
#include "Splitter.h"
#include "Uncommenter.h"

using namespace std;

File::File(const Preprocessor *pp, const string &filename)
	: filename(filename), tokens()
{
}


File::File(istream &in)
	: filename("<unknown>"), tokens(), lines()
{
	for (unsigned i = 1; !in.eof(); i++) {
		string line;
		getline(in, line);
		if (!line.empty()) {
			lines.push_back(shared_ptr<Line>(new FileLine(i, line, this)));
		}
	}
}

File::~File()
{
}

void File::tokenize()
{
	PPSplitter splitter([&](Token token) -> void { 
		shared_ptr<const Token> t(new Token(token));
		tokens.push_back(t); 
	});
	PPUncommenter uncommenter(&splitter);
	forEachLine([&uncommenter](const shared_ptr<const Line> &line) -> void { 
		uncommenter.parse(line); 
	});
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
	BOOST_FOREACH(const auto &token, tokens) {
		add_token(token);
	}
}

void File::forEachLine(function<void (const shared_ptr<const Line> &)> lineparser) const
{
	BOOST_ASSERT(false);
}
