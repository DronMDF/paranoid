
#include <algorithm>
#include <boost/foreach.hpp>
#include "TokenList.h"
#include "TokenPredicate.h"

using namespace std;

TokenList::TokenList(const list<token_ptr> &tokens)
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
	return tokens.empty() ? 0 : tokens.back()->getEndPos();
}

void TokenList::replaceToken(const TokenExpression &expression, 
	function<token_ptr (const list<token_ptr> &)> creator)
{
	// Deep replacement in other TokenList
	BOOST_FOREACH(auto &token, tokens) {
		if (auto tokenlist = dynamic_pointer_cast<TokenList>(token)) {
			tokenlist->replaceToken(expression, creator);
		}
	}

	// Cycle as long as all matches will not be replaced
	while(replaceTokenPass(expression, creator)) { 
	}
}

bool TokenList::replaceTokenPass(const TokenExpression &expression, 
	function<token_ptr (const list<token_ptr> &)> creator)
{
	bool is_replaced = false;
	auto begin = tokens.begin();
	while (begin != tokens.end()) {
		auto result = expression.match(begin, tokens.end());
		if (get<0>(result)) {
			const auto end = get<1>(result);
			const list<token_ptr> replaced(begin, end);
			replaceTokens(begin, end, creator(replaced));
			begin = end;
			is_replaced = true;
		} else {
			++begin;
		}
	}
	
	return is_replaced;
}

void TokenList::replaceTokens(list<token_ptr>::iterator begin, 
		list<token_ptr>::iterator end, const token_ptr &token)
{
	tokens.erase(begin, end);
	if (token) {
		tokens.insert(end, token);
	}
}

void TokenList::forEachToken(function<void (const shared_ptr<const Token> &)> func) const
{
	for_each(tokens.begin(), tokens.end(), func);
}
