
#pragma once

#include <string>

class Line;
class Locator;

class Token {
public:
	Token();
	Token(const Line *line, unsigned offset, unsigned length);
	
	std::string getText() const;
	
	void determoneLocation(Locator *locator) const;
	
private:
	const Line *line;
	unsigned offset;
	unsigned length;
};
