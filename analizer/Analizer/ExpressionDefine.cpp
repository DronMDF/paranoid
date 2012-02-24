
#include <algorithm>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "ExpressionDefine.h"

using namespace std;
using boost::is_digit;
using boost::all;

ExpressionDefine::ExpressionDefine(const list<shared_ptr<const Token>> &tokens)
	: TokenList(tokens)
{
}

list<string> ExpressionDefine::getUsedNamesFromToken(const shared_ptr<const Token> &token) const
{
	if (all(token->getText(), is_digit())) {
		return {};
	}
	
	return { token->getText() };
}

list<string> ExpressionDefine::getUsedNames() const
{
	auto token = tokens.begin();
	++token; // #define
	++token; // <space>
	++token; // <name>
	++token; // <space>
	
	list<string> names;
	while (token != tokens.end()) {
		names.splice(names.end(), getUsedNamesFromToken(*token));
		++token;
	}
	
	return names;
}
