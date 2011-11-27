
#include <boost/test/unit_test.hpp>
#include <Preprocessor/TokenInclude.h>
#include <Preprocessor/File.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenInclude)

BOOST_AUTO_TEST_CASE(testConstruct)
{
	const list<shared_ptr<const Token>> tokens;
	TokenInclude ti(tokens, shared_ptr<File>(new File("test.cpp")));
}

BOOST_AUTO_TEST_SUITE_END()
