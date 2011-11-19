
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "Line.h"
#include "Tokenizer.h"
#include "TokenNewline.h"
#include "TokenWord.h"
#include "TokenSpace.h"
#include "Error.h"

using namespace std;
using boost::algorithm::iequals;
using boost::algorithm::is_any_of;
using boost::algorithm::is_from_range;

Tokenizer::Tokenizer(add_token_t add_token)
	: add_token(add_token)
{
}
	
void Tokenizer::parse(const shared_ptr<const Line> &line) const
{
	for (size_type position = 0; position != string::npos && position < line->getText().size(); ) {
		if (is_any_of(" \t\v\r\f")(line->getText()[position])) {
			position = parseSpace(line, position);
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
	
	add_token(shared_ptr<Token>(new TokenNewline(line)));
}

Tokenizer::size_type Tokenizer::parseSpace(const shared_ptr<const Line> &line, size_type begin) const
{
	const size_type end = line->getText().find_first_not_of(" \t\v\r\f", begin);
	add_token(shared_ptr<Token>(new TokenSpace(line, begin, end)));
	return end;
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

Tokenizer::size_type Tokenizer::parseString(const shared_ptr<const Line> &line, size_type begin) const
{
	size_type end = begin + 1;
	
	while(true) {
		end = line->getText().find_first_of("\\\"", end);
		if (end == string::npos) {
			// TODO: handle Multiline string
			throw Error(*line, begin, string::npos, "Open quote");
		}
		
		if (line->getText()[end] == '"') {
			break;
		}
		
		end += 2;
	}
	
	end += 1;
	add_token(shared_ptr<Token>(new TokenWord(line, begin, end)));
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
