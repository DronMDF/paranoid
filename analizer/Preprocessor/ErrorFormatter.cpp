
#include "ErrorFormatter.h"
#include "Error.h"

std::string ErrorFormatter(const Error &error)
{
	return error.what();
}
