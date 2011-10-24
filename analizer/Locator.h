
#pragma once

#include <string>
#include <list>

class Locator {
public:
	Locator();
	
	std::string toString() const;
	
	void setLineNumber(unsigned number);
	
private:
	std::list<std::pair<std::string, unsigned>> path;
};
