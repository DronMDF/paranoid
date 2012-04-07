
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <Preprocessor/TokenPredicate.h>
#include "ExpressionIfDirective.h"

using namespace std;
using boost::is_digit;
using boost::all;

ExpressionIfDirective::ExpressionIfDirective(const list<shared_ptr<const Token>> &tokens)
	: TokenList(tokens)
{
}

set<string> ExpressionIfDirective::getUsedNames() const
{
	auto token = tokens.begin();
	if ((*token)->getText() == "#ifdef" or (*token)->getText() == "#ifndef") {
		++token;
		BOOST_ASSERT(isSpace(*token) or (*token)->getText() == " ");

		++token;
		if (all((*token)->getText(), is_digit())) {
			return {};
		}
		
		return { (*token)->getText() };
	}

	return {};
}

set<string> ExpressionIfDirective::getDeclaredNames() const
{
	return {};
}
