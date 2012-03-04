
#pragma once
#include <list>
#include <string>

class IncludePath {
public:
	virtual ~IncludePath();
	std::list<std::string> getQuotedPath() const;
	std::list<std::string> getSystemPath() const;
};
