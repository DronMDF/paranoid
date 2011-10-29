
#pragma once

#include <string>
#include "Line.h"

class File;

class FileLine : public Line {
public:
	FileLine(const FileLine &line);
	FileLine(unsigned number, const std::string &text, const File *file);
	virtual ~FileLine();
	
	virtual std::string getText() const;
	virtual std::string getLocation() const;

protected:
	FileLine();
private:
	FileLine &operator = (const FileLine &);
	
	const unsigned number;
	const std::string text;
	const File *file;
};
