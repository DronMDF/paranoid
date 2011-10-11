
#pragma once
#include <boost/test/test_tools.hpp>

#define CUSTOM_REQUIRE_EQUAL_COLLECTIONS(A, B) \
	BOOST_REQUIRE_EQUAL_COLLECTIONS((A).begin(), (A).end(), (B).begin(), (B).end());
