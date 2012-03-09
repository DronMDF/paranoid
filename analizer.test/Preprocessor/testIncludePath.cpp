
#include <boost/test/unit_test.hpp>
#include <Preprocessor/IncludePath.h>
#include "../Assertions.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteIncludePath)

BOOST_AUTO_TEST_CASE(testParseVerbose)
{
	struct testIncludePath : IncludePath {
		const list<string> lines;
		testIncludePath(const list<string> &lines) : lines(lines) { }
		// TODO: Suspend invoking compiler
		virtual list<string> readSpec() const { return lines; }
	};
	
	// lines produced by gcc: 'echo | gcc -v -E -'
	testIncludePath tip({
		"#include \"...\" search starts here:",
		"#include <...> search starts here:",
		" /usr/include",
		"End of search list." });
	
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tip.getQuotedPath(), list<string>());
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tip.getSystemPath(), {
		"/usr/include" });
}

BOOST_AUTO_TEST_SUITE_END()
