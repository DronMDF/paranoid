
#include "Analizer.h"

#include <functional>
#include <boost/foreach.hpp>
#include <Preprocessor/Error.h>
#include <Preprocessor/ErrorList.h>
#include <Preprocessor/File.h>
#include "AnalizeInclude.h"

using namespace std;
using namespace std::placeholders;

Analizer::Analizer(ErrorList *el)
	: el(el)
{
}

void Analizer::operator()(const std::shared_ptr<const File> &file) const
{
	AnalizeInclude helper;

	file->forEachToken(bind(&AnalizeInclude::checkToken, &helper, _1, file));

	BOOST_FOREACH(const auto &i, helper.getUnused()) {
		el->insert(Error(i, "Unused include"));
	}
}

