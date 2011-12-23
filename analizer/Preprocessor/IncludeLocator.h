
#pragma once
#include <list>
#include <string>
#include <vector>

class IncludeLocator {
public:
	IncludeLocator(const std::vector<const char *> &args, const std::list<std::string> spec_path);
	virtual ~IncludeLocator();
	
	std::string locate(const std::string &file, const std::string &include, bool system) const;
	
private:
	virtual bool isExists(const std::string &include) const;
	
	std::list<std::string> system_paths;
	std::list<std::string> local_paths;
};
