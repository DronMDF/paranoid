
#include <boost/test/unit_test.hpp>
#include <Preprocessor/TokenSpace.h>
#include <Preprocessor/TokenNewline.h>
#include "../FileStub.h"
#include "../TokenStub.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteExpressionTransformer)

class ExpressionTransformer {
public:
	void operator()(const std::shared_ptr<File> &) {};
};

BOOST_AUTO_TEST_CASE(ShouldTransformDefine)
{
	// Given
	list<shared_ptr<Token>> tokens = {
		make_shared<TokenStub>("#define"),
		make_shared<TokenSpace>(shared_ptr<Line>(), 0, 0),
		make_shared<TokenStub>("A"),
		make_shared<TokenNewline>(shared_ptr<Line>()),
	};
	auto file = make_shared<FileStub>(tokens);
	ExpressionTransformer trans;
	// When
	trans(file);
	// Then
	CUSTOM_EQUAL_FILE_TOKENS_TEXT(*file.get(), {"#define A", "\n"});
}

BOOST_AUTO_TEST_SUITE_END()

