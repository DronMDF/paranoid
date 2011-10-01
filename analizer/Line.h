
#pragma once

#include <string>

class File;

class Line {
public:
	Line(const Line &line);
	Line(unsigned number, const std::string &text, const File *file);
	
	unsigned getNumber() const;
	std::string getText() const;
	const File *getFile() const;
	
private:
	Line &operator = (const Line &);
	
	const unsigned number;
	const std::string text;
	const File *file;
};
