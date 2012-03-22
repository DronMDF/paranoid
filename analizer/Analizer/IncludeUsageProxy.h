
#pragma once
#include <memory>

class TokenInclude;

class IncludeUsageProxy {
public:
	IncludeUsageProxy(const std::shared_ptr<const TokenInclude> &token);

	bool unused() const;
	
	std::shared_ptr<const TokenInclude> getToken() const;
private:
	std::shared_ptr<const TokenInclude> token;
};
