
#pragma once
#include <list>
#include <memory>

class Token;

class AnalizeInclude {
public:
	void checkToken(const std::shared_ptr<const Token> &token);
	std::list<std::shared_ptr<const Token>> getUnused() const;
};
