
#include <iostream>
#include <string>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/range/algorithm/min_element.hpp>
#include <boost/regex.hpp>
#include "Line.h"
#include "LineUncommented.h"
#include "PPUncommenter.h"

using namespace std;
using namespace boost;

PPUncommenter::PPUncommenter(PPTokenizer *tokenizer)
	: tokenizer(tokenizer)
{
}

void PPUncommenter::parse(const Line *line)
{
	LineUncommented wline(line);
	scanText(&wline, 0);
	tokenizer->parse(&wline);
}

void PPUncommenter::scanText(LineUncommented *line, unsigned offset)
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

void PPUncommenter::scanString(LineUncommented *line, unsigned offset)
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

void PPUncommenter::scanComment(LineUncommented *line, unsigned offset)
{
	const auto pos = line->getText().find_first_of("/*", offset);
	if (pos == string::npos) {
		scanText(line, offset);
	} else if (line->getText()[pos] == '/') {
		scanCppComment(line, pos + 1);
	} else {
		scanCComment(line, pos + 1);
	}
}

void PPUncommenter::scanCppComment(LineUncommented *line, unsigned offset)
{
	line->hide(offset - 2, string::npos);
}

void PPUncommenter::scanCComment(LineUncommented *line, unsigned offset)
{
	auto pos = line->getText().find("*/", offset);
	if (pos == string::npos) {
		line->hide(offset - 2, string::npos);
	} else {
		line->hide(offset - 2, pos + 2);
		scanText(line, pos + 2);
	}
}
