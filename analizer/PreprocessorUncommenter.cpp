
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

void PreprocessorUncommenter::scanText(LineUncommented *line, unsigned offset)
{
	const auto pos = line->getText().find_first_of("/\"", offset);
	if (pos != string::npos) {
		if (line->getText()[pos] == '"') {
			scanString(line, pos + 1);
		} else {
			scanComment(line, pos + 1);
		}
	}
}

void PreprocessorUncommenter::scanString(LineUncommented *line, unsigned offset)
{
	const auto pos = line->getText().find_first_of("\\\"", offset);
	if (pos == string::npos) {
		throw logic_error("незакрытая строка");
	}
	
	if (line->getText()[pos] == '\\') {
		scanString(line, offset + 2);
	} else {
		scanText(line, pos + 1);
	}
}

void PreprocessorUncommenter::scanComment(LineUncommented *line, unsigned offset)
{
	const auto pos = line->getText().find_first_of("/*", offset);
	if (pos == string::npos) {
		scanText(line, pos + 1);
	} else if (line->getText()[pos] == '/') {
		scanCppComment(line, pos + 1);
	} else {
		scanCComment(line, pos + 1);
	}
}

void PreprocessorUncommenter::scanCppComment(LineUncommented *line, unsigned offset)
{
	line->hide(offset - 2, string::npos);
}

void PreprocessorUncommenter::scanCComment(LineUncommented *line, unsigned offset)
{
	auto pos = line->getText().find("*/", offset);
	if (pos == string::npos) {
		line->hide(offset - 2, string::npos);
	} else {
		line->hide(offset - 2, pos + 2);
		scanText(line, pos + 2);
	}
}
