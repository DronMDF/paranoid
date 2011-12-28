
#pragma once
#include <string>

class File;

class Line {
public:
	Line() = delete;
	Line(const Line &line) = delete;
	Line(unsigned number, const std::string &text, const File *file);
	virtual ~Line();

	Line &operator = (const Line &) = delete;
	
	virtual std::string getText() const;
	virtual std::string getLocation() const;
	virtual std::string getFileName() const;

private:
	const unsigned number;
	const std::string text;
	const File *file;
};
