
#include <boost/foreach.hpp>
#include "TokenList.h"
#include "TokenPredicate.h"

using namespace std;

TokenList::TokenList(const list<shared_ptr<Token>> &tokens)
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

void TokenList::replaceToken(TokenExpression expression, 
	function<shared_ptr<Token> (const list<shared_ptr<Token>> &)> creator)
{
	BOOST_FOREACH(auto &token, tokens) {
		if (auto tokenlist = dynamic_pointer_cast<TokenList>(token)) {
			tokenlist->replaceToken(expression, creator);
		}
	}

	auto lookup = tokens.begin();
	while (lookup != tokens.end()) {
		expression.reset();
		
		auto begin = lookup;
		while (begin != tokens.end()) {
			if (expression.match(*begin)) {
				break;
			}
			++begin;
		}
		
		if (begin == tokens.end()) {
			return;
		}

		auto end = begin;
		++end;
		
		if (expression.isMatched()) {
			const list<shared_ptr<Token>> replaced(begin, end);
			replaceTokens(begin, end, creator(replaced));
			lookup = end;
			continue;
		}
		
		while (end != tokens.end()) {
			if (expression.match(*end)) {
				++end;
				continue;
			}
			
			if (expression.isMatched()) {
				const list<shared_ptr<Token>> replaced(begin, end);
				replaceTokens(begin, end, creator(replaced));
				lookup = end;
			} else {
				lookup = ++begin;
			}
			break;
		}
	}
}

void TokenList::replaceTokens(list<shared_ptr<Token>>::iterator begin, 
		list<shared_ptr<Token>>::iterator end, const shared_ptr<Token> &token)
{
	tokens.erase(begin, end);
	if (token) {
		tokens.insert(end, token);
	}
}
