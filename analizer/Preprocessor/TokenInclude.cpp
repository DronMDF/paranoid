
#include "TokenInclude.h"

using namespace std;

TokenInclude::TokenInclude(const list<shared_ptr<const Token>> &tokens, const shared_ptr<const File> &file)
	: TokenList(tokens)
{
}
