
#pragma once
#include <list>
#include <memory>
#include <set>

class Token;

class AnalizeToken {
public:
	AnalizeToken();

	void checkToken(const std::shared_ptr<const Token> &token);
	std::list<std::shared_ptr<const Token>> getIncludes() const;
	bool isAllClassified() const;

	std::set<std::string> getUsedNames() const;
	
private:
	std::list<std::shared_ptr<const Token>> includes;
	std::set<std::string> names;
	bool unclassified;
};
