
#include "ErrorFormatter.h"
#include "Error.h"
#include "Line.h"
#include "Token.h"

std::string ErrorFormatter(const Error &error)
{
	auto line = error.token->getLine();
	return line->getLocation() + " error: " + error.message + "\n" + line->getText();
}
