
#include <iostream>
#include <boost/foreach.hpp>
#include <Preprocessor/TokenPredicate.h>
#include <Preprocessor/TokenInclude.h>
#include "AnalizeToken.h"
#include "ExpressionDefine.h"

using namespace std;

AnalizeToken::AnalizeToken()
	: includes(), names(), unclassified(false)
{
}

void AnalizeToken::checkToken(const shared_ptr<const Token> &token)
{
	if (isSpace(token) || isEol(token)) {
		return;
	}
	
	if (auto include = dynamic_pointer_cast<const TokenInclude>(token)) {
		includes.push_back(include);
		return;
	}
	
	if (auto exp = dynamic_pointer_cast<const ExpressionDefine>(token)) {
		auto token_names = exp->getUsedNames();
		names.insert(token_names.begin(), token_names.end());
		return;
	} 
	
	// TODO: expression parser
	
	unclassified = true;
}

list<shared_ptr<const TokenInclude>> AnalizeToken::getIncludes() const
{
	return includes;
}

bool AnalizeToken::isAllClassified() const
{
	return !unclassified;
}

set<string> AnalizeToken::getUsedNames() const
{
	return names;
}
