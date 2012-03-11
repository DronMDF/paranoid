
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/range/algorithm/find.hpp>
#include "IncludePath.h"

using namespace std;
using boost::ends_with;
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
	
	string language;
	
	auto cursor = command_line.begin();
	args.push_back(cursor->empty() ? "cpp" : *cursor);
	++cursor;
	while (cursor != command_line.end()) {
		const list<string> need_without_arg = { "-nostdinc" };
		const list<string> need_with_arg = { "-isystem", "-iquote", "-I" };
		if (find(need_without_arg, *cursor) != need_without_arg.end()) {
			args.push_back(*cursor);
		} else if (find(need_with_arg, *cursor) != need_with_arg.end()) {
			args.push_back(*cursor);
			++cursor;
			args.push_back(*cursor);
		} else if (starts_with(*cursor, "-I")) {
			args.push_back(*cursor);
		} else if (starts_with(*cursor, "-")) {
			// Other options skipping
			const list<string> with_arg = { "-o" };
			if (find(with_arg, *cursor) != with_arg.end()) {
				++cursor;
			}
		} else {
			// Filename
			if (ends_with(*cursor, ".c")) {
				language = "c";
			}
			
			if (ends_with(*cursor, ".c++") || ends_with(*cursor, ".cc") ||
				ends_with(*cursor, ".C") || ends_with(*cursor, ".cxx"))
			{
				language = "c++";
			}
		}
		++cursor;
	}

	if (!language.empty()) {
		args.push_back("-x");
		args.push_back(language);
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
