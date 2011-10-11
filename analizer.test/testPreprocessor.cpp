
#include <sstream>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/test/unit_test.hpp>
#include <File.h>
#include <Preprocessor.h>
#include "Assertions.h"

using namespace std;
using namespace boost;

BOOST_AUTO_TEST_SUITE(suitePreprocessor)

BOOST_AUTO_TEST_CASE(Tokenizer)
{
	istringstream in("int main(int argc, char **argv)\n{\n\treturn 0;\n}\n");
	const File file(in);
	const Preprocessor pp(file);
	
	list<string> pp_tok;
	transform(pp, back_inserter(pp_tok), [](const Token &t){ return t.getText(); });
	
	// Текст разбивается на слова и пробелы, к которым относятся так же табы и переносы строк
	list<const char *> expected = { "int", " ", "main(int", " ", "argc,", " ", 
		"char", " ", "**argv)", " ", "{", " ", "return", " ", "0;", " ", "}" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(pp_tok, expected);
}

BOOST_AUTO_TEST_SUITE_END()
