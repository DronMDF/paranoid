
#include <fstream>
#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "File.h"
#include "Line.h"
#include "Token.h"
#include "TokenList.h"
#include "TokenInclude.h"
#include "Tokenizer.h"

using namespace std;
using boost::find_if;
using boost::is_any_of;

File::File(const string &filename)
	: filename(filename), tokens(), included_from()
{
}

File::~File()
{
}

string File::getLocation() const
{
	// TODO: How to show multiple points of inclusion?
	string location;
	if (!included_from.empty()) {
		location += included_from.front()->getLocation() + '\n';
	}
	return location + filename;
}

void File::getTokens(function<void (const shared_ptr<const Token> &)> add_token) const
{
	BOOST_FOREACH(const auto &token, tokens) {
		add_token(token);
	}
}

void File::tokenize(function<void (const shared_ptr<TokenInclude> &, const string &, bool)> include)
{
	Tokenizer tokenizer([&](const shared_ptr<const Token> &t) { 
		tokens.push_back(t); 
	});
	forEachLine([&tokenizer](const shared_ptr<const Line> &line) { 
		tokenizer.parse(line); 
	});
	
	dropEscapedNewline();
	tokenizeIncludes(include);
}

void File::includedFrom(const shared_ptr<const Token> &token)
{
	included_from.push_back(token);
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

void File::tokenizeIncludes(function<void (const shared_ptr<TokenInclude> &, const string &, bool)> include)
{
	const auto is_sharp = [](shared_ptr<const Token> &t){ return t->getText() == "#"; };
	const auto is_rb = [](shared_ptr<const Token> &t){ return is_any_of(">\n")(t->getText()[0]); };
	auto begin = find_if(tokens, is_sharp);
	while (begin != tokens.end()) {
		auto end = begin;
		++end;
		
		while ((*end)->getText() == " ") {
			++end;
		}
		
		if ((*end)->getText() != "include") {
			begin = find_if(end, tokens.end(), is_sharp);
			continue;
		}

		++end;
		while ((*end)->getText() == " ") {
			++end;
		}
		
		if ((*end)->getText() != "<") {
			if ((*end)->getText()[0] != '"' || (*end)->getText().size() < 2) {
				begin = find_if(end, tokens.end(), is_sharp);
				continue;
			}

			// local include
			auto filename = string((*end)->getText(), 1, (*end)->getText().size() - 2);
			++end;
			auto itoken = shared_ptr<TokenInclude>(new TokenInclude(list<shared_ptr<const Token>>(begin, end)));
			replaceTokens(begin, end, itoken);
			
			include(itoken, filename, false);
			
			begin = find_if(end, tokens.end(), is_sharp);
			continue;
		}
		
		// System include
		++end;
		auto end2 = find_if(end, tokens.end(), is_rb);
		if ((*end2)->getText() == "\n") {
			begin = find_if(end, tokens.end(), is_sharp);
			continue;
		}
		
		auto fntoken = shared_ptr<Token>(new TokenList(list<shared_ptr<const Token>>(end, end2)));
		replaceTokens(end, end2, fntoken);
		
		++end2;
		auto itoken = shared_ptr<TokenInclude>(new TokenInclude(list<shared_ptr<const Token>>(begin, end2)));
		replaceTokens(begin, end2, itoken);

		include(itoken, fntoken->getText(), true);
		
		begin = find_if(end2, tokens.end(), is_sharp);
	}
}

void File::replaceTokens(tokens_iterator begin, tokens_iterator end, const shared_ptr<Token> &token)
{
	tokens.erase(begin, end);
	tokens.insert(end, token);
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
