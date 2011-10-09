
#include <unistd.h>
#include <string>
#include <vector>
#include "CommandLine.h"

using namespace std;

int main(int argc, const char **argv)
{
	vector<const char *> args = Chaining(argc, argv);

	if (string(args[0]) == "gcc" || string(args[0]) == "g++") {
		// anayze
	}
	
	return execvp(args[0], const_cast<char **>(&args[0]));
}
