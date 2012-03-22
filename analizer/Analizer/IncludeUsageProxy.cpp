
#include "IncludeUsageProxy.h"

using namespace std;

IncludeUsageProxy::IncludeUsageProxy(const shared_ptr<const TokenInclude> &token)
	: token(token)
{
}

bool IncludeUsageProxy::unused() const
{
	return true;
}
	
shared_ptr<const TokenInclude> IncludeUsageProxy::getToken() const
{
	return token;
}
