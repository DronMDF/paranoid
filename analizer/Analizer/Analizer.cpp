
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
#include "AnalizeInclude.h"
#include "ExpressionDefine.h"
#include "ExpressionIfDirective.h"
#include "ExpressionIfBlock.h"

using namespace std;
using namespace std::placeholders;

Analizer::Analizer()
	: errors()
{
}

void Analizer::checkUsedIncludeInFile(const shared_ptr<const File> &file)
{
	AnalizeInclude helper;

	file->forEachToken(bind(&AnalizeInclude::checkToken, &helper, _1, file));

	BOOST_FOREACH(const auto &i, helper.getUnused()) {
		errors.push_back(Error(i, "Unused include"));
	}
}

list<Error> Analizer::getResult() const
{
	return errors;
}

