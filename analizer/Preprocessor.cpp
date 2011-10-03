
#include "Preprocessor.h"

using namespace std;

Preprocessor::Preprocessor(const File &file)
	: tokens()
{
}

Preprocessor::const_iterator Preprocessor::begin() const
{
	return tokens.begin();
}

Preprocessor::const_iterator Preprocessor::end() const
{
	return tokens.end();
}
