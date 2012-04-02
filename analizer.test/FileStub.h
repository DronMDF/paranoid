
#include <boost/foreach.hpp>
#include <Preprocessor/File.h>
#include <Preprocessor/Line.h>
#include <Preprocessor/Token.h>

struct FileStub : public File {
	const std::list<std::string> lines;
	FileStub(const std::string &filename, const std::list<std::string> &lines) 
		: File(filename), lines(lines) 
	{
	}
	void forEachLine(std::function<void (const std::shared_ptr<const Line> &)> lineparser) const {
		unsigned n = 0;
		BOOST_FOREACH(const auto &l, lines) {
			lineparser(std::make_shared<Line>(++n, l, this));
		}
	}
	
	std::list<std::string> getTokensText() const {
		std::list<std::string> texts;
		forEachToken([&texts](const std::shared_ptr<const Token> &t) { texts.push_back(t->getText()); });
		return texts;
	}

	std::list<std::string> getExportedText() const {
		return {};
	}
};