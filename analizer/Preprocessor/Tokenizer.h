
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
	
	void parseRecurse(const std::shared_ptr<const Line> &line, size_type begin, size_type current) const;
	void parseSpace(const std::shared_ptr<const Line> &line, size_type begin, size_type current) const;
	void parseWord(const std::shared_ptr<const Line> &line, size_type begin, size_type current) const; 
	void parseString(const std::shared_ptr<const Line> &line, size_type begin, size_type current) const;
	void parseChar(const std::shared_ptr<const Line> &line, size_type begin, size_type current) const;

	add_token_t add_token;
};
