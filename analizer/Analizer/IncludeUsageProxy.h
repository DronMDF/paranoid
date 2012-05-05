
#pragma once
#include <list>
#include <memory>
#include <set>

class Token;
class TokenInclude;
class IncludedFile;

class IncludeUsageProxy {
public:
	IncludeUsageProxy(const std::shared_ptr<const TokenInclude> &token,
		const std::shared_ptr<const IncludedFile> &file,
		const std::list<std::shared_ptr<const IncludedFile>> &included_stack 
			= std::list<std::shared_ptr<const IncludedFile>>());

	bool unused() const;
	
	std::shared_ptr<const TokenInclude> getToken() const;
	bool checkName(const std::string &name);
	
private:
	std::shared_ptr<const TokenInclude> token;
	std::list<IncludeUsageProxy> includes;
	std::set<std::string> names;
	bool used;
	std::list<std::shared_ptr<const IncludedFile>> included_stack;
	
	void getName(const std::shared_ptr<const Token> &token, 
		const std::shared_ptr<const IncludedFile> &file);
};
