
#include <functional>
#include <iostream>
#include <list>
#include <boost/assert.hpp>
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
	: errors(), declarations()
{
}

// Transform token chains in expression
void Analizer::transformFile(const shared_ptr<File> &file) const
{
	file->replaceToken({"#define", Some(Not(isEol))},
		[](const list<shared_ptr<const Token>> &t){ return make_shared<ExpressionDefine>(t); });
}

void Analizer::addName(const shared_ptr<const File> &file, const shared_ptr<const Token> &token)
{
	if (auto expression = dynamic_cast<const ExpressionDefine *>(token.get())) {
		auto names = expression->getDeclaredNames();
		declarations[file].insert(names.begin(), names.end());
	}
}

void Analizer::collectNames(const shared_ptr<const File> &file)
{
	BOOST_ASSERT(declarations.count(file) == 0);
	declarations[file] = {};
	
	// TODO: collect declared names
	file->forEachToken(bind(&Analizer::addName, this, file, _1));
}

void Analizer::checkFile(const shared_ptr<const File> &file)
{
	// TODO: construct include graph
	
	AnalizeToken helper;
	// TODO: Imported names check by namelist, if all names is present - detect unused include
	// 	If any name is absent - unused include cannot be detected
	file->forEachToken(bind(&AnalizeToken::checkToken, &helper, _1));

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
