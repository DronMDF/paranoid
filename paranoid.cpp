
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include "CommandLine.h"
#include "analizer/Preprocessor/File.h"
#include "analizer/Preprocessor/Preprocessor.h"

using namespace std;
using boost::ends_with;
using boost::filesystem::exists;

void checkSource(const vector<const char *> &args)
{
	const string source = getSourceFile(args);
	if (source.empty()) {
		return;
	}

	if (exists(source) && (ends_with(source, ".cpp") || ends_with(source, ".c"))) {
		Preprocessor pp(source);
		pp.tokenize();
	}
}

int main(int argc, const char **argv)
{
	vector<const char *> args = Chaining(argc, argv);

	try {
		checkSource(args);
	} catch (const exception &e) {
		cout << e.what() << endl;
	}
	
	if (args[0] == 0) {
		// No chaining
		return 0;
	}
	
	args.push_back(0);
	return execvp(args[0], const_cast<char **>(&args[0]));
}
