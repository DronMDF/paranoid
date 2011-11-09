
#include <functional>
#include <memory>

class Line;
class Token;

class Splitter {
public:
	Splitter(std::function<void (const std::shared_ptr<const Token> &)> add_token);
	
	void parse(const std::shared_ptr<const Line> &line);
	
private:
	std::function<void (const std::shared_ptr<const Token> &)> add_token;
};
