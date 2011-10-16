
#include <string>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/regex.hpp>
#include "Line.h"
#include "PreprocessorUncommenter.h"

using namespace std;
using namespace boost;

// Чтобы не разбираться с тем, новая строка или страя - надо хранить состояние отдельно,
// А объект создавать для каждой строки заново. Состояние может быть статическим.

PreprocessorUncommenter::PreprocessorUncommenter(const PreprocessorUncommenter::low_parser_call &parser)
	: ll_parser(parser)
{
}

void PreprocessorUncommenter::parse(const Line *line) const
{
	scanComments(line, 0);
}

void PreprocessorUncommenter::scanComments(const Line *line, unsigned offset) const
{
	const string text = string(line->getText(), offset);
	const regex re("[^\\\\](\".*[^\\\\]\"|//|/\\*.*?\\*/)");
	smatch what;
	if (regex_search(text, what, re)) {
		if (what.str(1) == "//") {
			ll_parser(line, 0, offset + what.position(1));
		} else if (starts_with(what.str(1), "/*")) {
			// Для начала просто поделим на два.
			ll_parser(line, 0, offset + what.position(1));
			ll_parser(line, offset + what.position(1) + what.length(1), 
				  text.size() - (offset + what.position(1) + what.length(1)));
		} else {
			scanComments(line, offset + what.position(1) + what.length(1));
		}
		return;
	}
	
	ll_parser(line, 0, line->getText().size());
}

