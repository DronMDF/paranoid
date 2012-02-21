
#pragma once
#include <memory>

class File;
class Error;

class Analizer {
public:
	Analizer();
	
	void transformFile(const std::shared_ptr<File> &file) const;
	void checkFile(const std::shared_ptr<const File> &file);
	
	std::list<Error> getResult() const;
	
private:
	std::list<Error> errors;
};
