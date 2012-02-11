
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/range/algorithm/transform.hpp>
#include "TokenInclude.h"
#include "TokenPredicate.h"

using namespace std;
using boost::is_any_of;
using boost::starts_with;
using boost::trim_copy_if;
using boost::join;

TokenInclude::TokenInclude(const list<shared_ptr<const Token>> &tokens)
	: TokenList(tokens)
{
}

void TokenInclude::include(const shared_ptr<const File> &file __attribute__((unused)))
{
}

bool TokenInclude::isSystem() const
{
	if (tokens.empty()) {
		return false;
	}
	
	const string text = tokens.back()->getText();
	return !starts_with(text, "\"");
}

string TokenInclude::getHeaderName() const
{
	if (!tokens.empty()) {
		auto cursor = tokens.begin();
		BOOST_ASSERT((*cursor)->getText() == "#include");
		++cursor;
		while ((*cursor)->getText() == " ") {
			++cursor;
		}

		list<string> text;
		transform(cursor, tokens.end(), back_inserter(text),
			[](const shared_ptr<const Token> &t){ return t->getText(); });
		return trim_copy_if(join(text, ""), is_any_of("\"<>"));
	}

	return "";
}
