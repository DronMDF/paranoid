
#pragma once

class Line;

/// Интерфейс обработчика строк. Основное предназначение - разделение строки на 
///	символы препроцессора, кроме того к нему будет несколько декораторов.
class PPTokenizer {
public:
	virtual ~PPTokenizer() {}
	virtual void parse(const Line *line) = 0;
	
};
