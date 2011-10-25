
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
	rout << "in file " << path.front().first;
	if (path.front().second != 0) {
		rout << ':' << path.front().second;
	}
	
	return rout.str();
}

void Locator::setFileName(const string &name)
{
	path.push_back(make_pair(name, 0));
}

void Locator::setLineNumber(unsigned number)
{
	if (path.empty()) {
		path.push_back(make_pair("<unknown>", number));
	} else {
		path.back().second = number;
	}
}
