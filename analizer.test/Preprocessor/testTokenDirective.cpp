#include <boost/test/unit_test.hpp>
#include <Preprocessor/TokenDirective.h>
#   include "DummyToken.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenDirective)

BOOST_AUTO_TEST_CASE(testDirectiveWithSpace)
{
	TokenDirective token({
		make_shared<DummyToken>("#"),
		make_shared<DummyToken>(" "),
		make_shared<DummyToken>(" "),
		make_shared<DummyToken>("include"),
	});
	
	BOOST_REQUIRE_EQUAL(token.getText(), "#include");
}

BOOST_AUTO_TEST_SUITE_END()
