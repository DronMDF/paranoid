
#include <fstream>
#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include "File.h"
#include "Line.h"
#include "Token.h"
#include "Tokenizer.h"

using namespace std;
using boost::find_if;

File::File(const string &filename)
	: filename(filename), tokens()
{
}

File::~File()
{
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

void File::tokenize()
{
	Tokenizer tokenizer([&](const shared_ptr<const Token> &t) { 
		tokens.push_back(t); 
	});
	forEachLine([&tokenizer](const shared_ptr<const Line> &line) { 
		tokenizer.parse(line); 
	});
	
	dropEscapedNewline();
	
}

void File::dropEscapedNewline()
{
	const auto predicate = [](shared_ptr<const Token> &t){ return t->getText() == "\\"; };
	auto begin = find_if(tokens, predicate);
	while (begin != tokens.end()) {
		auto end = begin;
		++end;
		
		if ((*end)->getText() == "\n") {
			++end;
			tokens.erase(begin, end);
			
		}
		
		begin = find_if(end, tokens.end(), predicate);
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
