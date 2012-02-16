
#pragma once
#include <list>
#include <memory>

class Token;

class AnalizeToken {
public:
	AnalizeToken();

	void checkToken(const std::shared_ptr<const Token> &token);
	std::list<std::shared_ptr<const Token>> getIncludes() const;
	bool isAllClassified() const;

private:
	std::list<std::shared_ptr<const Token>> includes;
	bool unclassified;
};
