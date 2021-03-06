
#include <fstream>
#include <boost/filesystem.hpp>
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

File::File(const string &filename)
	: TokenList({}), filename(filename), included_from()
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

void File::tokenize()
{
	auto add_token = [&](const shared_ptr<Token> &t) { tokens.push_back(t); };
	Tokenizer tokenizer(add_token);

	forEachLine([&tokenizer](const shared_ptr<const Line> &line) { tokenizer.parse(line); });
	
	typedef const list<shared_ptr<Token>> tokenlist;
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

void File::forEachToken(function<void (const shared_ptr<const Token> &)> func) const
{
	TokenList::forEachToken(func);
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

