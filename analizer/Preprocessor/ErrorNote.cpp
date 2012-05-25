
#include "ErrorNote.h"

using namespace std;

ErrorNote::ErrorNote(const shared_ptr<const Token> &token, const string &message)
	: Error(token, message, "note")
{
}

