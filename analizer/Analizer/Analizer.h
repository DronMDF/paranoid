
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
	void collectNames(const std::shared_ptr<const File> &file);
	void checkFile(const std::shared_ptr<const File> &file);
	void checkUsedIncludeInFile(const std::shared_ptr<const File> &file);
	
	std::list<Error> getResult() const;
	
private:
	std::list<Error> errors;
	std::map<std::shared_ptr<const File>, std::set<std::string>> declarations;
	
	void addName(const std::shared_ptr<const File> &file, const std::shared_ptr<const Token> &token);
};
