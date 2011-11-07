
#include <sstream>
#include <boost/range/algorithm/transform.hpp>
#include <boost/test/unit_test.hpp>
#include <File.h>
#include <FileLine.h>
#include <Preprocessor.h>
#include "../Assertions.h"

using namespace std;
using boost::transform;

BOOST_AUTO_TEST_SUITE(suitePreprocessor)

BOOST_AUTO_TEST_CASE(testConstruct)
{
	struct testPreprocessor : public Preprocessor {
		testPreprocessor() : Preprocessor("test.cpp") {}
		virtual ~testPreprocessor() { 
			BOOST_REQUIRE_EQUAL(files.front().second->getLocation(), "test.cpp");
		}
	} pp;
}

BOOST_AUTO_TEST_CASE(testTokenize)
{
	Preprocessor pp("test.cpp");
	// TODO: replace inner File to stub.
	
	// TODO: pp.tokenize();	<- this is command
	
	list<string> tokens;
	pp.getTokens([&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t->getText()); });
	
	list<string> expected = { "int", " ", "main(int", " ", "argc,", " ", 
		"char", " ", "**argv)", " ", "{", " ", "return", " ", "0;", " ", "}" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

// BOOST_AUTO_TEST_CASE(testTokenizer)
// {
// 	istringstream in("int main(int argc, char **argv)\n{\n\treturn 0;\n}\n");
// 	const File file(in);
// 	const Preprocessor pp(file);
// 	
// 	list<string> pp_tok;
// 	transform(pp, back_inserter(pp_tok), [](const Token &t){ return t.getText(); });
// 	
// 	list<string> expected = { "int", " ", "main(int", " ", "argc,", " ", 
// 		"char", " ", "**argv)", " ", "{", " ", "return", " ", "0;", " ", "}" };
// 	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(pp_tok, expected);
// }

// struct TestPreprocessor : public Preprocessor {
// 	TestPreprocessor() : Preprocessor() {}
// 	using Preprocessor::addToken;
// };
// 
// BOOST_FIXTURE_TEST_CASE(testAddToken, TestPreprocessor)
// {
// 	addToken(Token());
// 	BOOST_REQUIRE(begin() == end());
// }
// 
// BOOST_FIXTURE_TEST_CASE(testAddTokenMultipleSpaces, TestPreprocessor)
// {
// 	const shared_ptr<const Line> line(new FileLine(0, "text", 0));
// 	addToken(Token(line, 0, 4));
// 	addToken(Token());
// 	addToken(Token());
// 	
// 	list<string> values;
// 	transform(*this, back_inserter(values), [](const Token &t){ return t.getText(); });
// 	
// 	list<string> expected = { "text", " " };
// 	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(values, expected);
// }
// 
// BOOST_AUTO_TEST_CASE(testOneLineComment)
// {
// 	istringstream in("int main(); // comment\n");
// 	const File file(in);
// 	const Preprocessor pp(file);
// 	
// 	list<string> pp_tok;
// 	transform(pp, back_inserter(pp_tok), [](const Token &t){ return t.getText(); });
// 	
// 	//list<const char *> expected = { "int", " ", "main", "(", ")", ";", " " };
// 	list<const char *> expected = { "int", " ", "main();" };
// 	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(pp_tok, expected);
// }

BOOST_AUTO_TEST_SUITE_END()
