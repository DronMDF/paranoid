
#include <boost/foreach.hpp>
#include "ErrorList.h"
#include "Error.h"

using namespace std;

ErrorList::ErrorList()
	: errors()
{
}

void ErrorList::insert(const Error &e)
{
	errors.push_back(e);
}

void ErrorList::forEachError(function<void (const Error &e)> formatter) const
{
	BOOST_FOREACH(const auto &e, errors) {
		formatter(e);
	}
}

