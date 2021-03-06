
#include <algorithm>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "ExpressionDefine.h"

using namespace std;
using boost::is_digit;
using boost::all;

ExpressionDefine::ExpressionDefine(const list<shared_ptr<Token>> &tokens)
	: Expression(tokens)
{
}

set<string> ExpressionDefine::getUsedNamesFromToken(const shared_ptr<const Token> &token) const
{
	if (all(token->getText(), is_digit())) {
		return {};
	}
	
	return { token->getText() };
}

set<string> ExpressionDefine::getUsedNames() const
{
	auto token = tokens.begin();
	++token; // #define
	++token; // <space>
	++token; // <name>
	
	if (token == tokens.end()) {
		return {};
	}
	
	if ((*token)->getText() == "(") {
		// TODO: Get names from macro
		return {"*"};
	}
	
	++token; // <space>
	
	set<string> names;
	while (token != tokens.end()) {
		auto token_names = getUsedNamesFromToken(*token);
		names.insert(token_names.begin(), token_names.end());
		++token;
	}
	
	return names;
}

set<string> ExpressionDefine::getDeclaredNames() const
{
	auto token = tokens.begin();
	++token; // #define
	++token; // <space>
	return { (*token)->getText() };
}

void ExpressionDefine::replaceToken(const TokenExpression &/*expression*/, 
	function<shared_ptr<Token> (const list<shared_ptr<Token>> &)> /*creator*/)
{
	// TODO: This action only on expression
}
