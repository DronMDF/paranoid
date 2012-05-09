
#pragma once
#include <memory>
class File;

template <typename ErrorInsertIterator>
class AnalyzeIncludeGuard {
private:
	ErrorInsertIterator ei;
	std::set<std::string> guarded;
	
	void checkToken(const shared_ptr<const Token> &token) {
		if (auto ifblock = dynamic_pointer_cast<const ExpressionIfBlock>(token)) {
			auto guard = ifblock->getIncludeGuardName();
			if (!guard.empty()) {
				if (guarded.count(guard) > 0) {
					ei++ = Error(token, "Include guard already used");
				}
				guarded.insert(guard);
			}
		}
	}
	
public:
	AnalyzeIncludeGuard(ErrorInsertIterator ei) 
		: ei(ei)
	{
	}
	
	void operator() (const std::shared_ptr<File> &file) 
	{
		file->forEachToken(bind(&AnalyzeIncludeGuard::checkToken, this, _1));
	}
};

