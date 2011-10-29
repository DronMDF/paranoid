
#pragma once

#include <string>

class Line {
public:
	virtual ~Line() {};
	
	virtual std::string getText() const = 0;
	virtual std::string getLocation() const = 0;
};
