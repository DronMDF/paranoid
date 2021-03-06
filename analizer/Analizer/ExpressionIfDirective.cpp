
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <Preprocessor/TokenPredicate.h>
#include "ExpressionIfDirective.h"

using namespace std;
using boost::all;
using boost::is_digit;

ExpressionIfDirective::ExpressionIfDirective(const list<shared_ptr<Token>> &tokens)
	: Expression(tokens)
{
}

set<string> ExpressionIfDirective::getUsedNames() const
{
	auto token = tokens.begin();
	
	if ((*token)->getText() == "#ifdef" or (*token)->getText() == "#ifndef") {
		++token;
		BOOST_ASSERT(isSpace(*token) or (*token)->getText() == " ");
		++token;
		return { (*token)->getText() };
	}

	if ((*token)->getText() == "#if") {
		++token;
		BOOST_ASSERT(isSpace(*token) or (*token)->getText() == " ");
		++token;
		if (all((*token)->getText(), is_digit())) {
			return {};
		}
	}
	
	// TODO: parse expressions
	return {"*"};
}

set<string> ExpressionIfDirective::getDeclaredNames() const
{
	return {};
}

string ExpressionIfDirective::getDirective() const
{
	return tokens.front()->getText();
}
