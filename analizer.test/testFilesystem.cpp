
#include <boost/test/unit_test.hpp>
#include <Filesystem.h>

BOOST_AUTO_TEST_SUITE(suiteFilesystem)

BOOST_AUTO_TEST_CASE(testDirname)
{
	BOOST_REQUIRE_EQUAL(dirname("test.cpp"), ".");
	BOOST_REQUIRE_EQUAL(dirname("a/b/c/d/test.cpp"), "a/b/c/d");
	BOOST_REQUIRE_EQUAL(dirname("/root/sub/test.cpp"), "/root/sub");
}

BOOST_AUTO_TEST_CASE(testCanonical)
{
	BOOST_REQUIRE_EQUAL(canonical("test.cpp"), "test.cpp");
	BOOST_REQUIRE_EQUAL(canonical("./test.cpp"), "./test.cpp");
	BOOST_REQUIRE_EQUAL(canonical("/root/././././test.cpp"), "/root/test.cpp");
	BOOST_REQUIRE_EQUAL(canonical(".///test.cpp"), "./test.cpp");
	BOOST_REQUIRE_EQUAL(canonical("/root/sub/../test.cpp"), "/root/test.cpp");
}

BOOST_AUTO_TEST_SUITE_END()
