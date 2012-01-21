#pragma once

#include <string>
#include <memory>
#include <Preprocessor/Token.h>

class Line;

struct DummyToken : public Token {
	const std::string text;
	DummyToken(const std::string &text) : text(text) {}
	std::string getText() const { return text; }
	std::string getLocation() const { return ""; }
	std::string getTextInString(const std::string &, const std::string &) const { return ""; }
	std::string getFileName() const { return ""; }
	std::shared_ptr<const Line> getLine() const { return std::shared_ptr<const Line>(); }
	size_t getBeginPos() const { return 0; }
	size_t getEndPos() const { return 0; }
};
