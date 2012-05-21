
#include <boost/test/unit_test.hpp>
#include <Preprocessor/Error.h>
#include <Preprocessor/ErrorFormatter.h>
#include "../TokenStub.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteErrorList);

class ErrorList {
public:
	void insert(const Error &) {};
	void forEachError(function<void (const Error &e)> f) {};
};

BOOST_AUTO_TEST_CASE(ShouldKeepInsertedMessages)
{
	// Given
	ErrorList el;
	//When
	el.insert(Error(make_shared<TokenStub>("test"), "numbers error"));
	el.insert(Error(make_shared<TokenStub>("next"), "next word error"));
	//Then
	string result;
	el.forEachError([&result](const Error &e){ return ErrorFormatter(e); });
	BOOST_REQUIRE_EQUAL(result, "test: numbers error\nnext: next word error\n");
}

BOOST_AUTO_TEST_SUITE_END();

