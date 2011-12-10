
#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include "Preprocessor.h"
#include "File.h"
#include "Line.h"

using namespace std;
using namespace std::placeholders;

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
		fit->second->tokenize(bind(&Preprocessor::include, this, _1, _2, _3));
		++fit;
	}
}

void Preprocessor::include(const shared_ptr<TokenInclude> &token, const string &file, bool system)
{
	BOOST_FOREACH(auto &fit, files) {
		if (fit.first == file) {
			fit.second->includedFrom(token);
			return;
		}
	}
	
	files.push_back(make_pair(file, shared_ptr<File>(new File(file))));
}

void Preprocessor::getTokens(function<void (const shared_ptr<const Token> &)> add_token) const
{
	BOOST_FOREACH(const auto &file, files) {
		file.second->getTokens(add_token);
	}
}
