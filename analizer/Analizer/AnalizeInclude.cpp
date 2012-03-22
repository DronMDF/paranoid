
#include <boost/foreach.hpp>
#include <Preprocessor/TokenInclude.h>
#include "AnalizeInclude.h"

using namespace std;

AnalizeInclude::AnalizeInclude()
	: includes()
{
}

void AnalizeInclude::checkToken(const shared_ptr<const Token> &token)
{
	if (auto include = dynamic_pointer_cast<const TokenInclude>(token)) {
		includes.push_back(IncludeUsageProxy(include));
		return;
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
