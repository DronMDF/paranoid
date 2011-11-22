
#include <boost/range/algorithm/transform.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/foreach.hpp>
#include <Preprocessor/File.h>
#include <Preprocessor/Line.h>
#include <Preprocessor/Preprocessor.h>
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
		testFile() : File("test.cpp") {}
		typedef shared_ptr<const Line> line_ptr;
		virtual void forEachLine(function<void (const line_ptr &)> lineparser) const {
			list<string> source = { "int main(int argc, char **argv) {", " return 0;", " }" };
			int lineno = 1;
			BOOST_FOREACH(const auto &source_line, source) {
				line_ptr line(new Line(lineno++, source_line, this));
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
	
	list<string> expected = { "int", " ", "main", "(", "int", " ", "argc", ",", " ", 
		"char", " ", "*", "*", "argv", ")", " ", "{", "\n", 
		" ", "return", " ", "0", ";", "\n", " ", "}", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_AUTO_TEST_SUITE_END()
