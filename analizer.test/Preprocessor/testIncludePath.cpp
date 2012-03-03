
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteIncludePath)

BOOST_AUTO_TEST_CASE(testParseVerbose)
{
	// lines produced by gcc: 'echo | gcc -v -E -'
	auto lines = {
		"#include \"...\" search starts here:",
		"#include <...> search starts here:",
		"/usr/lib/gcc/i686-pc-linux-gnu/4.5.3/include",
		"/usr/lib/gcc/i686-pc-linux-gnu/4.5.3/include-fixed",
		"/usr/include",
		"End of search list." };
	
	// TODO: parse this
}

BOOST_AUTO_TEST_SUITE_END()
