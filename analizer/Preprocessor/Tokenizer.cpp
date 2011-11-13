
#include <boost/algorithm/string/classification.hpp>
#include "Line.h"
#include "Tokenizer.h"
#include "TokenNewline.h"
#include "TokenWord.h"
#include "TokenSpace.h"

using namespace std;
using boost::algorithm::is_any_of;

Tokenizer::Tokenizer(add_token_t add_token)
	: add_token(add_token)
{
}
	
void Tokenizer::parse(const shared_ptr<const Line> &line) const
{
	parseRecurse(line, 0, 0);
	add_token(shared_ptr<Token>(new TokenNewline(line)));
}

void Tokenizer::parseRecurse(const shared_ptr<const Line> &line, 
			     string::size_type begin, string::size_type current) const
{
	if (current < line->getText().size()) {
		if (is_any_of(" \t")(line->getText()[current])) {
			parseSpace(line, begin, current + 1);
		} else if (line->getText()[current] == '"') {
			parseString(line, begin, current + 1);
		} else if (line->getText()[current] == '\'') {
			parseString(line, begin, current + 1);
		} else {
			parseWord(line, begin, current + 1);
		}
	}
}

void Tokenizer::parseSpace(const shared_ptr<const Line> &line, 
			   string::size_type begin, string::size_type current) const
{
	if (current < line->getText().size()) {
		if (is_any_of(" \t")(line->getText()[current])) {
			parseSpace(line, begin, current + 1);
			return;
		}
	}
		
	add_token(shared_ptr<Token>(new TokenSpace(line, begin, current)));
	parseRecurse(line, current, current);
	return;
}

void Tokenizer::parseWord(const shared_ptr<const Line> &line, 
			  string::size_type begin, string::size_type current) const
{
	if (current < line->getText().size() && !is_any_of(" \t")(line->getText()[current])) {
		parseWord(line, begin, current + 1);
		return;
	}
		
	add_token(shared_ptr<Token>(new TokenWord(line, begin, current)));
	parseRecurse(line, current, current);
	return;
}

void Tokenizer::parseString(const shared_ptr<const Line> &line, 
			  string::size_type begin, string::size_type current) const
{
	if (current < line->getText().size()) {
		if (line->getText()[current] == '\\') {
			parseString(line, begin, current + 2);
			return;
		}
		
		if (line->getText()[current] != '"') {
			parseString(line, begin, current + 1);
			return;
		}
	}
		
	add_token(shared_ptr<Token>(new TokenWord(line, begin, current + 1)));
	parseRecurse(line, current + 1, current + 1);
	return;
}

void Tokenizer::parseChar(const shared_ptr<const Line> &line, 
			  string::size_type begin, string::size_type current) const
{
	if (current < line->getText().size()) {
		if (line->getText()[current] == '\\') {
			parseChar(line, begin, current + 2);
			return;
		}
		
		if (line->getText()[current] != '\'') {
			parseChar(line, begin, current + 1);
			return;
		}
	}
		
	add_token(shared_ptr<Token>(new TokenWord(line, begin, current + 1)));
	parseRecurse(line, current + 1, current + 1);
	return;
}
