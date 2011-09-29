
#include <sstream>
#include <gtest/gtest.h>
#include <File.h>

using namespace std;

TEST(FileTest, Construction1)
{
	istringstream in("line1\nline2\nline3\n");
	File file(in);
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
