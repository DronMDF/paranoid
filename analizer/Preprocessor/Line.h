
#pragma once

#include <string>
#include "Location.h"

struct Line : public Location {
	virtual ~Line() {};
	virtual std::string getText() const = 0;
};

class File;

class FileLine : public Line {
public:
	FileLine(const FileLine &line);
	FileLine(unsigned number, const std::string &text, const Location *file);
	virtual ~FileLine();
	
	virtual std::string getText() const;
	virtual std::string getLocation() const;

protected:
	FileLine();
private:
	FileLine &operator = (const FileLine &);
	
	const unsigned number;
	const std::string text;
	const Location *file;
};
