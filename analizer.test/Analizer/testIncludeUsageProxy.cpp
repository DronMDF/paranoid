
#include <boost/test/unit_test.hpp>
#include <Analizer/IncludeUsageProxy.h>
#include <Preprocessor/TokenInclude.h>
#include <Preprocessor/IncludedFile.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteIncludeUsageProxy)

BOOST_AUTO_TEST_CASE(ShouldPreventRecursion)
{
	// Given
	struct TestIncludedFile : public IncludedFile {
		shared_ptr<Token> token;
		mutable bool scaned;
		TestIncludedFile(const shared_ptr<Token> &t) : token(t), scaned(false) {};
		void forEachToken(function<void (const shared_ptr<const Token> &)> func) const {
			BOOST_REQUIRE(!scaned);
			scaned = true;
			func(token);
		}
	};
	auto token = make_shared<TokenInclude>(list<shared_ptr<Token>>());
	auto file = make_shared<TestIncludedFile>(token);
	token->include(file);
	//When
	IncludeUsageProxy proxy(token);
	// Then exited
}

BOOST_AUTO_TEST_SUITE_END()
