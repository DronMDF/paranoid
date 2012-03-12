
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
#include "TokenPredicate.h"
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
		fit->second->tokenize();
		
		auto createIncludeToken = bind(&Preprocessor::createIncludeToken, this, _1);
		fit->second->replaceToken(
			{"#include", Optional(Some(isSpace)), "<", Some(Not(">")), ">"}, 
			createIncludeToken);
		fit->second->replaceToken(
			{"#include", Optional(Some(isSpace)), isWord}, // TODO: isString
			createIncludeToken);
		
		++fit;
	}
}

shared_ptr<Token> Preprocessor::createIncludeToken(const list<shared_ptr<const Token>> &tokens)
{
	auto token = make_shared<TokenInclude>(tokens);
	const auto ffp = locate(token);
	
	if (!ffp.empty()) {
		const auto cfp = canonical(ffp);
		BOOST_FOREACH(auto &fit, files) {
			if (fit.first == cfp) {
				fit.second->includedFrom(token);
				token->include(fit.second);
				return token;
			}
		}
		
		auto file = make_shared<File>(cfp);
		file->includedFrom(token);
		token->include(file);
		files.push_back(make_pair(cfp, file));
	}
	
	return token;
}

void Preprocessor::forEachFile(function<void (const shared_ptr<File> &)> analyzer)
{
	BOOST_FOREACH(const auto &file, files) {
		analyzer(file.second);
	}
}
