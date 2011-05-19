
#include <boost/scoped_ptr.hpp>

#include <llvm/Support/Host.h>
#include <llvm/Support/ManagedStatic.h>

#include <clang/Basic/TargetInfo.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>

using namespace std;
using namespace boost;
using namespace llvm;
using namespace clang;

int main(int argc, char **argv)
{
	CompilerInstance compiler;
	compiler.createDiagnostics(argc, argv);
	//compiler.createFileManager();
	//compiler.createSourceManager(compiler.getFileManager());
	compiler.getTargetOpts().Triple = sys::getHostTriple();
	compiler.setTarget(TargetInfo::CreateTargetInfo(
		compiler.getDiagnostics(), compiler.getTargetOpts()));

	compiler.getLangOpts().CPlusPlus = 1;
	compiler.getLangOpts().Bool = 1;
	
	pair<InputKind, string> input(IK_CXX, "saffer.cpp");
	compiler.getFrontendOpts().Inputs.push_back(input);
	compiler.getFrontendOpts().OutputFile = "saffer.xml";

	compiler.getPreprocessorOpts().addMacroDef("__STDC_LIMIT_MACROS");
	compiler.getPreprocessorOpts().addMacroDef("__STDC_CONSTANT_MACROS");
	
	compiler.getHeaderSearchOpts().AddPath("/usr/lib/clang/2.9/include/",
		frontend::System, false, false, false);
	compiler.getHeaderSearchOpts().Verbose = 1;

	//compiler.createPreprocessor();
	//compiler.createASTContext();

	ASTDumpAction action;
	compiler.ExecuteAction(action);

	llvm_shutdown();
	return 0;
}
