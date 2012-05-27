
#pragma once
#include <functional>
#include <list>
#include <map>
#include <memory>

class Token;
class File;
class Error;
class ErrorList;

class AnalyzeIncludeGuard {
public:
	AnalyzeIncludeGuard(ErrorList *el);
	AnalyzeIncludeGuard(const AnalyzeIncludeGuard &parent);
	
	void operator() (const std::shared_ptr<File> &file);

private:
	ErrorList *el;
	std::map<std::string, std::shared_ptr<const Token>> guarded;
	bool is_guarded;
	std::list<Error> current;
	
	void checkToken(const std::shared_ptr<const Token> &token);
	
	AnalyzeIncludeGuard &operator=(const AnalyzeIncludeGuard&) = delete;	
};

