
#include <sstream>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <gtest/gtest.h>
#include <File.h>

using namespace std;
using namespace boost;

TEST(File, Construction1)
{
	istringstream in("line1\nline2\nline3\n");
	const File file(in);
	File::const_iterator it = file.begin();
	ASSERT_EQ(it->getNumber(), 1U);
	ASSERT_EQ(it->getText(), "line1");
	++it;
	ASSERT_EQ(it->getNumber(), 2U);
	ASSERT_EQ(it->getText(), "line2");
	++it;
	ASSERT_EQ(it->getNumber(), 3U);
	ASSERT_EQ(it->getText(), "line3");
	++it;
	ASSERT_EQ(it->getNumber(), 4U);
	ASSERT_TRUE(it->getText().empty());
	++it;
	ASSERT_EQ(it, file.end());
}

TEST(File, Foreach)
{
	istringstream in("line1\nline2\nline3\n");
	const File file(in);
	unsigned number = 1;
	BOOST_FOREACH(const Line &line, file) {
		ASSERT_EQ(line.getNumber(), number);
		if (number < 4) {
			ASSERT_EQ(line.getText(), "line" + lexical_cast<string>(number));
		} else {
			ASSERT_TRUE(line.getText().empty());
		}
		number++;
	}
}
