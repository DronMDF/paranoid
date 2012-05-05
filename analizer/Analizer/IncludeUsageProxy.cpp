
#include <functional>
#include <algorithm>
#include <boost/foreach.hpp>
#include <Preprocessor/File.h>
#include <Preprocessor/Line.h>
#include <Preprocessor/TokenInclude.h>
#include <Preprocessor/TokenPredicate.h>
#include "IncludeUsageProxy.h"
#include "Expression.h"

using namespace std;
using namespace std::placeholders;

IncludeUsageProxy::IncludeUsageProxy(const shared_ptr<const TokenInclude> &token,
		const shared_ptr<const IncludedFile> &file,
		const list<shared_ptr<const IncludedFile>> &stack)
	: token(token), includes(), names(), used(false), included_stack(stack)
{
	included_stack.push_back(file);
	auto included = token->getIncludedFile();
	if (included) {
		auto iter = find(included_stack.begin(), included_stack.end(), included);
		if (iter == included_stack.end()) {
			included->forEachToken(bind(&IncludeUsageProxy::getName, this, _1, included));
		}
	} else {
		names.insert("*");
	}
}

void IncludeUsageProxy::getName(const shared_ptr<const Token> &token, 
	const shared_ptr<const IncludedFile> &file)
{
	if (names.count("*") > 0) {
		return;
	}
	
	if (isSpace(token) || isEol(token)) {
		return;
	}

	if (auto include = dynamic_pointer_cast<const TokenInclude>(token)) {
		includes.push_back(IncludeUsageProxy(include, file, included_stack));
		return;
	}
	
	if (auto exp = dynamic_pointer_cast<const Expression>(token)) {
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
