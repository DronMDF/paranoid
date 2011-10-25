
#pragma once

#include <string>
#include <memory>

class Line;
class Locator;

class Token {
public:
	Token();
	Token(const std::shared_ptr<const Line> &line, unsigned offset, unsigned length);
	
	std::string getText() const;
	
	void determoneLocation(Locator *locator) const;
	
private:
	const std::shared_ptr<const Line> line;
	const unsigned offset;
	const unsigned length;
};
