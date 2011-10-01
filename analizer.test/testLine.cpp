

#include <sstream>
#include <gtest/gtest.h>

#include <File.h>
#include <Line.h>

using namespace std;

TEST(Line, GetFilePointer)
{
	istringstream in("");
	File file(in);
	Line line(10, "test", &file);
	ASSERT_EQ(line.getFile(), &file);
}
