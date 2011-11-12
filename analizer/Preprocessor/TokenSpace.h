
#pragma once
#include "TokenWord.h"

class TokenSpace : public TokenWord {
public:
	TokenSpace(const std::shared_ptr<const Line> &line, 
		  std::string::size_type begin, std::string::size_type end);
	
	virtual std::string getText() const;
};
