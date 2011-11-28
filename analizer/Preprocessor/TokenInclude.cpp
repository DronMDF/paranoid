
#include "TokenInclude.h"

using namespace std;

TokenInclude::TokenInclude(const list<shared_ptr<const Token>> &tokens)
	: TokenList(tokens)
{
}

void TokenInclude::include(const shared_ptr<const File> &file)
{
}
