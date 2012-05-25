
#pragma once
#include <string>
#include <Preprocessor/Line.h>

class LineStub : public Line {
public:
	LineStub(const std::string &text) : Line(0, text, 0) {};
	virtual std::string getText() const { return Line::getText(); };
	virtual std::string getLocation() const { return "test.cxx:10"; };
	virtual std::string getFileName() const { return "test.cxx"; };
};

