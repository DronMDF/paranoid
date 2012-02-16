
#include <list>
#include <iostream>
#include <boost/foreach.hpp>
#include <Preprocessor/TokenInclude.h>
#include <Preprocessor/TokenSpace.h>
#include <Preprocessor/TokenNewline.h>
#include <Preprocessor/File.h>
#include <Preprocessor/Error.h>
#include <Preprocessor/ErrorFormatter.h>
#include "Analizer.h"

using namespace std;

Analizer::Analizer()
	: errors()
{
}

void Analizer::checkFile(const shared_ptr<File> &file)
{
	list<shared_ptr<const Token>> tokens;
	file->getTokens([&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t); });

	list<shared_ptr<const Token>> includes;
	list<shared_ptr<const Token>> others;
	BOOST_FOREACH(const auto &t, tokens) {
		if (dynamic_cast<const TokenInclude *>(t.get()) != 0) {
			includes.push_back(t);
			continue;
		}
		
		if (dynamic_cast<const TokenSpace *>(t.get()) != 0) {
			continue;
		}
		
		if (dynamic_cast<const TokenNewline *>(t.get()) != 0) {
			continue;
		}
		
		others.push_back(t);
	}

	if (others.empty()) {
		BOOST_FOREACH(const auto &i, includes) {
			errors.push_back(Error(i, "Unused include"));
		}
	}
}

list<Error> Analizer::getResult() const
{
	return errors;
}
