
#include <list>
#include <Preprocessor/File.h>
#include <Preprocessor/TokenPredicate.h>
#include "ExpressionDefine.h"
#include "ExpressionIfBlock.h"
#include "ExpressionIfDirective.h"
#include "ExpressionTransformer.h"

using namespace std;

void ExpressionTransformer::operator()(const shared_ptr<File> &file) const
{
	typedef const list<shared_ptr<Token>> tokenlist;
	
	file->replaceToken({"#define", Some(Not(isEol))},
		[](tokenlist &t){ return make_shared<ExpressionDefine>(t); });
	
	file->replaceToken({"#if", Some(Not(isEol))},
		[](tokenlist &t){ return make_shared<ExpressionIfDirective>(t); });
	file->replaceToken({"#ifdef", Some(Not(isEol))},
		[](tokenlist &t){ return make_shared<ExpressionIfDirective>(t); });
	file->replaceToken({"#ifndef", Some(Not(isEol))},
		[](tokenlist &t){ return make_shared<ExpressionIfDirective>(t); });
	// TODO: elseif is Expression
	// TODO: endl and space collapse
	file->replaceToken({ isType<ExpressionIfDirective>(),
			Optional(Some(Not(Or(isType<ExpressionIfDirective>(), "#endif")))), "#endif"},
		[](tokenlist &t){ return make_shared<ExpressionIfBlock>(t); });
}

