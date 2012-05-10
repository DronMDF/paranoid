
#pragma once
#include <memory>
#include <functional>
#include <Preprocessor/File.h>
#include "ExpressionIfBlock.h"

template <typename ErrorInsertIterator>
class AnalyzeIncludeGuard {
private:
	ErrorInsertIterator ei;
	std::map<std::string, std::shared_ptr<const Token>> guarded;
	
	void checkToken(const std::shared_ptr<const Token> &token) {
		if (auto ifblock = std::dynamic_pointer_cast<const ExpressionIfBlock>(token)) {
			auto guard = ifblock->getIncludeGuardName();
			if (!guard.empty()) {
				if (guarded.count(guard) > 0) {
					ei++ = Error(token, "Include guard already used");
					ei++ = Error(guarded[guard], "Previously declared here");
				}
				guarded[guard] = token;
			}
		}
	}
	
public:
	AnalyzeIncludeGuard(ErrorInsertIterator ei) 
		: ei(ei), guarded()
	{
	}
	
	void operator() (const std::shared_ptr<File> &file) 
	{
		file->forEachToken(std::bind(&AnalyzeIncludeGuard::checkToken, this, std::placeholders::_1));
	}
};

