
#pragma once
#include <string>
#include <memory>
#include <Preprocessor/Token.h>
#include "LineStub.h"

struct TokenStub : public Token {
	const std::string text;
	TokenStub(const std::string &text) : text(text) {}
	std::string getText() const { return text; }
	std::string getLocation() const { return ""; }
	std::string getFileName() const { return ""; }
	std::shared_ptr<const Line> getLine() const { 
		return std::make_shared<LineStub>(text); 
	}
	size_t getBeginPos() const { return 0; }
	size_t getEndPos() const { return text.size(); }
};
