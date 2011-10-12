
#include <list>
#include <string>
#include <vector>
#include <boost/range/algorithm/find.hpp>
#include <boost/range/algorithm/find_if.hpp>

using namespace std;
using namespace boost;

vector<const char *> Chaining(int argc, const char **argv)
{
	list<const char *> args(argv, argv + argc);
	args.pop_front();
	
	auto chain = find_if(args, [](const char *a){ return string(a) == "-chain"; });
	if (chain != args.end()) {
		auto cexec = args.erase(chain);
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

string getSourceFile(const vector<const char *> &args)
{
	vector<string> wop = {"-MF", "-o", "-isystem"};
	for (unsigned i = 1; i < args.size(); ++i) {
		if (args[i] == 0) {
			break;
		}

		if (args[i][0] == '-') {
			if (find(wop, string(args[i])) != wop.end()) {
				++i;
			}
			continue;
		}
		
		return args[i];
	}
	return string();
}
