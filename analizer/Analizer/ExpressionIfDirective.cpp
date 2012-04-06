
#include "ExpressionIfDirective.h"

using namespace std;

ExpressionIfDirective::ExpressionIfDirective(const list<shared_ptr<const Token>> &tokens)
	: TokenList(tokens)
{
}

set<string> ExpressionIfDirective::getUsedNamesFromToken(const shared_ptr<const Token> &token) const
{
	return {};
}

set<string> ExpressionIfDirective::getUsedNames() const
{
	return {};
}

set<string> ExpressionIfDirective::getDeclaredNames() const
{
	return {};
}
