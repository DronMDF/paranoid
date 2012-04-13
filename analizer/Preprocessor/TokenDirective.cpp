
#include <boost/assert.hpp>
#include "TokenDirective.h"

using namespace std;

TokenDirective::TokenDirective(const list<shared_ptr<Token>> &tokens)
	: TokenList(tokens)
{
	BOOST_ASSERT(tokens.front()->getText() == "#");
	BOOST_ASSERT(tokens.size() >= 2);
}

string TokenDirective::getText() const
{
	return tokens.front()->getText() + tokens.back()->getText();
}
