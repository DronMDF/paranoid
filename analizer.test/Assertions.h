
#pragma once
#include <boost/test/test_tools.hpp>

template<typename A, typename B>
void CUSTOM_REQUIRE_EQUAL_COLLECTIONS(const A &a, const B &b)
{
	BOOST_REQUIRE_EQUAL_COLLECTIONS(a.begin(), a.end(), b.begin(), b.end());
}

// Initializer list is not deduced by default
template<typename A, typename B>
void CUSTOM_REQUIRE_EQUAL_COLLECTIONS(const A &a, const std::initializer_list<B> &b)
{
	BOOST_REQUIRE_EQUAL_COLLECTIONS(a.begin(), a.end(), b.begin(), b.end());
}
