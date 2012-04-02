
#pragma once
#include <map>
#include <set>
#include <memory>

class File;
class Error;
class Token;

class Analizer {
public:
	Analizer();
	
	void transformFile(const std::shared_ptr<File> &file) const;
	void checkUsedIncludeInFile(const std::shared_ptr<const File> &file);
	
	std::list<Error> getResult() const;
	
private:
	std::list<Error> errors;
};
