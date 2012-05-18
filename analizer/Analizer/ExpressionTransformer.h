
#pragma once
#include <memory>

class File;

class ExpressionTransformer {
public:
	void operator()(const std::shared_ptr<File> &) const;
};

