
#pragma once

#include <memory>

class Line;

/// Интерфейс обработчика строк. Основное предназначение - разделение строки на 
///	символы препроцессора, кроме того к нему будет несколько декораторов.
class PPTokenizer {
public:
	virtual ~PPTokenizer() {}
	virtual void parse(const std::shared_ptr<const Line> &line) = 0;
};
