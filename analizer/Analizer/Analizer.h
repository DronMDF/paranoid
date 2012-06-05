
#pragma once
#include <map>
#include <set>
#include <memory>

class File;
class Error;
class ErrorList;
class Token;

class Analizer {
public:
	Analizer(ErrorList *el);
	
	void checkUsedIncludeInFile(const std::shared_ptr<const File> &file);
	
	std::list<Error> getResult() const;
	
private:
	ErrorList *el;
};
