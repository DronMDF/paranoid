
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include "IncludeLocator.h"

using namespace std;
using boost::filesystem::exists;
using boost::filesystem::path;

IncludeLocator::IncludeLocator(const vector<const char *> &args)
	: system_paths(args.begin(), args.end()), local_paths()
{
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
