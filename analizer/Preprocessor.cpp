
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

Preprocessor::Preprocessor()
	: tokens()
{
}

Preprocessor::Preprocessor(const File &file)
	: tokens()
{
	BOOST_FOREACH(const Line &line, file) {
		parseLine(line);
	}
}

Preprocessor::~Preprocessor()
{
}

Preprocessor::const_iterator Preprocessor::begin() const
{
	return tokens.begin();
}

Preprocessor::const_iterator Preprocessor::end() const
{
	return tokens.end();
}

void Preprocessor::addToken(Token token)
{
	if (token.getText() == " ") {
		if (tokens.empty() || tokens.back().getText() == " ") {
			return;
		}
	}
	
	tokens.push_back(token);
}

void Preprocessor::parseLine(const Line &line)
{
	string text = line.getText();
	
	// Вырезаем однострочный комментарий
	const size_t comment = text.find("//");
	if (comment != string::npos) {
		text.erase(comment);
	}
	
	if (!text.empty() && !tokens.empty() && tokens.back().getText() != " ") {
		tokens.push_back(Token());
	}
	
	for (size_t eword = 0;;) {
		size_t sword = text.find_first_not_of(" \t", eword);
		if (sword == string::npos) {
			break;
		}
		
		if (sword > eword && !tokens.empty() && tokens.back().getText() != " ") {
			tokens.push_back(Token());
		}
		
		eword = text.find_first_of(" \t", sword);
		if (eword == string::npos) {
			if (text.size() > sword) {
				tokens.push_back(Token(&line, sword, text.size() - sword));
			}
			break;
		}
			
		tokens.push_back(Token(&line, sword, eword - sword));
	}
}
