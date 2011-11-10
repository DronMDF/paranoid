
#pragma once

#include <functional>
#include <memory>

class Line;
class Token;

class Tokenizer {
public:
	typedef std::function<void (const std::shared_ptr<const Token> &)> add_token_t;
	
	Tokenizer(add_token_t add_token);
	
	void parse(const std::shared_ptr<const Line> &line);
	
private:
	add_token_t add_token;
};
