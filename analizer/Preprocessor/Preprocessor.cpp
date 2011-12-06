
#include <iostream>
#include <vector>
#include <memory>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include "Preprocessor.h"
#include "File.h"
#include "Line.h"

using namespace std;

class TokenInclude;

Preprocessor::Preprocessor(const string &filename)
	: files()
{
	// First file created, but not parse. Later.
	files.push_back(make_pair(filename, shared_ptr<File>(new File(filename))));
}

Preprocessor::~Preprocessor()
{
}

void Preprocessor::tokenize()
{
	auto fit = files.begin();
	while (fit != files.end()) {
		fit->second->tokenize([](const shared_ptr<TokenInclude> &, const string &, bool){});
		++fit;
	}
}

void Preprocessor::getTokens(function<void (const shared_ptr<const Token> &)> add_token) const
{
	BOOST_FOREACH(const auto &file, files) {
		file.second->getTokens(add_token);
	}
}
