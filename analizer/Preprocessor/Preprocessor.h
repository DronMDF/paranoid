
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
	// TODO: construct with include/sysinclude paths
	explicit Preprocessor(
		std::function<std::string(const std::string &, const std::string &, bool)> locate, 
		const std::string &filename);
	virtual ~Preprocessor();

	void tokenize();
	void getTokens(std::function<void (const std::shared_ptr<const Token> &)> add_token) const;
	
protected:
	void include(const std::shared_ptr<TokenInclude> &token);
	
	std::function<std::string(const std::string &, const std::string &, bool)> locate;
	std::list<std::pair<std::string, std::shared_ptr<File>>> files;
};
