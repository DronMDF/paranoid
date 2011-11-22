
#include <fstream>
#include <boost/foreach.hpp>
#include "File.h"
#include "Line.h"
#include "Token.h"
#include "Tokenizer.h"

using namespace std;

File::File(const string &filename)
	: filename(filename), tokens()
{
}

File::~File()
{
}

void File::tokenize()
{
	Tokenizer tokenizer([&](const shared_ptr<const Token> &t) { 
		tokens.push_back(t); 
	});
	forEachLine([&tokenizer](const shared_ptr<const Line> &line) { 
		tokenizer.parse(line); 
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
			lineparser(shared_ptr<Line>(new Line(i, line, this)));
		}
	}
}
