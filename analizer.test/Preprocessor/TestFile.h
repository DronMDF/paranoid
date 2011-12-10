
#include <boost/foreach.hpp>
#include <Preprocessor/File.h>
#include <Preprocessor/Line.h>

struct TestFile : public File {
	const std::list<std::string> lines;
	TestFile(const std::string &filename, const std::list<std::string> &lines) 
		: File(filename), lines(lines) 
	{
	}
	void forEachLine(std::function<void (const std::shared_ptr<const Line> &)> lineparser) const {
		unsigned n = 0;
		BOOST_FOREACH(const auto &l, lines) {
			std::shared_ptr<const Line> line(new Line(++n, l, this));
			lineparser(line);
		}
	}
};