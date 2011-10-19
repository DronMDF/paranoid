
#include <functional>
#include "PPTokenizer.h"

class Line;
class Token;

class PPSplitter : public PPTokenizer {
public:
	PPSplitter(std::function<void (Token)> add_token);
	
	virtual void parse(const Line *line);
	
private:
	std::function<void (Token)> add_token;
};
