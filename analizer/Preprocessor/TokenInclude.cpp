
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/trim.hpp>
#include "TokenInclude.h"

using namespace std;
using boost::is_any_of;
using boost::starts_with;
using boost::trim_copy_if;

TokenInclude::TokenInclude(const list<shared_ptr<const Token>> &tokens)
	: TokenList(tokens)
{
}

void TokenInclude::include(const shared_ptr<const File> &file)
{
}

bool TokenInclude::isSystem() const
{
	if (tokens.empty()) {
		return false;
	}
	
	const string text = tokens.back()->getText();
	return starts_with(text, "<");
}

string TokenInclude::getHeaderName() const
{
	if (!tokens.empty()) {
		const string text = tokens.back()->getText();
		if (starts_with(text, "<")) {
			return trim_copy_if(text, is_any_of("<>"));
		}
		
		if (starts_with(text, "\"")) {
			return trim_copy_if(text, is_any_of("\""));
		}
	}

	return "";
}
