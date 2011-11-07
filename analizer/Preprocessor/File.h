
#pragma once

#include <list>
#include <memory>
#include <string>
#include "Location.h"

class Line;
class Preprocessor;
class Token;

// One file structure class
class File : public Location {
public:
	File(const Preprocessor *pp, const std::string &filename);
	virtual ~File();
	
	void tokenize();
	// TODO: Command for adding include point
	
	virtual std::string getLocation() const;
	virtual void getTokens(std::function<void (const std::shared_ptr<const Token> &)> add_token) const;
	
private:
	// TODO: Keep the Preprocessor pointer for include callbacks
	const std::string filename;
	std::list<std::shared_ptr<const Token>> tokens;
	
	virtual void forEachLine(std::function<void (const std::shared_ptr<const Line> &)> lineparser) const;
};
