
#include <unistd.h>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
	vector<const char *> args(argv, argv + argc);
	args[0] = "gcc";
	args.push_back(0);
	
	return execvp("gcc", const_cast<char **>(&args[0]));
}
