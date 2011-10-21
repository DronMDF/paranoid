
#include <iostream>
#include <vector>
#include <memory>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include "Preprocessor.h"
#include "PPSplitter.h"
#include "PPUncommenter.h"
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
	PPUncommenter uncommenter(&splitter);
	
	BOOST_FOREACH(const auto &line, file) {
		if (!tokens.empty() && tokens.back().getText() != " ") {
			addToken(Token());
		}
		
		try {
			uncommenter.parse(line);
		} catch (const std::exception &e) {
			cout << format("in file %1%:%2%") % "unknown" % "unknown" << endl;
			throw;
		}
	}
	
	if (!tokens.empty() && tokens.back().getText() == " ") {
		tokens.pop_back();
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
