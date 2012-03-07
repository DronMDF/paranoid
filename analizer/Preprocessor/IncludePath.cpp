
#include "IncludePath.h"

using namespace std;

IncludePath::~IncludePath() = default;

list<string> IncludePath::readSpec() const 
{
	FILE *in = popen("sh -c 'echo | gcc -v -E -' 2>&1", "r");
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

list<string> IncludePath::getQuotedPath() const 
{
	return {};
}

list<string> IncludePath::getSystemPath() const 
{
	return readSpec();
}
