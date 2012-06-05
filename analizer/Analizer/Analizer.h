
#pragma once
#include <memory>

class File;
class ErrorList;

class Analizer {
public:
	Analizer(ErrorList *el);
	
	void operator()(const std::shared_ptr<const File> &file) const;	
	
private:
	ErrorList *el;
};
