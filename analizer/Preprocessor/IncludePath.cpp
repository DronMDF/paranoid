
#include "IncludePath.h"

using namespace std;

IncludePath::~IncludePath() = default;

list<string> IncludePath::readSpec() const 
{
	FILE *in = popen("gcc -v -E", "r");
	
	pclose(in);
	return {};
}

list<string> IncludePath::getQuotedPath() const 
{
	return {};
}

list<string> IncludePath::getSystemPath() const 
{
	return {};
}
