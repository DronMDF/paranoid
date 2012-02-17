
#include "ExpressionDefine.h"

using namespace std;

ExpressionDefine::ExpressionDefine(const list<shared_ptr<const Token>> &tokens)
	: TokenList(tokens)
{
}
	
list<string> ExpressionDefine::getUsedNames() const
{
	return {};
}
