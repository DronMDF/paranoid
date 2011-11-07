
#pragma once

#include <iosfwd>
#include <list>
#include <memory>
#include "Location.h"
#include "Token.h"

class Line;
class Preprocessor;
class Token;

// One file structure class
class File : public Location {
public:
	typedef std::list<std::shared_ptr<const Line>> lines_type __attribute__((deprecated));
	typedef lines_type::const_iterator const_iterator __attribute__((deprecated));

	File(const Preprocessor *pp, const std::string &filename);
	explicit File(std::istream &in) __attribute__((deprecated));
	virtual ~File();
	
	void tokenize();
	// TODO: Command for adding include point
	
	virtual std::string getLocation() const;
	
	// TODO: Need to be replaced by visitor interface
	const_iterator begin() const __attribute__((deprecated));
	const_iterator end() const __attribute__((deprecated));
	
	virtual void getTokens(std::function<void (const std::shared_ptr<const Token> &)> add_token) const;
	
private:
	// TODO: Keep the Preprocessor pointer for include callbacks
	const std::string filename;
	std::list<std::shared_ptr<const Token>> tokens;
	
	virtual void forEachLine(std::function<void (const std::shared_ptr<const Line> &)> lineparser) const;
	
	lines_type lines __attribute__((deprecated));
};
