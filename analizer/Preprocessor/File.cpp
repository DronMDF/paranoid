
#include <fstream>
#include <algorithm>
#include <boost/algorithm/string/classification.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include "File.h"
#include "Line.h"
#include "TokenDirective.h"
#include "Token.h"
#include "TokenInclude.h"
#include "Tokenizer.h"
#include "TokenList.h"
#include "TokenPredicate.h"

using namespace std;
using namespace std::placeholders;
using boost::filesystem::is_regular_file;
using boost::find_if;
using boost::for_each;
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

void File::forEachToken(function<void (const shared_ptr<const Token> &)> func) const
{
	for_each(tokens, func);
}

void File::tokenize()
{
	auto add_token = [&](const shared_ptr<const Token> &t) { tokens.push_back(t); };
	Tokenizer tokenizer(add_token);

	forEachLine([&tokenizer](const shared_ptr<const Line> &line) { tokenizer.parse(line); });
	
	
	typedef const list<shared_ptr<const Token>> tokenlist;
	replaceToken({"\\", isEol}, // Cut escaped endline
		[](tokenlist &){ return shared_ptr<Token>(); });
	replaceToken({"#", Optional(Some(isSpace)), isWord}, // Preprocessor directive
		[](tokenlist &tokens){ return make_shared<TokenDirective>(tokens); });
	replaceToken({"#pragma", Some(Not(isEol))}, // Cut any pragma
		[](tokenlist &){ return shared_ptr<Token>(); });
}

void File::includedFrom(const shared_ptr<const TokenInclude> &token)
{
	included_from.push_back(token);
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
		BOOST_ASSERT(is_regular_file(filename));
		for (unsigned i = 1; !file.eof(); i++) {
			string line;
			getline(file, line);
			if (!line.empty()) {
				lineparser(make_shared<Line>(i, line, this));
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
		
		if (expression.isMatched()) {
			const list<shared_ptr<const Token>> replaced(begin, end);
			replaceTokens(begin, end, creator(replaced));
			lookup = end;
			continue;
		}
		
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

