
#pragma once

#include <functional>
#include <list>
#include <memory>

class Line;
class Token;

class Tokenizer {
public:
	typedef std::function<void (const std::shared_ptr<Token> &)> add_token_t;
	
	Tokenizer(add_token_t add_token);
	virtual ~Tokenizer();
	
	void parse(const std::shared_ptr<const Line> &line);
	
private:
	typedef std::string::size_type size_type;
	
	size_type parseSpace(const std::shared_ptr<const Line> &line, size_type begin) const;
	size_type parseCComment(const std::shared_ptr<const Line> &line, size_type begin);
	size_type parseWord(const std::shared_ptr<const Line> &line, size_type begin) const; 
	size_type parseNumber(const std::shared_ptr<const Line> &line, size_type begin) const;
	size_type parseString(const std::shared_ptr<const Line> &line, size_type begin);
	size_type parseChar(const std::shared_ptr<const Line> &line, size_type begin) const;

	add_token_t add_token;
	bool in_ccomment;
	std::list<std::shared_ptr<Token>> string_tokens;
};
