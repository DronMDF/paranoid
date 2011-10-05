
#include <sstream>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <gtest/gtest.h>

#include <File.h>
#include <Preprocessor.h>

using namespace std;
using namespace boost;

TEST(Preprocessor, Tokenizer)
{
	istringstream in("int main(int argc, char **argv)\n{\n\treturn 0;\n}\n");
	const File file(in);
	const Preprocessor pp(file);
	
	// Текст разбивается на слова и пробелы, к которым относятся так же табы и переносы строк
	const char * expected[] = { "int", " ", "main(int", " ", "argc,", " ", 
		"char", " ", "**argv)", " ", "{", " ", "return", " ", "0;", " ", "}" };

	list<string> pp_tok;
	transform(pp, back_inserter(pp_tok), bind(&Token::getText, _1));
	
	ASSERT_TRUE(equal(pp_tok, expected));
}
