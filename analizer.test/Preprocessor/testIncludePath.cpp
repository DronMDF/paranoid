
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/IncludePath.h>
#include "../Assertions.h"

using namespace std;
using boost::split;
using boost::is_space;
using boost::token_compress_on;


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
	const string argss = "gcc -Wp,-MD,arch/x86/boot/.video-bios.o.d  -nostdinc "
		"-isystem /usr/lib/gcc/i686-pc-linux-gnu/4.5.3/include "
		"-I/home/dron/Store/tmp/linux/arch/x86/include -Iarch/x86/include/generated "
		"-Iinclude  -include /home/dron/Store/tmp/linux/include/linux/kconfig.h "
		"-D__KERNEL__ -I/home/dron/Store/tmp/linux/arch/x86/include "
		"-Iarch/x86/include/generated -Iinclude "
		"-include /home/dron/Store/tmp/linux/include/linux/kconfig.h -g -Os -D_SETUP "
		"-D__KERNEL__ -DDISABLE_BRANCH_PROFILING -Wall -Wstrict-prototypes -march=i386 "
		"-mregparm=3 -include /home/dron/Store/tmp/linux/arch/x86/boot/code16gcc.h "
		"-fno-strict-aliasing -fomit-frame-pointer -ffreestanding -fno-toplevel-reorder "
		"-fno-stack-protector -mpreferred-stack-boundary=2 -m32    -D\"KBUILD_STR(s)=#s\" "
		"-D\"KBUILD_BASENAME=KBUILD_STR(video_bios)\" "
		"-D\"KBUILD_MODNAME=KBUILD_STR(video_bios)\" -c -o arch/x86/boot/video-bios.o "
		"arch/x86/boot/video-bios.c";

	list<string> args;
	split(args, argss, is_space(), token_compress_on);
		
	struct testIncludePath : IncludePath {
		mutable list<string> args;
		testIncludePath(const list<string> &as) : IncludePath(as), args() { }
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
