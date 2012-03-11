
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <Filesystem.h>
#include "Error.h"
#include "IncludeLocator.h"
#include "TokenInclude.h"

using namespace std;
using boost::filesystem::exists;
using boost::starts_with;

IncludeLocator::IncludeLocator(const list<string> system, const list<string> quoted)
	: system_paths(system), quoted_paths(quoted)
{
}

IncludeLocator::~IncludeLocator()
{
}

bool IncludeLocator::isExists(const string &include) const
{
	return exists(include);
}

string IncludeLocator::locate(const shared_ptr<const TokenInclude> &token) const
{
	if (!token->isSystem()) {
		auto cp = dirname(token->getFileName()) + '/' + token->getHeaderName();
		if (isExists(cp)) {
			return cp;
		}
	}
	
	BOOST_FOREACH(const auto &p, token->isSystem() ? system_paths : quoted_paths) {
		auto cp = p + '/' + token->getHeaderName();
		if (isExists(cp)) {
			return cp;
		}
	}
	
	// Unknown include is normal way for paranoid, not error
	return "";
}
