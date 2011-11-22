
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
	return string();
}

string TokenList::getTextInString(const string &begin_marker, const string &end_marker) const
{
	return string();
}
