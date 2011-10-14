
#include <string>
#include "Line.h"
#include "PreprocessorUncommenter.h"

using namespace std;

PreprocessorUncommenter::PreprocessorUncommenter(const PreprocessorUncommenter::low_parser_call &parser)
	: ll_parser(parser)
{
}

void PreprocessorUncommenter::parse(const Line *line)
{
	const string text = line->getText();
	const size_t comst = text.find("//");
	if (comst != string::npos) {
		if (comst > 0) {
			ll_parser(line, 0, comst);
		}
	} else {
		ll_parser(line, 0, text.size());
	}
}
