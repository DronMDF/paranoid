
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

Preprocessor::Preprocessor(function<string(const string &, const string &, bool)> locate, 
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
	try {
		const auto ffp = locate("", token->getFileName(), token->isSystem());
		
		BOOST_FOREACH(auto &fit, files) {
			if (fit.first == ffp) {
				fit.second->includedFrom(token);
				return;
			}
		}
		
		files.push_back(make_pair(ffp, shared_ptr<File>(new File(ffp))));
	} catch (const std::exception &e) {
		throw Error(*token, e.what());
	}
}

void Preprocessor::getTokens(function<void (const shared_ptr<const Token> &)> add_token) const
{
	BOOST_FOREACH(const auto &file, files) {
		file.second->getTokens(add_token);
	}
}
