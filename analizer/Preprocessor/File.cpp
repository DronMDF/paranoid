
#include <fstream>
#include <boost/foreach.hpp>
#include "File.h"
#include "FileLine.h"
#include "Splitter.h"
#include "Token.h"
#include "Uncommenter.h"

using namespace std;

File::File(const Preprocessor *pp, const string &filename)
	: filename(filename), tokens()
{
}

File::~File()
{
}

void File::tokenize()
{
	Splitter splitter([&](const shared_ptr<const Token> &t) { 
		tokens.push_back(t); 
	});
	Uncommenter uncommenter([&splitter](const shared_ptr<const Line> &line) {
		splitter.parse(line);
	});
	forEachLine([&uncommenter](const shared_ptr<const Line> &line) { 
		uncommenter.parse(line); 
	});
}

string File::getLocation() const
{
	return filename;
}

void File::getTokens(function<void (const shared_ptr<const Token> &)> add_token) const
{
	BOOST_FOREACH(const auto &token, tokens) {
		add_token(token);
	}
}

void File::forEachLine(function<void (const shared_ptr<const Line> &)> lineparser) const
{
	ifstream file(filename);
	for (unsigned i = 1; !file.eof(); i++) {
		string line;
		getline(file, line);
		if (!line.empty()) {
			lineparser(shared_ptr<Line>(new FileLine(i, line, this)));
		}
	}
}
