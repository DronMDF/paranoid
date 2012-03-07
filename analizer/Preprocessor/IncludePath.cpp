
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/range/algorithm/find.hpp>
#include "IncludePath.h"

using namespace std;
using boost::trim_copy;
using boost::starts_with;

IncludePath::~IncludePath() = default;

list<string> IncludePath::readSpec() const 
{
	FILE *in = popen("sh -c 'echo | LANG=C gcc -v -E -' 2>&1", "r");
	if (in == 0) {
		return {};
	}
	
	list<string> result;
	string last;
	while (true) {
		char c = fgetc(in);
		if (c == EOF) {
			break;
		}
			
		if (c == '\n') {
			result.push_back(last);
			last.erase();
		} else {
			last.push_back(c);
		}
	}
	
	pclose(in);
	return result;
}

list<string> IncludePath::getQuotedPath() const 
{
	return {};
}

list<string> IncludePath::getSystemPath() const 
{
	auto spec = readSpec();
	
	auto sit = boost::range::find(spec, "#include <...> search starts here:");
	if (sit == spec.end()) {
		return {};
	}
	++sit;
	
	list<string> paths;
	while (sit != spec.end() && starts_with(*sit, " ")) {
		paths.push_back(trim_copy(*sit));
		++sit;
	}
	
	return paths;
}
