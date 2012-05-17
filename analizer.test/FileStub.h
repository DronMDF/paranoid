
#include <boost/foreach.hpp>
#include <Preprocessor/File.h>
#include <Preprocessor/Line.h>
#include <Preprocessor/Token.h>
#include "Assertions.h"

struct FileStub : public File {
	const std::list<std::string> lines;
	FileStub(const std::string &filename, const std::list<std::string> &lines) 
		: File(filename), lines(lines) 
	{
	}
	
	FileStub(const std::list<std::shared_ptr<Token>> &tokens) 
		: File("test"), lines()
	{
		this->tokens.insert(this->tokens.end(), tokens.begin(), tokens.end());
	}
	
	void forEachLine(std::function<void (const std::shared_ptr<const Line> &)> lineparser) const {
		unsigned n = 0;
		BOOST_FOREACH(const auto &l, lines) {
			lineparser(std::make_shared<Line>(++n, l, this));
		}
	}
	
	std::list<std::string> getExportedText() const {
		return {};
	}
};

static inline
void CUSTOM_EQUAL_FILE_TOKENS_TEXT(const File &file, const std::list<std::string> &expected)
{
	std::list<std::string> actual;
	file.forEachToken([&actual](const std::shared_ptr<const Token> &t) {
		actual.push_back(t->getText());
	});
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(actual, expected);
}
