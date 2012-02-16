
#pragma once
#include <memory>

class File;
class Error;

class Analizer {
public:
	void operator()(const std::shared_ptr<File> &file);
	
	std::list<Error> getResult() const;
};
