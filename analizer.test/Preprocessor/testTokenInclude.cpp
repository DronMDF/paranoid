
#include <boost/test/unit_test.hpp>
#include <Preprocessor/TokenInclude.h>
#include <Preprocessor/TokenSpace.h>
#include <Preprocessor/File.h>
#include "DummyToken.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenInclude)

BOOST_AUTO_TEST_CASE(testConstruct)
{
	TokenInclude ti({});
	ti.include(make_shared<File>("test.h"));
}

BOOST_AUTO_TEST_CASE(testSystemInclude)
{
	TokenInclude ti({
		make_shared<DummyToken>("#include"),
		make_shared<DummyToken>(" "),
		make_shared<DummyToken>("<"),
		make_shared<DummyToken>("test.h"),
		make_shared<DummyToken>(">")});
	//ti.include(shared_ptr<File>());
	BOOST_REQUIRE(ti.isSystem());
	BOOST_REQUIRE_EQUAL(ti.getHeaderName(), "test.h");
}

BOOST_AUTO_TEST_CASE(testLocalInclude)
{
	TokenInclude ti({
		make_shared<DummyToken>("#include"),
		make_shared<DummyToken>(" "),
		make_shared<DummyToken>("\"local.h\"")});
	//ti.include(shared_ptr<File>());
	BOOST_REQUIRE(!ti.isSystem());
	BOOST_REQUIRE_EQUAL(ti.getHeaderName(), "local.h");
}

BOOST_AUTO_TEST_SUITE_END()
