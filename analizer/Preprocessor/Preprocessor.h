
#pragma once

#include <list>
#include <memory>
#include <string>
#include "Token.h"

class File;
class Line;

// Preprocessor is main class for parse raw source
class Preprocessor {
public:
	// TODO: construct with include/sysinclude paths
	explicit Preprocessor(const std::string &filename);
	virtual ~Preprocessor();

protected:
	std::list<std::pair<std::string, std::shared_ptr<File>>> files;
};
