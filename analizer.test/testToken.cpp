
#include <gtest/gtest.h>

#include <Line.h>
#include <Token.h>

TEST(Token, GetTextFromLine)
{
	const Line line(10, "aaaxxxxxaaa", 0);
	const Token token(&line, 3, 5);
	ASSERT_EQ(token.getText(), "xxxxx");
}

TEST(Token, GetEmptyText)
{
	// Специальный случай Токена - пробельный токен
	const Token token;
	ASSERT_EQ(token.getText(), " ");
}
