
#include <boost/algorithm/string/classification.hpp>
#include "Line.h"
#include "Tokenizer.h"
#include "TokenNewline.h"
#include "TokenWord.h"
#include "TokenSpace.h"
#include "Error.h"

using namespace std;
using boost::algorithm::is_any_of;

Tokenizer::Tokenizer(add_token_t add_token)
	: add_token(add_token)
{
}
	
void Tokenizer::parse(const shared_ptr<const Line> &line) const
{
	parseRecurse(line);
	add_token(shared_ptr<Token>(new TokenNewline(line)));
}

void Tokenizer::parseRecurse(const shared_ptr<const Line> &line) const
{
	for (size_type position = 0; position != string::npos && position < line->getText().size(); ) {
		if (is_any_of(" \t")(line->getText()[position])) {
			position = parseSpace(line, position);
		} else if (line->getText()[position] == '"') {
			position = parseString(line, position);
		} else if (line->getText()[position] == '\'') {
			position = parseChar(line, position);
		} else {
			position = parseWord(line, position);
		}
	}
}

Tokenizer::size_type Tokenizer::parseSpace(const shared_ptr<const Line> &line, size_type begin) const
{
	const size_type end = line->getText().find_first_not_of(" \t", begin);
	add_token(shared_ptr<Token>(new TokenSpace(line, begin, end)));
	return end;
}

Tokenizer::size_type Tokenizer::parseWord(const shared_ptr<const Line> &line, size_type begin) const
{
	const size_type end = line->getText().find_first_of(" \t", begin);
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
	size_type end = begin + 1;
	while(true) {
		end = line->getText().find_first_of("\\'", end);
		if (end == string::npos) {
			throw Error(*line, begin, string::npos, "Open quote");
		}
	
		if (line->getText()[end] == '\'') {
			break;
		}
		
		end += 2;
	}

	end += 1;
	add_token(shared_ptr<Token>(new TokenWord(line, begin, end)));
	return end;
}
