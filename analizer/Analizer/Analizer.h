
#pragma once
#include <memory>

class File;

class Analizer {
public:
	void operator()(const std::shared_ptr<File> &file) const;
};
