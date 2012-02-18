
#include <Preprocessor/TokenPredicate.h>
#include <Preprocessor/TokenInclude.h>
#include "AnalizeToken.h"
#include "ExpressionDefine.h"

using namespace std;

AnalizeToken::AnalizeToken()
	: includes(), unclassified(false)
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
	
	// TODO: collect names
	if (dynamic_cast<const ExpressionDefine *>(token.get()) != 0) {
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
