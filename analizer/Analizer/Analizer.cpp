
#include <functional>
#include <iostream>
#include <list>
#include <boost/foreach.hpp>
#include <Preprocessor/ErrorFormatter.h>
#include <Preprocessor/Error.h>
#include <Preprocessor/File.h>
#include <Preprocessor/TokenInclude.h>
#include <Preprocessor/TokenNewline.h>
#include <Preprocessor/TokenPredicate.h>
#include <Preprocessor/TokenSpace.h>
#include "Analizer.h"
#include "AnalizeToken.h"
#include "ExpressionDefine.h"

using namespace std;
using namespace std::placeholders;

Analizer::Analizer()
	: errors()
{
}

void Analizer::checkFile(const shared_ptr<File> &file)
{
	// Transform tokens chain
	file->replaceToken({"#define", Some(Not(isEol))},
		[](const list<shared_ptr<const Token>> &t){ return make_shared<ExpressionDefine>(t); });
	
	AnalizeToken helper;
	// TODO: forEachToken
	file->getTokens(bind(&AnalizeToken::checkToken, &helper, _1));

	if (helper.isAllClassified()) {
		BOOST_FOREACH(const auto &i, helper.getIncludes()) {
			errors.push_back(Error(i, "Unused include"));
		}
	}
}

list<Error> Analizer::getResult() const
{
	return errors;
}
