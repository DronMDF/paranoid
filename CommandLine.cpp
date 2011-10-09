
#include <list>
#include <vector>
#include <boost/bind.hpp>
#include <boost/range/algorithm/find_if.hpp>

using namespace std;
using namespace boost;

vector<const char *> Chaining(int argc, const char **argv)
{
	list<const char *> args(argv, argv + argc);
	args.pop_front();
	
	list<const char *>::iterator chain = find_if(args, bind(strcmp, _1, "-chain") == 0);
	if (chain != args.end()) {
		list<const char *>::iterator cexec = args.erase(chain);
		if (cexec != args.end()) {
			args.push_front(*cexec);
			args.erase(cexec);
		}
	} else {
		args.push_front("gcc");
	}

	args.push_back(0);
	return vector<const char *>(args.begin(), args.end());
}
