
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
	
	if (dynamic_cast<const TokenInclude *>(token.get()) != 0) {
		includes.push_back(token);
		return;
	}
	
	if (auto exp = dynamic_cast<const ExpressionDefine *>(token.get())) {
		auto token_names = exp->getUsedNames();
		names.insert(token_names.begin(), token_names.end());
		return;
	} 
	
	// TODO: expression parser
	
	unclassified = true;
}

list<shared_ptr<const Token>> AnalizeToken::getIncludes() const
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
