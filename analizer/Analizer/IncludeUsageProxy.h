
#pragma once
#include <list>
#include <memory>
#include <set>

class Token;
class TokenInclude;

class IncludeUsageProxy {
public:
	IncludeUsageProxy(const std::shared_ptr<const TokenInclude> &token);

	bool unused() const;
	
	std::shared_ptr<const TokenInclude> getToken() const;
	bool checkName(const std::string &name);
	
private:
	std::shared_ptr<const TokenInclude> token;
	std::list<IncludeUsageProxy> includes;
	std::set<std::string> names;
	bool used;
	
	void getName(const std::shared_ptr<const Token> &token);
};
