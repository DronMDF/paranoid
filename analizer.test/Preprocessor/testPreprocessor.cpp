
#include <boost/range/algorithm/transform.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/foreach.hpp>
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
		using Preprocessor::files;
	} pp;

	BOOST_REQUIRE_EQUAL(pp.files.front().second->getLocation(), "test.cpp");
}

BOOST_AUTO_TEST_CASE(testTokenize)
{
	struct testPreprocessor : public Preprocessor {
		testPreprocessor() : Preprocessor("test.cpp") {}
		using Preprocessor::files;
	} pp;
	
	// Replace the file in pp
	struct testFile : public File {
		testFile() : File(0, "test.cpp") {}
		typedef shared_ptr<const Line> line_ptr;
		virtual void forEachLine(function<void (const line_ptr &)> lineparser) const {
			list<string> source = { "int main(int argc, char **argv) {", " return 0;", " }" };
			int lineno = 1;
			BOOST_FOREACH(const auto &source_line, source) {
				line_ptr line(new FileLine(lineno++, source_line, this));
				lineparser(line);
			}
		}
	};
	pp.files.clear();
	pp.files.push_back(make_pair("test.cpp", shared_ptr<File>(new testFile())));
	
	// Parse
	pp.tokenize();
	
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
