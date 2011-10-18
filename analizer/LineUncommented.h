
#include <list>
#include "Line.h"

class LineUncommented : public Line {
public:
	typedef std::string::size_type size_type;
	
	explicit LineUncommented(const Line *line);

	virtual const Line *getPointer() const;
	virtual std::string getText() const;

	void hide(size_type spos, size_type epos);
	
private:
	LineUncommented(const LineUncommented &);
	LineUncommented &operator = (const LineUncommented &);
	
	const Line *line;
	std::list<std::pair<size_type, size_type>> holes;
};
