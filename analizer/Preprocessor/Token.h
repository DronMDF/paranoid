
#pragma once

#include <string>
#include <memory>

class Line;

class Token {
public:
	Token();
	Token(const std::shared_ptr<const Line> &line, unsigned offset, unsigned length);
	
	std::string getText() const;
	std::string getLocation() const;
	// TODO: need pass style formatter
	std::string getTextInString() const;
	
private:
	const std::shared_ptr<const Line> line;
	const unsigned offset;
	const unsigned length;
};
