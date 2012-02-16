
#pragma once
#include <memory>

class File;
class Error;

class Analizer {
public:
	Analizer();
	
	void checkFile(const std::shared_ptr<File> &file);
	
	std::list<Error> getResult() const;
	
private:
	std::list<Error> errors;
};
