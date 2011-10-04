
#include <iostream>
#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/foreach.hpp>
#include "Preprocessor.h"
#include "File.h"
#include "Line.h"

using namespace std;
using namespace boost;

Preprocessor::Preprocessor(const File &file)
	: tokens()
{
	BOOST_FOREACH(const Line &line, file) {
		string text = line.getText();
		vector<string> toks;
		split(toks, text, is_space(), token_compress_on);
		BOOST_FOREACH(const string &tok, toks) {
			if (tok.empty()) {
				continue;
			}
			
			if (tok == " " && !tokens.empty() && tokens.back().getText() == " ") {
				continue;
			}
			
			tokens.push_back(Token(tok));
			tokens.push_back(Token(" "));
		}
	}
	
	if (!tokens.empty() && tokens.back().getText() == " ") {
		tokens.pop_back();
	}
}

Preprocessor::const_iterator Preprocessor::begin() const
{
	return tokens.begin();
}

Preprocessor::const_iterator Preprocessor::end() const
{
	return tokens.end();
}
