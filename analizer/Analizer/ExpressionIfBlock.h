
#include "Expression.h"

class ExpressionIfBlock : public Expression {
public:
	ExpressionIfBlock(const std::list<std::shared_ptr<Token>> &tokens);

	virtual std::set<std::string> getUsedNames() const;
	virtual std::set<std::string> getDeclaredNames() const;
	
	std::string getIncludeGuardName() const;
};
