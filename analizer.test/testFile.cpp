
#include <sstream>
#include <gtest/gtest.h>
#include <File.h>

using namespace std;

TEST(FileTest, Construction1)
{
	istringstream in("line1\nline2\nline3\n");
	File file(in);
}
