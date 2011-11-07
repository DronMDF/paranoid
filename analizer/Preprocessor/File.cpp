
#include <iostream>
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
