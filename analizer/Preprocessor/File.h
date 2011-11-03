
#pragma once

#include <iosfwd>
#include <list>
#include <memory>

class Line;

class File {
public:
	typedef std::list<std::shared_ptr<const Line>> lines_type;
	typedef lines_type::const_iterator const_iterator;

	explicit File(std::istream &in);
	File() : lines() { }
	
	virtual ~File() { };

	virtual std::string getLocation() const;
	
	const_iterator begin() const;
	const_iterator end() const;
	
private:
	lines_type lines;
};
