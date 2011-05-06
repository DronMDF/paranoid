
#include <iostream>

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

	TargetOptions targetOptions;
	targetOptions.Triple = sys::getHostTriple();
	TargetInfo *pTargetInfo = TargetInfo::CreateTargetInfo(diagnostic, targetOptions);

	FileSystemOptions fileSystemOptions;
	FileManager fileManager(fileSystemOptions);
	SourceManager sourceManager(diagnostic, fileManager);
	HeaderSearch headerSearch(fileManager);
	
	Preprocessor preprocessor(diagnostic, languageOptions, *pTargetInfo,
		sourceManager, headerSearch);

	const FileEntry *pFile = fileManager.getFile(argv[1]);
	sourceManager.createMainFileID(pFile);
	preprocessor.EnterMainSourceFile();
	pTextDiagnosticPrinter->BeginSourceFile(languageOptions, &preprocessor);

	Token token;
	do {
		preprocessor.Lex(token);
		if (diagnostic.hasErrorOccurred()) {
			break;
		}
		preprocessor.DumpToken(token);
		cerr << endl;
	} while (token.isNot(tok::eof));
	pTextDiagnosticPrinter->EndSourceFile();
		
	return 0;
}
