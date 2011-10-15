
#pragma once

#include <boost/function.hpp>

class Line;

class PreprocessorUncommenter {
public:
	typedef boost::function<void(const Line *, unsigned, unsigned)> low_parser_call;
	
	PreprocessorUncommenter(const low_parser_call &parser);
	void parse(const Line *line) const;
	
private:
	void scanComments(const Line *line, unsigned offset) const;
	
	low_parser_call ll_parser;
};
