
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
	typedef std::list<std::shared_ptr<const Line>> lines_type;
	typedef lines_type::const_iterator const_iterator;

	File(const Preprocessor *pp, const std::string &filename);
	explicit File(std::istream &in);
	
	virtual ~File() { };

	void tokenize();
	// TODO: Command for adding include point
	
	virtual std::string getLocation() const;
	
	// TODO: Need to be replaced by visitor interface
	const_iterator begin() const;
	const_iterator end() const;
	
	virtual void getTokens(std::function<void (const std::shared_ptr<const Token> &)> add_token) const;
	
private:
	const std::string filename;
	std::list<std::shared_ptr<const Token>> tokens;
	
	virtual void forEachLine(std::function<void (const std::shared_ptr<const Line> &)> lineparser) const;
	
	// TODO: Keep the Preprocessor pointer for include callbacks
	// TODO: Keep the preprocessed token list only by this file (not by included)
	lines_type lines;
};
