
#include <iostream>

#include <boost/foreach.hpp>

#include <llvm/Support/Host.h>
#include <llvm/Support/raw_ostream.h>

#include <clang/Frontend/Utils.h>
#include <clang/Frontend/FrontendOptions.h>
#include <clang/Frontend/DiagnosticOptions.h>
#include <clang/Frontend/PreprocessorOptions.h>
#include <clang/Frontend/HeaderSearchOptions.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Basic/FileManager.h>
#include <clang/Basic/TargetOptions.h>
#include <clang/Basic/FileSystemOptions.h>
#include <clang/Lex/HeaderSearch.h>
#include <clang/Lex/Preprocessor.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/Sema/Sema.h>
#include <clang/Parse/Parser.h>

using namespace std;
using namespace llvm;
using namespace clang;

int main(int argc, char **argv)
{
	DiagnosticOptions diagnosticOptions;
	TextDiagnosticPrinter *pTextDiagnosticPrinter =
		new TextDiagnosticPrinter(outs(), diagnosticOptions);
	IntrusiveRefCntPtr<DiagnosticIDs> pDiagIDs;
	Diagnostic diagnostic(pDiagIDs, pTextDiagnosticPrinter);

	LangOptions languageOptions;
	languageOptions.Bool = 1;
	languageOptions.CPlusPlus = 1;

	TargetOptions targetOptions;
	targetOptions.Triple = sys::getHostTriple();
	TargetInfo *pTargetInfo = TargetInfo::CreateTargetInfo(diagnostic, targetOptions);

	FileSystemOptions fileSystemOptions;
	FileManager fileManager(fileSystemOptions);
	SourceManager sourceManager(diagnostic, fileManager);
	HeaderSearch headerSearch(fileManager);

	Preprocessor preprocessor(diagnostic, languageOptions, *pTargetInfo,
		sourceManager, headerSearch);

	PreprocessorOptions preprocessorOptions;

	HeaderSearchOptions headerSearchOptions;
	headerSearchOptions.UseStandardIncludes = 1;
	headerSearchOptions.UseStandardCXXIncludes = 1;
	
	ApplyHeaderSearchOptions(headerSearch, headerSearchOptions,
		languageOptions, pTargetInfo->getTriple());

	FrontendOptions frontendOptions;
	
	InitializePreprocessor(preprocessor, preprocessorOptions,
		headerSearchOptions, frontendOptions);
		
	const FileEntry *pFile = fileManager.getFile(argv[1]);
	sourceManager.createMainFileID(pFile);
	preprocessor.EnterMainSourceFile();

	IdentifierTable identifierTable(languageOptions);
	SelectorTable selectorTable;
	Builtin::Context builtinContext(*pTargetInfo);
	ASTContext astContext(languageOptions, sourceManager, *pTargetInfo,
		identifierTable, selectorTable, builtinContext, 0);
	ASTConsumer astConsumer;
	Sema sema(preprocessor, astContext, astConsumer);

	Parser parser(preprocessor, sema);
    
	pTextDiagnosticPrinter->BeginSourceFile(languageOptions, &preprocessor);
	parser.ParseTranslationUnit();
	pTextDiagnosticPrinter->EndSourceFile();
	identifierTable.PrintStats();

	return 0;
}
