
#include <sstream>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/File.h>
#include <Preprocessor/Line.h>
#include <Preprocessor/Token.h>
#include "../Assertions.h"

using namespace std;
using boost::lexical_cast;
using boost::transform;

BOOST_AUTO_TEST_SUITE(suiteFile)

BOOST_AUTO_TEST_CASE(testGetConstructedLocation)
{
	const File file("test.cpp");
	BOOST_REQUIRE_EQUAL(file.getLocation(), "test.cpp");
}

BOOST_AUTO_TEST_CASE(testTokenize)
{
	struct testFile : public File {
		testFile() : File("none") {}
		typedef shared_ptr<const Line> line_ptr;
		virtual void forEachLine(function<void (const line_ptr &)> lineparser) const {
			line_ptr line(new Line(7, "012345", this));
			lineparser(line);
		}
	} file;

	file.tokenize();
	
	list<string> tokens;
	file.getTokens([&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t->getText()); });
	
	list<string> expected = { "012345", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_AUTO_TEST_CASE(testTokenize2)
{
	struct testFile : public File {
		testFile() : File("none") {}
		typedef shared_ptr<const Line> line_ptr;
		virtual void forEachLine(function<void (const line_ptr &)> lineparser) const {
			line_ptr line(new Line(1, "aaa bbb", this));
			lineparser(line);
		}
	} file;

	file.tokenize();
	
	list<string> tokens;
	file.getTokens([&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t->getText()); });
	
	list<string> expected = { "aaa", " ", "bbb", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_AUTO_TEST_SUITE_END()
