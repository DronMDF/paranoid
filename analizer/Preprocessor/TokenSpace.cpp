
#include "TokenSpace.h"

using namespace std;

string TokenSpace::getText() const
{
	return " ";
}

string TokenSpace::getLocation() const
{
	return string();
}

string TokenSpace::getTextInString(const string &begin_marker __attribute__((unused)), 
				   const string &end_marker __attribute__((unused))) const
{
	return string();
}
