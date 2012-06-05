
#include "AnalizeIncludeGuard.h"

#include <Preprocessor/File.h>
#include <Preprocessor/Error.h>
#include <Preprocessor/ErrorNote.h>
#include <Preprocessor/ErrorList.h>
#include "ExpressionIfBlock.h"

using namespace std;
using namespace std::placeholders;

AnalyzeIncludeGuard::AnalyzeIncludeGuard(ErrorList *el) 
	: el(el), guarded(), is_guarded(true), current()
{
}

AnalyzeIncludeGuard::AnalyzeIncludeGuard(const AnalyzeIncludeGuard &parent) 
	: el(parent.el), guarded(), is_guarded(true), current()
{
}
	
void AnalyzeIncludeGuard::operator() (const shared_ptr<File> &file) 
{
	is_guarded = true;
	current.clear();
	
	file->forEachToken(bind(&AnalyzeIncludeGuard::checkToken, this, _1));
	
	if (is_guarded) {
		BOOST_FOREACH(const auto &err, current) {
			el->insert(err);
		}
	}
}
	
void AnalyzeIncludeGuard::checkToken(const shared_ptr<const Token> &token) 
{
	if (isSpace(token) or isEol(token)) {
		return;
	}

	if (auto ifblock = dynamic_pointer_cast<const ExpressionIfBlock>(token)) {
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

