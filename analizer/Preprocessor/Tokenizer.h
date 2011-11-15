
#pragma once

#include <functional>
#include <memory>

class Line;
class Token;

class Tokenizer {
public:
	typedef std::function<void (const std::shared_ptr<const Token> &)> add_token_t;
	
	Tokenizer(add_token_t add_token);
	
	void parse(const std::shared_ptr<const Line> &line) const;
	
private:
	typedef std::string::size_type size_type;
	
	void parseRecurse(const std::shared_ptr<const Line> &line) const;
	size_type parseSpace(const std::shared_ptr<const Line> &line, size_type begin) const;
	size_type parseWord(const std::shared_ptr<const Line> &line, size_type begin) const; 
	size_type parseString(const std::shared_ptr<const Line> &line, size_type begin) const;
	size_type parseChar(const std::shared_ptr<const Line> &line, size_type begin) const;

	add_token_t add_token;
};
