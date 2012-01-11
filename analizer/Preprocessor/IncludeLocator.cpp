
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include "Error.h"
#include "IncludeLocator.h"
#include "TokenInclude.h"

using namespace std;
using boost::filesystem::exists;
using boost::filesystem::path;
using boost::starts_with;

IncludeLocator::IncludeLocator(const vector<const char *> &args, const list<string> spec_path)
	: system_paths(), local_paths()
{
	vector<const char *>::const_iterator it = args.begin();
	while (it != args.end()) {
		if (starts_with(*it, "-I")) {
			if (string(*it).size() == 2) {
				++it;
				if (it == args.end()) {
					break;
				}
				local_paths.push_back(*it);
			} else {
				local_paths.push_back(*it + 2);
			}
		} else if (string(*it) == "-isystem") {
			++it;
			if (it == args.end()) {
				break;
			}
			system_paths.push_back(*it);
		}
		
		++it;
	}
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
		auto cp = path(token->getFileName()).parent_path().string() + '/' + token->getHeaderName();
		if (isExists(cp)) {
			return cp;
		}
	}
	
	BOOST_FOREACH(const auto &p, token->isSystem() ? system_paths : local_paths) {
		auto cp = p + '/' + token->getHeaderName();
		if (isExists(cp)) {
			return cp;
		}
	}
	
	// Unknown include is normal way for paranoid, not error
	return "";
}
