
#include <boost/foreach.hpp>
#include "TokenList.h"

using namespace std;

TokenList::TokenList(const list<shared_ptr<const Token>> &tokens)
	: tokens(tokens)
{
}

string TokenList::getText() const
{
	string text;
	BOOST_FOREACH(const auto token, tokens) {
		text += token->getText();
	}
	return text;
}

string TokenList::getLocation() const
{
	// TODO: Location agregator can accumulate line info from all token
	if (!tokens.empty()) {
		return tokens.front()->getLocation();
	}
	return string();
}

string TokenList::getTextInString(const string &begin_marker, const string &end_marker) const
{
	// TODO: Selection agregator can accumulate string from all token
	if (!tokens.empty()) {
		return tokens.front()->getTextInString(begin_marker, end_marker);
	}
	return string();
}

string TokenList::getFileName() const
{
	// Get filename from first token, this is correct?
	return tokens.empty() ? "unknown" : tokens.front()->getFileName();
}

shared_ptr<const Line> TokenList::getLine() const
{
	return tokens.empty() ? shared_ptr<const Line>() : tokens.front()->getLine();
}

size_t TokenList::getBeginPos() const
{
	return tokens.empty() ? 0 : tokens.front()->getBeginPos();
}

size_t TokenList::getEndPos() const
{
	return tokens.empty() ? 0 : tokens.back()->getBeginPos();
}
