
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/Host.h>

#include <clang/Frontend/DiagnosticOptions.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <clang/Basic/FileSystemOptions.h>
#include <clang/Basic/FileManager.h>
#include <clang/Basic/TargetOptions.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Lex/HeaderSearch.h>
#include <clang/Lex/Preprocessor.h>

using namespace llvm;
using namespace clang;

int main(int, char **)
{
	DiagnosticOptions diagnosticOptions;
	TextDiagnosticPrinter *pTextDiagnosticPrinter =
		new TextDiagnosticPrinter(outs(), diagnosticOptions);
	IntrusiveRefCntPtr<DiagnosticIDs> pDiagIDs;
	Diagnostic diagnostic(pDiagIDs, pTextDiagnosticPrinter);

	LangOptions languageOptions;

	TargetOptions targetOptions;
	targetOptions.Triple = sys::getHostTriple();
	TargetInfo *pTargetInfo = TargetInfo::CreateTargetInfo(diagnostic, targetOptions);

	FileSystemOptions fileSystemOptions;
	FileManager fileManager(fileSystemOptions);
	SourceManager sourceManager(diagnostic, fileManager);
	HeaderSearch headerSearch(fileManager);
	
	Preprocessor preprocessor(diagnostic, languageOptions, *pTargetInfo,
		sourceManager, headerSearch);
	
	return 0;
}
