
#include <string>
#include "Line.h"
#include "PreprocessorUncommenter.h"

using namespace std;

PreprocessorUncommenter::PreprocessorUncommenter(const PreprocessorUncommenter::low_parser_call &parser)
	: ll_parser(parser)
{
}

unsigned PreprocessorUncommenter::getQuoteLenght(const string &quote) const
{
	unsigned qpos = quote.find('"');
	unsigned qchar = quote.find("\\\"");
	while (qchar + 1 == qpos) {
		qpos = quote.find('"', qpos + 1);
		qchar = quote.find("\\\"", qpos + 1);
	}
	return qpos + 1;
}

void PreprocessorUncommenter::parse(const Line *line)
{
	const string text = line->getText();
	unsigned start = 0;
	for (unsigned i = 0; i < text.size(); ) {
		if (text[i] == '"') {
			i += getQuoteLenght(string(text, i));
			continue;
		}
		
		if (string(text, i, 2) == "//") {
			ll_parser(line, start, i - start);
			return;
		}
		
		i++;
	}
	
	ll_parser(line, start, text.size() - start);
}
