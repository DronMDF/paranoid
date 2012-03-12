
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
	const auto realname = realpath(filename);
	const auto canonicalname = canonical(filename);
	files.push_back(make_pair(realname, make_shared<File>(canonicalname)));
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
	const auto located_name = locate(token);
	
	if (!located_name.empty()) {
		const auto canonical_name = canonical(located_name);
		const auto real_name = realpath(located_name);
		BOOST_FOREACH(auto &fit, files) {
			if (fit.first == real_name) {
				fit.second->includedFrom(token);
				token->include(fit.second);
				return token;
			}
		}
		
		auto file = make_shared<File>(canonical_name);
		file->includedFrom(token);
		token->include(file);
		files.push_back(make_pair(real_name, file));
	}
	
	return token;
}

void Preprocessor::forEachFile(function<void (const shared_ptr<File> &)> analyzer)
{
	BOOST_FOREACH(const auto &file, files) {
		analyzer(file.second);
	}
}
