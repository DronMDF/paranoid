
#include "ExpressionIfBlock.h"

using namespace std;

ExpressionIfBlock::ExpressionIfBlock(const list<shared_ptr<Token>> &tokens)
	: Expression(tokens)
{
}

set<string> ExpressionIfBlock::getUsedNames() const
{
	// TODO: Accumulate names from subexpressions
	return {};
}

set<string> ExpressionIfBlock::getDeclaredNames() const
{
	// TODO: Accumulate names from subexpressions
	return {};
}

string ExpressionIfBlock::getIncludeGuardName() const
{
	return "";
}
