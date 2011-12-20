
#pragma once
#include <vector>

class IncludeLocator {
public:
	explicit IncludeLocator(const std::vector<const char *> &args);
	virtual ~IncludeLocator();
};
