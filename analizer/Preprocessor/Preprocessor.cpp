
#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include "Preprocessor.h"
#include "File.h"
#include "Line.h"
#include "TokenInclude.h"
#include "Error.h"

using namespace std;
using namespace std::placeholders;
using boost::filesystem::exists;

Preprocessor::Preprocessor(function<string(const std::shared_ptr<const TokenInclude> &)> locate, 
			   const string &filename)
	: locate(locate), files()
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
		fit->second->tokenize(bind(&Preprocessor::include, this, _1));
		++fit;
	}
}

void Preprocessor::include(const shared_ptr<TokenInclude> &token)
{
	const auto ffp = locate(token);
	
	if (ffp.empty()) {
		return;
	}
	
	BOOST_FOREACH(auto &fit, files) {
		if (fit.first == ffp) {
			fit.second->includedFrom(token);
			return;
		}
	}
	
	files.push_back(make_pair(ffp, shared_ptr<File>(new File(ffp))));
}

void Preprocessor::getTokens(const string &filename, 
	function<void (const shared_ptr<const Token> &)> add_token) const
{
	BOOST_FOREACH(const auto &file, files) {
		if (file.first == filename) {
			file.second->getTokens(add_token);
		}
	}
}
