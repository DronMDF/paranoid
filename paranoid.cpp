
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include "CommandLine.h"
#include "analizer/File.h"
#include "analizer/Preprocessor.h"

using namespace std;
using namespace boost::filesystem;

void checkSource(const vector<const char *> &args)
{
	if (string(args[0]) == "gcc" || string(args[0]) == "g++") {
		const string source = getSourceFile(args);
		if (source.empty()) {
			// Компилятор прокачивается на стандартный ввод
			return;
		}
		
		if (!exists(source)) {
			BOOST_FOREACH(const char *a, args) {
				cout << "'" << a << "' ";
			}
			cout << endl;
			
			cout << "error: unknown source " << source << " in command line" << endl;
			// Временно, пока не отладим аргументы командной строки
			exit(-1);
		}
		
		ifstream in(source);
		const File file(in);
		const Preprocessor pp(file);
	}
}

int main(int argc, const char **argv)
{
	vector<const char *> args = Chaining(argc, argv);

	checkSource(args);
	
	args.push_back(0);
	return execvp(args[0], const_cast<char **>(&args[0]));
}
