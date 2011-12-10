
#pragma once

#include <list>
#include <memory>
#include <string>

class File;
class Line;
class Token;
class TokenInclude;

// Preprocessor is main class for parse raw source
class Preprocessor {
public:
	// TODO: construct with include/sysinclude paths
	explicit Preprocessor(const std::string &filename);
	virtual ~Preprocessor();

	void tokenize();
	void getTokens(std::function<void (const std::shared_ptr<const Token> &)> add_token) const;
	
protected:
	void include(const std::shared_ptr<TokenInclude> &token, const std::string &file, bool system);
	
	std::list<std::pair<std::string, std::shared_ptr<File>>> files;
};
