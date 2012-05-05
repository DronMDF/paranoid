
#include <boost/foreach.hpp>
#include <Preprocessor/TokenInclude.h>
#include <Preprocessor/TokenPredicate.h>
#include "AnalizeInclude.h"
#include "Expression.h"

using namespace std;

AnalizeInclude::AnalizeInclude()
	: includes()
{
}

void AnalizeInclude::checkToken(const shared_ptr<const Token> &token, 
	const shared_ptr<const IncludedFile> &file)
{
	if (isSpace(token) || isEol(token)) {
		return;
	}

	if (auto include = dynamic_pointer_cast<const TokenInclude>(token)) {
		includes.push_back(IncludeUsageProxy(include, file));
		return;
	}
	
	if (auto exp = dynamic_pointer_cast<const Expression>(token)) {
		BOOST_FOREACH(const auto &name, exp->getUsedNames()) {
			BOOST_FOREACH(auto &inc, includes) {
				inc.checkName(name);
			}
		}
		return;
	}

	// Unclassified token can use any names
	BOOST_FOREACH(auto &inc, includes) {
		inc.checkName("*");
	}
}

list<shared_ptr<const Token>> AnalizeInclude::getUnused() const
{
	list<shared_ptr<const Token>> unused;
	
	BOOST_FOREACH(const auto &ip, includes) {
		if (ip.unused()) {
			unused.push_back(ip.getToken());
		}
	}
	
	return unused;
}
