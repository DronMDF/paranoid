
#include <functional>
#include "Tokenizer.h"

class Line;
class Token;

class PPSplitter {
public:
	PPSplitter(std::function<void (Token)> add_token);
	
	void parse(const std::shared_ptr<const Line> &line);
	
private:
	std::function<void (Token)> add_token;
};
