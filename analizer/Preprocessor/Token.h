
#pragma once
#include <memory>
#include <string>

class Line;
class File;

class Token {
public:
	virtual ~Token();
	
	virtual std::string getText() const = 0;
	virtual std::string getLocation() const = 0;
	virtual std::string getFileName() const = 0;
	virtual std::shared_ptr<const Line> getLine() const = 0;
	virtual size_t getBeginPos() const = 0;
	virtual size_t getEndPos() const = 0;
};
