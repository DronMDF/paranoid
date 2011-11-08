
#pragma once

#include <map>
#include <string>
#include <boost/function.hpp>
#include "Tokenizer.h"

class Line;
class LineUncommented;

class PPUncommenter : public PPTokenizer {
public:
	PPUncommenter(const PPUncommenter &) = delete;
	PPUncommenter &operator =(const PPUncommenter &) = delete;
	
	explicit PPUncommenter(PPTokenizer *tokenizer);
	explicit PPUncommenter(std::function<void (const std::shared_ptr<const Line> &)> parser);
	void parse(const std::shared_ptr<const Line> &line);
	
private:
	void scanText(const std::shared_ptr<LineUncommented> &line, unsigned offset);
	void scanString(const std::shared_ptr<LineUncommented> &line, 
			std::string::size_type begin, unsigned pos);
	void scanChar(const std::shared_ptr<LineUncommented> &line, unsigned offset);
	void scanComment(const std::shared_ptr<LineUncommented> &line, unsigned offset);
	void scanCppComment(const std::shared_ptr<LineUncommented> &line, unsigned offset);
	void scanCComment(const std::shared_ptr<LineUncommented> &line, unsigned offset);
	
	std::function<void (const std::shared_ptr<const Line> &)> parser;
	bool in_comment;
};
