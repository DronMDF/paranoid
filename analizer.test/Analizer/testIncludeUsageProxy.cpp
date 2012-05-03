
#include <boost/test/unit_test.hpp>
#include <Analizer/IncludeUsageProxy.h>
#include <Preprocessor/TokenInclude.h>
#include "../FileStub.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteIncludeUsageProxy)

BOOST_AUTO_TEST_CASE(ShouldPreventRecursion)
{
	// Given
	struct TestFile : public FileStub {
		shared_ptr<Token> token;
		TestFile(const shared_ptr<Token> &t) : FileStub("", list<string>()), token(t) {};
		void forEachToken(function<void (const shared_ptr<const Token> &)> func) const {
			func(token);	
		}	
	};
	auto token = make_shared<TokenInclude>(list<shared_ptr<Token>>());
	auto file = make_shared<TestFile>(token);
	token->include(file);
	//When
	IncludeUsageProxy proxy(token);
	// Then exited
}

BOOST_AUTO_TEST_SUITE_END()
