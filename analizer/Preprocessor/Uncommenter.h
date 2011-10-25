
#pragma once

#include <map>
#include <string>
#include <boost/function.hpp>
#include "Tokenizer.h"

class Line;
class LineUncommented;

class PPUncommenter : public PPTokenizer {
public:
	PPUncommenter(PPTokenizer *tokenizer);
	void parse(const std::shared_ptr<const Line> &line);
	
private:
	PPUncommenter(const PPUncommenter &);
	PPUncommenter &operator =(const PPUncommenter &);
	
	void scanText(const std::shared_ptr<LineUncommented> &line, unsigned offset);
	void scanString(const std::shared_ptr<LineUncommented> &line, unsigned offset);
	void scanChar(const std::shared_ptr<LineUncommented> &line, unsigned offset);
	void scanComment(const std::shared_ptr<LineUncommented> &line, unsigned offset);
	void scanCppComment(const std::shared_ptr<LineUncommented> &line, unsigned offset);
	void scanCComment(const std::shared_ptr<LineUncommented> &line, unsigned offset);
	
	PPTokenizer *tokenizer;
	bool in_comment;
};
