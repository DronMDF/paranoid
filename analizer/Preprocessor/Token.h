
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
	std::string getTextInString(const std::string &begin_marker = std::string(), 
				    const std::string &end_marker = std::string()) const;
	
private:
	const std::shared_ptr<const Line> line;
	const unsigned offset;
	const unsigned length;
};
