
#pragma once

#include <string>

class Line {
public:
	Line(unsigned number, const std::string &text);
	
	unsigned getNumber() const;
	std::string getText() const;
	
private:
	const unsigned number;
	const std::string text;
};
