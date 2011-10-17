
#pragma once

#include <string>

class File;

// TODO: Line - Это будет интерфейс. 
//	Основная реализация FileLine
//	Дополнительно будут врапперы.

class Line {
public:
	Line(const Line &line);
	Line(unsigned number, const std::string &text, const File *file);
	virtual ~Line();
	
	virtual unsigned getNumber() const;
	virtual std::string getText() const;
	const File *getFile() const;
	
	virtual const Line *getPointer() const;
	
protected:
	Line();
private:
	Line &operator = (const Line &);
	
	const unsigned number;
	const std::string text;
	const File *file;
};
