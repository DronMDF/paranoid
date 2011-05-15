
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
	compiler.getTargetOpts().Triple = sys::getHostTriple();
	compiler.createDiagnostics(argc, argv);
	compiler.createFileManager();
	compiler.createSourceManager(compiler.getFileManager());
	compiler.setTarget(TargetInfo::CreateTargetInfo(
		compiler.getDiagnostics(), compiler.getTargetOpts()));
	compiler.createPreprocessor();
	//compiler.createASTContext();
	
	DumpTokensAction action/*(compiler, argv[1])*/;
	compiler.ExecuteAction(action);

	llvm_shutdown();
	return 0;
}
