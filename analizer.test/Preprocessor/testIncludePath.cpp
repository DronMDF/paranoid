
#include <boost/test/unit_test.hpp>
#include <Preprocessor/IncludePath.h>
#include "../Assertions.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteIncludePath)

BOOST_AUTO_TEST_CASE(testParseVerbose)
{
	struct testIncludePath : IncludePath {
		const list<string> lines;
		testIncludePath(const list<string> &lines) : IncludePath({}), lines(lines) { }
		// TODO: Suspend invoking compiler
		virtual list<string> readSpec() const { return lines; }
	};
	
	// lines produced by gcc: 'echo | gcc -v -E -'
	testIncludePath tip({
		"#include \"...\" search starts here:",
		"#include <...> search starts here:",
		" /usr/include",
		"End of search list." });
	
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tip.getQuotedPath(), list<string>());
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tip.getSystemPath(), { "/usr/include" });
}

BOOST_AUTO_TEST_CASE(testFilterArgs)
{
	// Linux kernel args
	const list<string> args = {"gcc", "-Wp,-MD,mm/.truncate.o.d", "-nostdinc",  "-isystem",
		"/usr/lib/gcc/i686-pc-linux-gnu/4.5.3/include", 
		"-I/home/dron/Store/tmp/linux/arch/x86/include",
		"-Iarch/x86/include/generated", "-Iinclude", "-include",
		"/home/dron/Store/tmp/linux/include/linux/kconfig.h", "-D__KERNEL__", "-Wall",
		"-Wundef", "-Wstrict-prototypes", "-Wno-trigraphs", "-fno-strict-aliasing", 
		"-fno-common", "-Werror-implicit-function-declaration", "-Wno-format-security", 
		"-fno-delete-null-pointer-checks", "-O2", "-m32", "-msoft-float", "-mregparm=3",
		"-freg-struct-return", "-mpreferred-stack-boundary=2", "-march=i686", 
		"-Wa,-mtune=generic32", "-ffreestanding", "-DCONFIG_AS_CFI=1", 
		"-DCONFIG_AS_CFI_SIGNAL_FRAME=1", "-DCONFIG_AS_CFI_SECTIONS=1", "-pipe", 
		"-Wno-sign-compare", "-fno-asynchronous-unwind-tables", "-mno-sse", "-mno-mmx", 
		"-mno-sse2", "-mno-3dnow", "-Wframe-larger-than=1024", "-fno-stack-protector", 
		"-fomit-frame-pointer", "-Wdeclaration-after-statement", "-Wno-pointer-sign", 
		"-fno-strict-overflow", "-fconserve-stack", "-DCC_HAVE_ASM_GOTO", "-DKBUILD_STR(s)=#s",
		"-DKBUILD_BASENAME=KBUILD_STR(truncate)", "-DKBUILD_MODNAME=KBUILD_STR(truncate)", 
		"-c", "-o", "mm/truncate.o", "mm/truncate.c"};

	struct testIncludePath : IncludePath {
		mutable list<string> args;
		testIncludePath(const list<string> &args) : IncludePath(args), args() { }
		virtual list<string> readSpec(const list<string> &a) const {
			args = a;
			return {};
		}
	} tip(args);
	
	const list<string> expected = { "gcc", "-nostdinc",  "-isystem",
		"/usr/lib/gcc/i686-pc-linux-gnu/4.5.3/include", 
		"-I/home/dron/Store/tmp/linux/arch/x86/include",
		"-Iarch/x86/include/generated", "-Iinclude", "-x", "c"};
	
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tip.args, expected);
}

BOOST_AUTO_TEST_SUITE_END()
