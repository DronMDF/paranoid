
#include <boost/test/unit_test.hpp>
#include <CommandLine.h>
#include "Assertions.h"

using namespace std;
using namespace boost;

BOOST_AUTO_TEST_SUITE(suiteCommandLine)
	
BOOST_AUTO_TEST_CASE(testChaining)
{
	vector<const char *> argsrc = {"test", "-chain", "valid"};
	auto argres = Chaining(argsrc.size(), &argsrc[0]);
	
	list<const char *> argexpected = {"valid"};
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(argres, argexpected);
}

BOOST_AUTO_TEST_CASE(testGetSourceFile)
{
	vector<const char *> args = {"test", "file.cpp"};
	BOOST_REQUIRE_EQUAL(getSourceFile(args), "file.cpp");
}

BOOST_AUTO_TEST_CASE(testGetSourceFileWithOpts)
{
	vector<const char *> args = { "g++", "-MMD", "-MF", "../CommandLine.dep",
		"-std=c++0x", "-Wall", "-Wextra", "-ggdb3", "-O0", "-I..", 
		"-I../analizer", "-c", "-o", "../CommandLine.o", "../CommandLine.cpp"};
	BOOST_REQUIRE_EQUAL(getSourceFile(args), args.back());
}

BOOST_AUTO_TEST_CASE(testGetSourceFileWithFailOpts)
{
	vector<const char *> args = { "gcc", "-E", "-xc", "-" };
	BOOST_REQUIRE(getSourceFile(args).empty());
}

BOOST_AUTO_TEST_SUITE_END()
