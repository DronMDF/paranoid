
#pragma once
#include <memory>
#include <string>
#include "Error.h"

class Token;

class ErrorNote : public Error {
public:
	ErrorNote(const std::shared_ptr<const Token> &token, const std::string &message);
};

