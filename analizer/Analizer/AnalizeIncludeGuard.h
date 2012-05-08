
#pragma once
#include <memory>
class File;

template <typename ErrorInsertIterator>
class AnalyzeIncludeGuard {
private:
	ErrorInsertIterator ei;
public:
	AnalyzeIncludeGuard(ErrorInsertIterator ei) 
		: ei(ei)
	{
	}
	
	void operator() (const std::shared_ptr<File> &file __attribute__((unused))) 
	{
	}	
};

