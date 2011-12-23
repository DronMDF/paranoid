
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include "IncludeLocator.h"

using namespace std;
using boost::filesystem::exists;
using boost::filesystem::path;
using boost::starts_with;

IncludeLocator::IncludeLocator(const vector<const char *> &args)
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

string IncludeLocator::locate(const string &file, const string &include, bool system) const
{
	if (!system) {
		auto cp = path(file).parent_path().string() + '/' + include;
		if (isExists(cp)) {
			return cp;
		}
	}
	
	BOOST_FOREACH(const auto &p, system ? system_paths : local_paths) {
		auto cp = p + '/' + include;
		if (isExists(cp)) {
			return cp;
		}
	}
	
	throw runtime_error("File not found");
}
