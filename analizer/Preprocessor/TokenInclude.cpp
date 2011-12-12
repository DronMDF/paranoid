
#include <boost/algorithm/string/predicate.hpp>
#include "TokenInclude.h"

using namespace std;
using boost::starts_with;

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
