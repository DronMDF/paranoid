
#include <functional>
#include <boost/foreach.hpp>
#include <Preprocessor/File.h>
#include <Preprocessor/TokenInclude.h>
#include <Preprocessor/TokenPredicate.h>
#include "IncludeUsageProxy.h"
#include "ExpressionDefine.h"

using namespace std;
using namespace std::placeholders;

IncludeUsageProxy::IncludeUsageProxy(const shared_ptr<const TokenInclude> &token)
	: token(token), includes(), names(), used(false)
{
	auto file = token->getIncludedFile();
	if (file) {
		file->forEachToken(bind(&IncludeUsageProxy::getName, this, _1));
	} else {
		names.insert("*");
	}
}

void IncludeUsageProxy::getName(const shared_ptr<const Token> &token)
{
	if (names.count("*") > 0) {
		return;
	}
	
	if (isSpace(token) || isEol(token)) {
		return;
	}

	if (auto include = dynamic_pointer_cast<const TokenInclude>(token)) {
		includes.push_back(IncludeUsageProxy(include));
		return;
	}
	
	if (auto exp = dynamic_pointer_cast<const ExpressionDefine>(token)) {
		BOOST_FOREACH(const auto &name, exp->getDeclaredNames()) {
			names.insert(name);
		}
		return;
	}
	
	names.insert("*");
}

shared_ptr<const TokenInclude> IncludeUsageProxy::getToken() const
{
	return token;
}

bool IncludeUsageProxy::checkName(const string &name)
{
	if (used) {
		return true;
	}
	
	if (name == "*") {
		used = true;
		return true;
	}
	
	if (names.count("*") > 0) {
		used = true;
		return true;
	}
	
	if (names.count(name) > 0) {
		used = true;
		return true;
	}
	
	BOOST_FOREACH(auto &inc, includes) {
		if (inc.checkName(name)) {
			used = true;
			return true;
		}
	}
	
	return false;
}

bool IncludeUsageProxy::unused() const
{
	return !used;
}
