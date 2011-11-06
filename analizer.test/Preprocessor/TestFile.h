
#include <Preprocessor/Location.h>

class TestFile : public Location {
private:
	const std::string location;
public:
	explicit TestFile(const std::string &filename) 
		: location(filename)
	{
	}
	
	virtual std::string getLocation() const
	{
		return location;
	}
};
