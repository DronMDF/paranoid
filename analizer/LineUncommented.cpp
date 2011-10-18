
#include <boost/foreach.hpp>
#include "LineUncommented.h"

using namespace std;

LineUncommented::LineUncommented(const Line *line)
	: line(line), holes()
{
}

const Line *LineUncommented::getPointer() const 
{
	return line;
}

void LineUncommented::hide(size_type spos, size_type epos)
{
	holes.push_back(make_pair(spos, epos));
}

string LineUncommented::getText() const
{
	string text = line->getText();
	BOOST_FOREACH(const auto &hole, holes) {
		text.erase(hole.first, hole.second - hole.first);
	}
	return text;
}
