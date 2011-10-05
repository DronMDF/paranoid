
#pragma once

#include <string>

class Line;

class Token {
public:
	Token();
	Token(const Line *line, unsigned offset, unsigned len);
	
	std::string getText() const;
	
private:
	const Line *line;
	unsigned offset;
	unsigned lenght;
};
