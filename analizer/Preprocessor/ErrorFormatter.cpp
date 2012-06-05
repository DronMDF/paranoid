
#include <boost/algorithm/string/classification.hpp>
#include <boost/range/algorithm/replace_copy_if.hpp>
#include "ErrorFormatter.h"
#include "Error.h"
#include "Line.h"
#include "Token.h"

using namespace std;
using boost::is_space;
using boost::replace_copy_if;

std::string ErrorFormatter(const Error &error)
{
	auto line = error.token->getLine();
	auto linetext = line->getText();
	string tokenmask;
	replace_copy_if(linetext, back_inserter(tokenmask), !is_space(), ' ');
	auto len = error.token->getEndPos() - error.token->getBeginPos();
	tokenmask.replace(error.token->getBeginPos(), len, len, '~');
	return line->getLocation() + " " + error.type + ": " 
		+ error.message + "\n" + linetext + '\n' + tokenmask;
}
