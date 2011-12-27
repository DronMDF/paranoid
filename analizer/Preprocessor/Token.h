
#pragma once
#include <string>

class Token {
public:
	virtual ~Token();
	
	virtual std::string getText() const = 0;
	virtual std::string getLocation() const = 0;
	virtual std::string getTextInString(const std::string &begin_marker = std::string(), 
				    const std::string &end_marker = std::string()) const = 0;
	virtual std::string getFileName() const = 0;
};
