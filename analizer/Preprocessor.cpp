
#include <iostream>
#include <vector>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include "Preprocessor.h"
#include "PPSplitter.h"
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
	PPSplitter splitter(bind(&Preprocessor::addToken, this, _1));
	
	BOOST_FOREACH(const Line &line, file) {
		if (!line.getText().empty()) {
			addToken(Token());
		}
		splitter.parse(&line);
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
