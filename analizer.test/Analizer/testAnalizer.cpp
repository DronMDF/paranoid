
#include<memory>	// <- Check for optional
#include <boost/test/unit_test.hpp>
#include <Analizer/Analizer.h>
#include <Preprocessor/Error.h>
#include <Preprocessor/TokenInclude.h>
#include <Preprocessor/TokenPredicate.h>
#include "../FileStub.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteAnalizer)

BOOST_AUTO_TEST_CASE(testTransformDefine)
{
	list<string> flines = { "#define a 0" };
	auto file = make_shared<FileStub>("none", flines);
	file->tokenize();
	
	Analizer analizer;
	analizer.transformFile(file);
	
	CUSTOM_EQUAL_FILE_TOKENS_TEXT(*file, { "#define a 0", "\n" });
}

BOOST_AUTO_TEST_SUITE_END()
