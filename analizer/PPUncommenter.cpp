
#include <string>
#include <boost/algorithm/string/trim.hpp>
#include <boost/format.hpp>
#include "LineUncommented.h"
#include "PPUncommenter.h"

using namespace std;
using namespace boost;

PPUncommenter::PPUncommenter(PPTokenizer *tokenizer)
	: tokenizer(tokenizer), in_comment(false)
{
}

void PPUncommenter::parse(const Line *line)
{
	if (line->getText().empty()) {
		return;
	}
	
	LineUncommented wline(line);
	if (in_comment) {
		scanCComment(&wline, 0);
	} else {
		scanText(&wline, 0);
	}
	
	if (!trim_right_copy(wline.getText()).empty()) {
		tokenizer->parse(&wline);
	}
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
		// TODO: Need to get file name and line number.
		cout << format("'%1%' [%2%]\n\tOpen string") % line->getText() % offset << endl;
		throw runtime_error("Open string");
	}
	
	if (line->getText()[pos] == '\\') {
		scanString(line, pos + 1);
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
	auto sp = (offset >= 2) ? (offset - 2) : 0;
	auto pos = line->getText().find("*/", offset);
	if (pos == string::npos) {
		in_comment = true;
		line->hide(sp, string::npos);
	} else {
		line->hide(sp, pos + 2);
		in_comment = false;
		scanText(line, pos + 2);
	}
}
