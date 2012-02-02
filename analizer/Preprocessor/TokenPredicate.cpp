
#include "TokenPredicate.h"

using namespace std;

TokenPredicate::TokenPredicate(const char *text)
{
}

TokenPredicate::~TokenPredicate() = default;

bool TokenPredicate::operator()(const shared_ptr<Token> &token) const
{
	return true;
}
