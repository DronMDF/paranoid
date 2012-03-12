
#define _XOPEN_SOURCE 500
#include <limits.h>
#include <stdlib.h>
#include <string>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>

using namespace std;
using boost::erase_all;
using boost::filesystem::path;
using boost::find_first;
using boost::find_last;
using boost::replace_all;
using boost::iterator_range;

string dirname(const string &filename)
{
	path p(filename);
	if (!p.has_parent_path()) {
		return ".";
	}
	return p.parent_path().string();
}

string canonical(const string &path)
{
	string canonicalized = path;
	while (find_first(canonicalized, "/..")) {
		iterator_range<string::iterator> dots = find_first(canonicalized, "/..");
		iterator_range<string::iterator> todots(canonicalized.begin(), dots.begin());
		iterator_range<string::iterator> ps = find_last(todots, "/");
		canonicalized.erase(ps.begin(), dots.end());
	}
	erase_all(canonicalized, "/.");
	while (find_first(canonicalized, "//")) {
		replace_all(canonicalized, "//", "/");
	}
	return canonicalized;
}

string realpath(const string &filename)
{
	vector<char> resolved(PATH_MAX);
	const char *rstr = ::realpath(filename.c_str(), &resolved[0]);
	if (rstr == 0) {
		// fallback to canonical
		return canonical(filename);
	}
	return rstr;
}
