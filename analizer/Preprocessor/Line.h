
#pragma once
#include <string>

class File;

class Line {
public:
	Line(unsigned number, const std::string &text, const File *file);
	virtual ~Line();

	virtual std::string getText() const;
	virtual std::string getLocation() const;
	virtual std::string getFileName() const;

private:
	Line() = delete;
	Line(const Line &line) = delete;
	Line &operator = (const Line &) = delete;
	
	const unsigned number;
	const std::string text;
	const File *file;
};
