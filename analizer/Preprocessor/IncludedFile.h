
#pragma once 

class IncludedFile {
public:
	virtual ~IncludedFile() {};
	
	virtual void forEachToken(
		std::function<void (const std::shared_ptr<const Token> &)> func) const = 0;
};

