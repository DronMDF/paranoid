
#include "TokenList.h"

using namespace std;

TokenList::TokenList(const list<shared_ptr<const Token>> &tokens)
{
}

string TokenList::getText() const
{
	return string();
}

string TokenList::getLocation() const
{
	return string();
}

string TokenList::getTextInString(const string &begin_marker, const string &end_marker) const
{
	return string();
}
