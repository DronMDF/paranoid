
#pragma once

#include <map>
#include <string>
#include <boost/function.hpp>
#include "PPTokenizer.h"

//	PPProcessor - декоратор для токенайзера - обрабатывает директивы препроцессора

class Line;
class LineUncommented;

class PPUncommenter : public PPTokenizer {
public:
	PPUncommenter(PPTokenizer *tokenizer);
	void parse(const Line *line);
	
private:
	PPUncommenter(const PPUncommenter &);
	PPUncommenter &operator =(const PPUncommenter &);
	
	typedef std::map<std::string, boost::function<void(LineUncommented *, unsigned)>> action_type;
	
	void selectFirst(LineUncommented *line, unsigned offset, const action_type &actions);
	
	void scanText(LineUncommented *line, unsigned offset);
	void scanString(LineUncommented *line, unsigned offset);
	void scanComment(LineUncommented *line, unsigned offset);
	void scanCppComment(LineUncommented *line, unsigned offset);
	void scanCComment(LineUncommented *line, unsigned offset);
	
	PPTokenizer *tokenizer;
	bool in_comment;
};
