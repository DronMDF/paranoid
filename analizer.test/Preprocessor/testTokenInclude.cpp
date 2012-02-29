
#include <boost/test/unit_test.hpp>
#include <Preprocessor/TokenInclude.h>
#include <Preprocessor/TokenSpace.h>
#include <Preprocessor/File.h>
#include "../TokenStub.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenInclude)

BOOST_AUTO_TEST_CASE(testFile)
{
	TokenInclude ti({});
	auto file = make_shared<File>("test.h");
	ti.include(file);
	
	BOOST_REQUIRE_EQUAL(ti.getIncludedFile(), file);
}

BOOST_AUTO_TEST_CASE(testSystemInclude)
{
	TokenInclude ti({
		make_shared<TokenStub>("#include"),
		make_shared<TokenStub>(" "),
		make_shared<TokenStub>("<"),
		make_shared<TokenStub>("test.h"),
		make_shared<TokenStub>(">")});
	//ti.include(shared_ptr<File>());
	BOOST_REQUIRE(ti.isSystem());
	BOOST_REQUIRE_EQUAL(ti.getHeaderName(), "test.h");
}

BOOST_AUTO_TEST_CASE(testLocalInclude)
{
	TokenInclude ti({
		make_shared<TokenStub>("#include"),
		make_shared<TokenStub>(" "),
		make_shared<TokenStub>("\"local.h\"")});
	//ti.include(shared_ptr<File>());
	BOOST_REQUIRE(!ti.isSystem());
	BOOST_REQUIRE_EQUAL(ti.getHeaderName(), "local.h");
}

BOOST_AUTO_TEST_SUITE_END()
