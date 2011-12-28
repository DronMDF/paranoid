
#pragma once
#include <list>
#include <string>
#include <vector>

class TokenInclude;

class IncludeLocator {
public:
	IncludeLocator(const std::vector<const char *> &args, const std::list<std::string> spec_path);
	virtual ~IncludeLocator();
	
	std::string locate(const std::shared_ptr<const TokenInclude> &token) const;
	
private:
	virtual bool isExists(const std::string &include) const;
	
	std::list<std::string> system_paths;
	std::list<std::string> local_paths;
};
