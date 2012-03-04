
#include <boost/test/unit_test.hpp>
#include "../Assertions.h"

using namespace std;

// TODO: Move to production
class IncludePath {
public:
	virtual ~IncludePath();
	list<string> getQuotedPath() const { return {}; };
	list<string> getSystemPath() const { return {}; };
};

IncludePath::~IncludePath() = default;

BOOST_AUTO_TEST_SUITE(suiteIncludePath)

BOOST_AUTO_TEST_CASE(testParseVerbose)
{
	struct testIncludePath : IncludePath {
		const list<string> lines;
		testIncludePath(const list<string> &lines) : lines(lines) { }
		// TODO: Suspend invoking compiler
	};
	
	// lines produced by gcc: 'echo | gcc -v -E -'
	testIncludePath tip({
		"#include \"...\" search starts here:",
		"#include <...> search starts here:",
		"/usr/lib/gcc/i686-pc-linux-gnu/4.5.3/include",
		"/usr/lib/gcc/i686-pc-linux-gnu/4.5.3/include-fixed",
		"/usr/include",
		"End of search list." });
	
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tip.getQuotedPath(), list<string>());
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tip.getSystemPath(), {
		"/usr/lib/gcc/i686-pc-linux-gnu/4.5.3/include",
		"/usr/lib/gcc/i686-pc-linux-gnu/4.5.3/include-fixed",
		"/usr/include" });
}

BOOST_AUTO_TEST_SUITE_END()
