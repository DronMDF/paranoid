
#pragma once
#include <list>
#include <string>

class IncludePath {
public:
	virtual ~IncludePath();
	std::list<std::string> getQuotedPath() const;
	std::list<std::string> getSystemPath() const;
	
private:
	virtual std::list<std::string> readSpec() const;
	std::list<std::string> getPath(const std::string &pattern) const;
};
