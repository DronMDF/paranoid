
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

string ExpressionIfBlock::getIncludeGuardName() const
{
	auto cursor = tokens.begin();
	
	while (isSpace(*cursor)) {
		++cursor;
	}
	
	string macro;
	if (auto iexp = dynamic_pointer_cast<const ExpressionIfDirective>(*cursor)) {
		if (iexp->getDirective() == "#ifndef") {
			auto used = iexp->getUsedNames();
			if (used.size() == 1) {
				macro = *used.begin();
			}
		}
	} else {
		return "";
	}
	
	++cursor;
	while (isSpace(*cursor) or isEol(*cursor)) {
		++cursor;
	}
	
	string define;
	if (auto dexp = dynamic_pointer_cast<const ExpressionDefine>(*cursor)) {
		auto declared = dexp->getDeclaredNames();
		if (declared.size() == 1) {
			define = *declared.begin();
		}
	}

	if (macro.empty() or macro != define) {
		return "";
	}
	
	return macro;
}

