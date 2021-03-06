
#pragma once

#include <list>
#include <memory>
#include <string>

class File;
class Token;
class TokenInclude;

// Preprocessor is main class for parse raw source
class Preprocessor {
public:
	Preprocessor(std::function<std::string (const std::shared_ptr<const TokenInclude> &)> locate,
		const std::string &filename);
	virtual ~Preprocessor();

	void tokenize();
	
	void forEachFile(std::function<void (const std::shared_ptr<File> &)> analyzer);

protected:
	std::shared_ptr<Token> createIncludeToken(const std::list<std::shared_ptr<Token>> &tokens);

	std::function<std::string(const std::shared_ptr<const TokenInclude> &)> locate;
	std::list<std::pair<std::string, std::shared_ptr<File>>> files;
};
