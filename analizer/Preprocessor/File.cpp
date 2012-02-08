
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
#include "TokenPredicate.h"

using namespace std;
using namespace std::placeholders;
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

string File::getFileName() const
{
	return filename;
}

void File::getTokens(function<void (const shared_ptr<const Token> &)> add_token) const
{
	BOOST_FOREACH(const auto &token, tokens) {
		add_token(token);
	}
}

void File::tokenize(function<void (const shared_ptr<TokenInclude> &)> include)
{
	auto add_token = [&](const shared_ptr<const Token> &t) { tokens.push_back(t); };
	Tokenizer tokenizer(add_token);

	forEachLine([&tokenizer](const shared_ptr<const Line> &line) { tokenizer.parse(line); });
	
	replaceToken({"\\", isEol}, 
		[](const list<shared_ptr<const Token>> &){ return shared_ptr<Token>(); });

	tokenizeIncludes(include);
}

void File::includedFrom(const shared_ptr<const TokenInclude> &token)
{
	included_from.push_back(token);
}

void File::tokenizeIncludes(function<void (const shared_ptr<TokenInclude> &)> include)
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

			++end;
			auto itoken = shared_ptr<TokenInclude>(new TokenInclude(list<shared_ptr<const Token>>(begin, end)));
			replaceTokens(begin, end, itoken);
			include(itoken);
			
			begin = find_if(end, tokens.end(), is_sharp);
			continue;
		}
		
		// System include
		auto end2 = find_if(end, tokens.end(), is_rb);
		if ((*end2)->getText() == "\n") {
			begin = find_if(end, tokens.end(), is_sharp);
			continue;
		}
		++end2;
		
		auto fntoken = shared_ptr<Token>(new TokenList(list<shared_ptr<const Token>>(end, end2)));
		replaceTokens(end, end2, fntoken);
		
		auto itoken = shared_ptr<TokenInclude>(new TokenInclude(list<shared_ptr<const Token>>(begin, end2)));
		replaceTokens(begin, end2, itoken);
		include(itoken);
		
		begin = find_if(end2, tokens.end(), is_sharp);
	}
}

void File::replaceTokens(tokens_iterator begin, tokens_iterator end, const shared_ptr<const Token> &token)
{
	tokens.erase(begin, end);
	if (token) {
		tokens.insert(end, token);
	}
}

void File::forEachLine(function<void (const shared_ptr<const Line> &)> lineparser) const
{
	ifstream file(filename);
	if (file.good()) {
		for (unsigned i = 1; !file.eof(); i++) {
			string line;
			getline(file, line);
			if (!line.empty()) {
				lineparser(shared_ptr<Line>(new Line(i, line, this)));
			}
		}
	}
}

void File::replaceToken(TokenExpression expression, 
			 function<shared_ptr<const Token> (const list<shared_ptr<const Token>> &)> creator)
{
	auto lookup = tokens.begin();
	while (lookup != tokens.end()) {
		expression.reset();
		
		auto begin = find_if(lookup, tokens.end(), bind(&TokenExpression::match, &expression, _1));
		if (begin == tokens.end()) {
			return;
		}
		
		auto end = begin;
		++end;
		while (end != tokens.end()) {
			if (expression.match(*end)) {
				++end;
				continue;
			}
			
			if (expression.isMatched()) {
				const list<shared_ptr<const Token>> replaced(begin, end);
				replaceTokens(begin, end, creator(replaced));
				lookup = end;
			} else {
				lookup = ++begin;
			}
			break;
		}
	}
}

