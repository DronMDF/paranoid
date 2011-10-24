
#include <sstream>
#include "Locator.h"

using namespace std;

Locator::Locator()
	: path()
{
}

string Locator::toString() const
{
	if (path.empty()) {
		return string();
	}
	
	ostringstream rout;
	rout << "in file " << path.front().first << ':' << path.front().second;
	return rout.str();
}

void Locator::setLineNumber(unsigned number)
{
	if (path.empty()) {
		path.push_back(make_pair("<unknown>", number));
	} else {
		path.back().second = number;
	}
}
