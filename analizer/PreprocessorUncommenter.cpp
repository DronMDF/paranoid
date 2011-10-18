
#include <string>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/range/algorithm/min_element.hpp>
#include <boost/regex.hpp>
#include "Line.h"
#include "LineUncommented.h"
#include "PreprocessorUncommenter.h"

using namespace std;
using namespace boost;

PreprocessorUncommenter::PreprocessorUncommenter(const low_parser_call &parser)
	: ll_parser(parser)
{
}

void PreprocessorUncommenter::parse(const Line *line)
{
	LineUncommented wline(line);
	scanText(&wline, 0);
	ll_parser(&wline, 0, line->getText().size());
}

void PreprocessorUncommenter::selectFirst(LineUncommented *line, unsigned offset, 
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

void PreprocessorUncommenter::scanText(LineUncommented *line, unsigned offset)
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

void PreprocessorUncommenter::scanString(LineUncommented *line, unsigned offset)
{
	action_type actions = {
		{"\\\"", bind(&PreprocessorUncommenter::scanString, this, _1, _2) },
		{"\"", bind(&PreprocessorUncommenter::scanText, this, _1, _2) },
	};
	selectFirst(line, offset, actions);
}

void PreprocessorUncommenter::scanCppComment(LineUncommented *line, unsigned offset)
{
	line->hide(offset - 2, string::npos);
}

void PreprocessorUncommenter::scanCComment(LineUncommented *line, unsigned offset)
{
	auto end_pos = line->getText().find("*/", offset);
	if (end_pos == string::npos) {
		line->hide(offset - 2, string::npos);
	} else {
		line->hide(offset - 2, end_pos + 2);
		scanText(line, end_pos + 2);
	}
}
