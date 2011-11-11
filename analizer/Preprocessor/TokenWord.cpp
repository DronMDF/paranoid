
#include "TokenWord.h"

using namespace std;

TokenWord::TokenWord(const shared_ptr<const Line> &line, unsigned begin, unsigned end)
	: Token(line, begin, end - begin)
{
}
