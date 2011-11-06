
#pragma once

struct Location {
	virtual ~Location() {};
	virtual std::string getLocation() const = 0;
};
