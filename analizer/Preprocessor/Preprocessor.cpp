
#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <Filesystem.h>
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
	const auto cfp = canonical(filename);
	files.push_back(make_pair(cfp, make_shared<File>(cfp)));
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
	
	const auto cfp = canonical(ffp);
	BOOST_FOREACH(auto &fit, files) {
		if (fit.first == cfp) {
			fit.second->includedFrom(token);
			return;
		}
	}
	
	files.push_back(make_pair(cfp, make_shared<File>(cfp)));
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

void Preprocessor::forEachFile(function<void (const shared_ptr<File> &)> analyzer)
{
	BOOST_FOREACH(const auto &file, files) {
		analyzer(file.second);
	}
}
