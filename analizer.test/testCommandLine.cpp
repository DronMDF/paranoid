
#include <boost/range/algorithm/equal.hpp>
#include <gtest/gtest.h>
#include <CommandLine.h>

using namespace std;
using namespace boost;

TEST(CommandLine, Chaining)
{
	const char *argsrc[] = {"test", "-chain", "valid"};
	const char *argexpected[] = {"valid", 0};
	
	vector<const char *> argres = Chaining(3, argsrc);
	
	ASSERT_TRUE(equal(argres, argexpected));
}
