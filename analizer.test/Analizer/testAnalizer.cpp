
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
	
	BOOST_REQUIRE_EQUAL(file->getTokensText().front(), "#define a 0");
}

BOOST_AUTO_TEST_SUITE_END()
