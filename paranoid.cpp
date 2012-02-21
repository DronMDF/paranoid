
#include <unistd.h>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <Analizer/Analizer.h>
#include <Preprocessor/Error.h>
#include <Preprocessor/ErrorFormatter.h>
#include <Preprocessor/File.h>
#include <Preprocessor/IncludeLocator.h>
#include <Preprocessor/Preprocessor.h>
#include <Preprocessor/TokenInclude.h>
#include <Preprocessor/TokenNewline.h>
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
		
		Analizer analizer;
		pp.forEachFile(bind(&Analizer::transformFile, &analizer, _1));
		pp.forEachFile(bind(&Analizer::checkFile, &analizer, _1));
		
		BOOST_FOREACH(const auto &e, analizer.getResult()) {
			cerr << ErrorFormatter(e) << endl;
		}
	}
}

int main(int argc, const char **argv)
{
	vector<const char *> args = Chaining(argc, argv);

	try {
		checkSource(args);
	} catch (const Error &e) {
		cerr << ErrorFormatter(e) << endl;
		return -1;	// Let it fail
	}
	
	if (args[0] == 0) {
		// No chaining
		return 0;
	}
	
	args.push_back(0);
	return execvp(args[0], const_cast<char **>(&args[0]));
}
