
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "Error.h"
#include "Line.h"
#include "Tokenizer.h"
#include "TokenList.h"
#include "TokenNewline.h"
#include "TokenSpace.h"
#include "TokenWord.h"

using namespace std;
using boost::algorithm::iequals;
using boost::algorithm::is_any_of;
using boost::algorithm::is_from_range;
using boost::algorithm::starts_with;

Tokenizer::Tokenizer(add_token_t add_token)
	: add_token(add_token), in_ccomment(false), string_tokens()
{
}

Tokenizer::~Tokenizer()
{
	if (!string_tokens.empty()) {
		Error error(*(string_tokens.front()), "Open quote");
		cerr << error.what() << endl;
	}
}

void Tokenizer::parse(const shared_ptr<const Line> &line)
{	
	size_type position = 0;
	if (!string_tokens.empty()) {
		position = parseString(line, position);
	}
	
	if (position != string::npos && in_ccomment) {
		position = parseCComment(line, position);
	}
	
	for (; position != string::npos && position < line->getText().size(); ) {
		if (is_any_of(" \t\v\r\f")(line->getText()[position])) {
			position = parseSpace(line, position);
		} else if (starts_with(string(line->getText(), position), "/*")) {
			position = parseCComment(line, position);
		} else if (starts_with(string(line->getText(), position), "//")) {
			add_token(shared_ptr<Token>(new TokenSpace(line, position, string::npos)));
			break;
		} else if (is_any_of("{}[]#()<>%:;.?*+-/^&|∼!=,\\")(line->getText()[position])) {
			add_token(shared_ptr<Token>(new TokenWord(line, position, position + 1)));
			position++;
		} else if (is_from_range('0', '9')(line->getText()[position])) {
			position = parseNumber(line, position);
		} else if (line->getText()[position] == '"') {
			position = parseString(line, position);
		} else if (line->getText()[position] == '\'') {
			position = parseChar(line, position);
		} else {
			position = parseWord(line, position);
		}
	}
	
	if (string_tokens.empty()) {
		add_token(shared_ptr<Token>(new TokenNewline(line)));
	} else {
		string_tokens.push_back(shared_ptr<Token>(new TokenNewline(line)));
	}
}

Tokenizer::size_type Tokenizer::parseSpace(const shared_ptr<const Line> &line, size_type begin) const
{
	const size_type end = line->getText().find_first_not_of(" \t\v\r\f", begin);
	add_token(shared_ptr<Token>(new TokenSpace(line, begin, end)));
	return end;
}

Tokenizer::size_type Tokenizer::parseCComment(const shared_ptr<const Line> &line, size_type begin)
{
	const size_type end = line->getText().find("*/", begin);
	in_ccomment = (end == string::npos);
	if (in_ccomment) {
		add_token(shared_ptr<Token>(new TokenSpace(line, begin, string::npos)));
		return string::npos;
	}
	
	add_token(shared_ptr<Token>(new TokenSpace(line, begin, end + 2)));
	return end + 2;
}

Tokenizer::size_type Tokenizer::parseWord(const shared_ptr<const Line> &line, size_type begin) const
{
	const size_type end = line->getText().find_first_of(" \t\v\r\f{}[]#()<>%:;.?*+-/^&|∼!=,\\\"’", begin);
	add_token(shared_ptr<Token>(new TokenWord(line, begin, end)));
	return end;
}

Tokenizer::size_type Tokenizer::parseNumber(const std::shared_ptr<const Line> &line, size_type begin) const
{
	size_type end = string::npos;
	if (line->getText()[begin] != '0') {
		// decimal
		end = line->getText().find_first_not_of("0123456789", begin);
	} else if (iequals(string(line->getText(), begin, 2), "0x")) {
		// hex
		end = line->getText().find_first_not_of("0123456789abcdefABCDEF", begin + 2);
	} else {
		// octal
		end = line->getText().find_first_not_of("01234567", begin);
	}
	
	add_token(shared_ptr<Token>(new TokenWord(line, begin, end)));
	return end;
}

Tokenizer::size_type Tokenizer::parseString(const shared_ptr<const Line> &line, size_type begin)
{
	size_type end = begin;
	if (string_tokens.empty()) {
		end++;	// skip the lead double quote char
	}
	
	while(true) {
		end = line->getText().find_first_of("\\\"", end);
		if (end == string::npos) {
			string_tokens.push_back(shared_ptr<Token>(new TokenWord(line, begin, end)));
			return end;
		}
		
		if (line->getText()[end] == '"') {
			break;
		}
		
		end += 2;
	}
	
	end += 1;
	shared_ptr<Token> token(new TokenWord(line, begin, end));
	
	if (string_tokens.empty()) {
		add_token(token);
	} else {
		string_tokens.push_back(token);
		add_token(shared_ptr<Token>(new TokenList(string_tokens)));
		string_tokens.clear();
	}
	
	return end;
}

Tokenizer::size_type Tokenizer::parseChar(const shared_ptr<const Line> &line, size_type begin) const
{
	// Character literal is not a string. Only one char or escape sequence
	// TODO: Parse escape sequence
	if (line->getText()[begin + 1] == '\\' && line->getText()[begin + 3] == '\'') {
		add_token(shared_ptr<Token>(new TokenWord(line, begin, begin + 4)));
		return begin + 4;
	}
	
	if (line->getText()[begin + 2] == '\'') {
		add_token(shared_ptr<Token>(new TokenWord(line, begin, begin + 3)));
		return begin + 3;
	}
	
	// Parse single quote as a symbol
	add_token(shared_ptr<Token>(new TokenWord(line, begin, begin + 1)));
	return begin + 1;
}
