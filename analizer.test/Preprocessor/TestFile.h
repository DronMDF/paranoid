
#include <Preprocessor/File.h>

class TestFile : public File {
private:
	const std::string location;
public:
	explicit TestFile(const std::string &filename) 
		: location(filename)
	{
	}
	
	std::string getLocation() const
	{
		return location;
	}
};
