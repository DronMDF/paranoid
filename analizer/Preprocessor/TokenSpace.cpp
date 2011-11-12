
#include "TokenSpace.h"

using namespace std;

TokenSpace::TokenSpace(const shared_ptr<const Line> &line, 
		       string::size_type begin, string::size_type end)
	: TokenWord(line, begin, end)
{
}

string TokenSpace::getText() const
{
	return " ";
}
