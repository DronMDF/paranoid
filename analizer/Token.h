
#pragma once

#include <string>

class Line;

class Token {
public:
	Token();
	Token(const Line *line, unsigned offset, unsigned length);
	
	std::string getText() const;
	
private:
	const Line *line;
	unsigned offset;
	unsigned length;
};
