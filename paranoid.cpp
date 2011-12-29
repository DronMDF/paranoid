
#include <unistd.h>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <Preprocessor/Error.h>
#include <Preprocessor/File.h>
#include <Preprocessor/IncludeLocator.h>
#include <Preprocessor/Preprocessor.h>
#include <Preprocessor/TokenInclude.h>
#include <Preprocessor/TokenSpace.h>
#include "CommandLine.h"

using namespace std;
using namespace std::placeholders;
using boost::ends_with;
using boost::filesystem::exists;

void checkSource(const vector<const char *> &args)
{
	const string source = getSourceFile(args);
	if (source.empty()) {
		return;
	}

	if (exists(source) && (ends_with(source, ".cpp") || ends_with(source, ".c"))) {
		// TODO: pass paths in locator
		IncludeLocator locator({}, {});
		Preprocessor pp(bind(&IncludeLocator::locate, locator, _1), source);
		pp.tokenize();
		
		list<shared_ptr<const Token>> tokens;
		pp.getTokens(source, [&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t); });

		list<shared_ptr<const Token>> includes;
		list<shared_ptr<const Token>> others;
		BOOST_FOREACH(const auto &t, tokens) {
			if (dynamic_cast<const TokenInclude *>(t.get()) != 0) {
				includes.push_back(t);
			} else if (dynamic_cast<const TokenSpace *>(t.get()) == 0) {
				others.push_back(t);
			}
		}
		
		if (others.empty()) {
			BOOST_FOREACH(const auto &i, includes) {
				cerr << Error(*i, "Unused include").what() << endl;
			}
		}
	}
}

int main(int argc, const char **argv)
{
	vector<const char *> args = Chaining(argc, argv);

	try {
		checkSource(args);
	} catch (const exception &e) {
		cerr << e.what() << endl;
		return -1;	// Let it fail
	}
	
	if (args[0] == 0) {
		// No chaining
		return 0;
	}
	
	args.push_back(0);
	return execvp(args[0], const_cast<char **>(&args[0]));
}
