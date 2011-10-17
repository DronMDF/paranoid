
#include <string>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/range/algorithm/min_element.hpp>
#include <boost/regex.hpp>
#include "Line.h"
#include "PreprocessorUncommenter.h"

using namespace std;
using namespace boost;

class LineWrapper : public Line {
public:
	explicit LineWrapper(const Line *line) 
		: line(line), holes()
	{
	}

	virtual const Line *getPointer() const {
		return line;
	}
	virtual unsigned getNumber() const {
		return line->getNumber();
	}
	
	void hide(unsigned spos, unsigned epos);
	virtual string getText() const;
	
private:
	LineWrapper(const LineWrapper &);
	LineWrapper &operator = (const LineWrapper &);

	const Line *line;
	list<pair<unsigned, unsigned>> holes;
};

void LineWrapper::hide(unsigned spos, unsigned epos)
{
	holes.push_back(make_pair(spos, epos));
}

string LineWrapper::getText() const
{
	string text = line->getText();
	BOOST_FOREACH(const auto &hole, holes) {
		text.erase(hole.first, hole.second - hole.first);
	}
	return text;
}


PreprocessorUncommenter::PreprocessorUncommenter(const PreprocessorUncommenter::low_parser_call &parser)
	: ll_parser(parser)
{
}

void PreprocessorUncommenter::parse(const Line *line)
{
	LineWrapper wline(line);
	scanText(&wline, 0);
	ll_parser(&wline, 0, line->getText().size());
}

void PreprocessorUncommenter::selectFirst(LineWrapper *line, unsigned offset, 
					  const action_type &actions)
{
	BOOST_ASSERT(!actions.empty());
	auto nearest = min_element(actions, 
		[&line, &offset](const action_type::value_type &a, 
				 const action_type::value_type &b) -> bool 
		{
			const auto ap = line->getText().find(a.first, offset);
			const auto bp = line->getText().find(b.first, offset);
			return ap < bp; 
		});
	
	const auto pos = line->getText().find(nearest->first, offset);
	if (pos != string::npos) {
		nearest->second(line, offset + pos + nearest->first.size());
	}
}

void PreprocessorUncommenter::scanText(LineWrapper *line, unsigned offset)
{
	action_type actions = {
		{"\\\"", bind(&PreprocessorUncommenter::scanText, this, _1, _2) },
		{"\\/", bind(&PreprocessorUncommenter::scanText, this, _1, _2) },
		{"\"", bind(&PreprocessorUncommenter::scanString, this, _1, _2) },
		{"//", bind(&PreprocessorUncommenter::scanCppComment, this, _1, _2) },
		{"/*", bind(&PreprocessorUncommenter::scanCComment, this, _1, _2) }
	};
	selectFirst(line, offset, actions);
}

void PreprocessorUncommenter::scanString(LineWrapper *line, unsigned offset)
{
	action_type actions = {
		{"\\\"", bind(&PreprocessorUncommenter::scanString, this, _1, _2) },
		{"\"", bind(&PreprocessorUncommenter::scanText, this, _1, _2) },
	};
	selectFirst(line, offset, actions);
}

void PreprocessorUncommenter::scanCppComment(LineWrapper *line, unsigned offset)
{
	line->hide(offset - 2, string::npos);
}

void PreprocessorUncommenter::scanCComment(LineWrapper *line, unsigned offset)
{
	auto end_pos = line->getText().find("*/", offset);
	if (end_pos == string::npos) {
		line->hide(offset - 2, string::npos);
	} else {
		line->hide(offset - 2, end_pos + 2);
		scanText(line, end_pos + 2);
	}
}
