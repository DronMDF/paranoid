
#pragma once

#include <string>
#include <list>

class Locator {
public:
	Locator();
	
	std::string toString() const;
	
	void setFileName(const std::string &name);
	void setLineNumber(unsigned number);
	
private:
	std::list<std::pair<std::string, unsigned>> path;
};
