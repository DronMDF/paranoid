
#pragma once
#include <list>
#include <string>

class IncludePath {
public:
	explicit IncludePath(const std::list<std::string> &command_line);
	virtual ~IncludePath();
	std::list<std::string> getQuotedPath() const;
	std::list<std::string> getSystemPath() const;
	
private:
	virtual std::list<std::string> readSpec(const std::list<std::string> &args) const;
	std::list<std::string> getPath(const std::string &pattern) const;
	
	std::list<std::string> args;
};
