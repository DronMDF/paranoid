
#pragma once
#include <functional>
#include <list>
#include <memory>
#include <Preprocessor/File.h>
#include <Preprocessor/Error.h>
#include <Preprocessor/ErrorNote.h>
#include <Preprocessor/ErrorList.h>
#include "ExpressionIfBlock.h"

// TODO: uninline
class AnalyzeIncludeGuard {
private:
	ErrorList *el;
	std::map<std::string, std::shared_ptr<const Token>> guarded;
	bool is_guarded;
	std::list<Error> current;
	
	void checkToken(const std::shared_ptr<const Token> &token) {
		if (isSpace(token) or isEol(token)) {
			return;
		}

		if (auto ifblock = std::dynamic_pointer_cast<const ExpressionIfBlock>(token)) {
			auto guard = ifblock->getIncludeGuardName();
			if (!guard.empty()) {
				if (guarded.count(guard) > 0) {
					current.push_back(Error(token, "Include guard already used"));
					current.push_back(ErrorNote(guarded[guard], "Previously declared here"));
				} else {
					guarded[guard] = token;
				}
				return;
			}
		}
		
		is_guarded = false;
	}
	
	AnalyzeIncludeGuard &operator=(const AnalyzeIncludeGuard&) = delete;
	
public:
	AnalyzeIncludeGuard(ErrorList *el) 
		: el(el), guarded(), is_guarded(true), current()
	{
	}

	AnalyzeIncludeGuard(const AnalyzeIncludeGuard &parent) 
		: el(parent.el), guarded(), is_guarded(true), current()
	{
	}
	
	void operator() (const std::shared_ptr<File> &file) 
	{
		is_guarded = true;
		current.clear();
		
		file->forEachToken(std::bind(&AnalyzeIncludeGuard::checkToken, this, std::placeholders::_1));
		
		if (is_guarded) {
			BOOST_FOREACH(const auto &err, current) {
				el->insert(err);
			}
		}
	}
};

