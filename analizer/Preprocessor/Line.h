
#pragma once

#include <string>
#include "Location.h"

struct Line : public Location {
	virtual ~Line() {};
	virtual std::string getText() const = 0;
};
