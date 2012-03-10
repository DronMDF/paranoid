
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/range/algorithm/find.hpp>
#include "IncludePath.h"

using namespace std;
using boost::find;
using boost::starts_with;
using boost::trim_copy;

IncludePath::IncludePath(const std::list<std::string> &command_line)
	: args()
{
	if (command_line.empty()) {
		args.push_back("cpp");
		return;
	}
	
	auto cursor = command_line.begin();
	args.push_back(cursor->empty() ? "cpp" : *cursor);
	++cursor;
	while (cursor != command_line.end()) {
		const list<string> without_arg = { "-nostdinc" };
		const list<string> with_arg = { "-isystem", "-iquote", "-I" };
		if (find(without_arg, *cursor) != without_arg.end()) {
			args.push_back(*cursor);
		} else if (find(with_arg, *cursor) != with_arg.end()) {
			args.push_back(*cursor);
			++cursor;
			args.push_back(*cursor);
		} else if (starts_with(*cursor, "-I")) {
			args.push_back(*cursor);
		}
		++cursor;
	}
}

IncludePath::~IncludePath() = default;

list<string> IncludePath::readSpec(const list<string> &args) const 
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

list<string> IncludePath::getPath(const string &pattern) const
{
	auto spec = readSpec(args);
	
	auto sit = boost::range::find(spec, pattern);
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

list<string> IncludePath::getQuotedPath() const 
{
	return getPath("#include \"...\" search starts here:");
}

list<string> IncludePath::getSystemPath() const 
{
	return getPath("#include <...> search starts here:");
}
