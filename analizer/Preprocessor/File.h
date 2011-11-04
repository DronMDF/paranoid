
#pragma once

#include <iosfwd>
#include <list>
#include <memory>

class Line;

// One file structure class
class File {
public:
	typedef std::list<std::shared_ptr<const Line>> lines_type;
	typedef lines_type::const_iterator const_iterator;

	// TODO: get the Preprocessor pointer and filename
	explicit File(std::istream &in);
	File() : lines() { }
	
	virtual ~File() { };

	// TODO: Command for tokenizing
	// TODO: Command for adding include point
	
	// TODO: Pull to Location interface
	virtual std::string getLocation() const;
	
	// TODO: Need to be replaced by visitor interface
	const_iterator begin() const;
	const_iterator end() const;
	
private:
	// TODO: Keep the Preprocessor pointer for include callbacks
	// TODO: Keep the preprocessed token list only by this file (not by included)
	lines_type lines;
};
