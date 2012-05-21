
#pragma once
#include <functional>
#include <list>

class Error;

class ErrorList {
public:
	ErrorList();

	void insert(const Error &);
	void forEachError(std::function<void (const Error &e)> f) const;
	
private:
	std::list<Error> errors;
};

