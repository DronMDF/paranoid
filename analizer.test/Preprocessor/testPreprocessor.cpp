
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

BOOST_AUTO_TEST_CASE(testInclude)
{
	struct testPreprocessor : public Preprocessor {
		testPreprocessor() : Preprocessor("test.cpp") {}
		using Preprocessor::files;
	} pp;
	
	typedef shared_ptr<const Line> line_ptr;
	
	struct testFile1 : public File {
		testFile1() : File("included.h") {}
		virtual void forEachLine(function<void (const line_ptr &)> lineparser) const {
			line_ptr line(new Line(1, "", this));
			lineparser(line);
		}
	};
	auto included = shared_ptr<File>(new testFile1());
	
	struct testFile2 : public File {
		testFile2() : File("includer.cpp") {}
		virtual void forEachLine(function<void (const line_ptr &)> lineparser) const {
			line_ptr line(new Line(1, "#include \"included.h\"", this));
			lineparser(line);
		}
	};
	
	auto includer = shared_ptr<File>(new testFile2());
	
	pp.files.push_back(make_pair("included.h", included));
	pp.files.push_back(make_pair("includer.cpp", includer));

	pp.tokenize();
	
	// included should be marked as 'included' from includer.cpp
	BOOST_REQUIRE_EQUAL(included->getLocation(), "includer.cpp:1\nincluded.h");
}

BOOST_AUTO_TEST_SUITE_END()
