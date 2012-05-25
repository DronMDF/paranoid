
#include <boost/test/unit_test.hpp>
#include <Preprocessor/Error.h>
#include <Preprocessor/ErrorFormatter.h>
#include <Preprocessor/ErrorList.h>
#include "../TokenStub.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteErrorList);

BOOST_AUTO_TEST_CASE(ShouldKeepInsertedMessages)
{
	// Given
	ErrorList el;
	//When
	el.insert(Error(make_shared<TokenStub>("test"), "numbers error"));
	el.insert(Error(make_shared<TokenStub>("next"), "next word error"));
	//Then
	string result;
	el.forEachError([&result](const Error &e){ result += ErrorFormatter(e) + "\n"; });
	BOOST_REQUIRE_EQUAL(result, 
		"test.cxx:10 error: numbers error\ntest\n~~~~\n"
		"test.cxx:10 error: next word error\nnext\n~~~~\n");
}

BOOST_AUTO_TEST_SUITE_END();

