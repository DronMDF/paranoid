
#include <stdexcept>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include "LineUncommented.h"

using namespace std;
using boost::format;

LineUncommented::LineUncommented(const shared_ptr<const Line> &line)
	: line(line), holes()
{
}

const Line *LineUncommented::getPointer() const 
{
	return line.get();
}

void LineUncommented::hide(size_type spos, size_type epos)
{
	if (spos >= line->getText().size()) {
		// TODO: Need to get file name and line number.
		cout << format("'%1%' [%2% - %3%]\n\tInvalid comment") 
			% line->getText() % spos % epos << endl;
		throw runtime_error("Invalid comment");
	}
	holes.push_back(make_pair(spos, epos));
}

string LineUncommented::getText() const
{
	string text = line->getText();
	BOOST_FOREACH(const auto &hole, holes) {
		const size_type length = min(hole.second, text.size()) - hole.first;
		text.replace(hole.first, length, length, ' ');
	}
	return text;
}

string LineUncommented::getLocation() const
{
	return string();
}

