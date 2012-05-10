
#include "ExpressionDefine.h"
#include "ExpressionIfBlock.h"
#include "ExpressionIfDirective.h"

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

string ExpressionIfBlock::getIfndefVariable() const
{
	BOOST_FOREACH(const auto &token, tokens) {
		if (isSpace(token)) {
			continue;
		}
		
		if (auto iexp = dynamic_pointer_cast<const ExpressionIfDirective>(token)) {
			if (iexp->getDirective() == "#ifndef") {
				auto used = iexp->getUsedNames();
				if (used.size() == 1) {
					return *used.begin();
				}
			}
		}
		
		break;		
	}
	
	return "";
}

string ExpressionIfBlock::getDefinedVariable() const
{
	BOOST_FOREACH(const auto &token, tokens) {
		if (isSpace(token) || isEol(token)) {
			continue;
		}
		
		if (dynamic_pointer_cast<const ExpressionIfDirective>(token)) {
			continue;
		}
		
		if (auto dexp = dynamic_pointer_cast<const ExpressionDefine>(token)) {
			auto declared = dexp->getDeclaredNames();
			if (declared.size() == 1) {
				return *declared.begin();
			}
		}
		
		break;		
	}
	
	return "";
}

string ExpressionIfBlock::getIncludeGuardName() const
{
	const auto macro = getIfndefVariable();
	const auto define = getDefinedVariable();

	if (macro.empty() or macro != define) {
		return "";
	}
	
	return macro;
}

