
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
