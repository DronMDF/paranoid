
#include <sstream>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/test/unit_test.hpp>

#include <File.h>
#include <Preprocessor.h>

using namespace std;
using namespace boost;

BOOST_AUTO_TEST_SUITE(suitePreprocessor)

BOOST_AUTO_TEST_CASE(Tokenizer)
{
	istringstream in("int main(int argc, char **argv)\n{\n\treturn 0;\n}\n");
	const File file(in);
	const Preprocessor pp(file);
	
	// Текст разбивается на слова и пробелы, к которым относятся так же табы и переносы строк
	const char * expected[] = { "int", " ", "main(int", " ", "argc,", " ", 
		"char", " ", "**argv)", " ", "{", " ", "return", " ", "0;", " ", "}" };

	list<string> pp_tok;
	transform(pp, back_inserter(pp_tok), bind(&Token::getText, _1));
	
	BOOST_REQUIRE_EQUAL_COLLECTIONS(pp_tok.begin(), pp_tok.end(), expected, expected + 17);
}

BOOST_AUTO_TEST_SUITE_END()
