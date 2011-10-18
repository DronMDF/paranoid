
#pragma once

#include <map>
#include <string>
#include <boost/function.hpp>

// TODO: Основной интерфейс - PPTokenizer
//	PPTokenizerImpl - Основная реализация, делит чистый си поток на токены
//	PPProcessor - декоратор для токенайзера - обрабатывает директивы препроцессора
//	PPUncommenter - вырезает все комментарии.

// Токенайзер с декораторами комбинируется в препроцессоре и прокачивают 
//	чере себя поток в виде последовательности абстрактных строк (Line)

// Сейчас я что-то наворотил

class Line;
class LineUncommented;

class PreprocessorUncommenter {
public:
	typedef boost::function<void(const Line *, unsigned, unsigned)> low_parser_call;
	
	PreprocessorUncommenter(const low_parser_call &parser);
	void parse(const Line *line);
	
private:
	typedef std::map<std::string, boost::function<void(LineUncommented *, unsigned)>> action_type;
	
	void selectFirst(LineUncommented *line, unsigned offset, const action_type &actions);
	
	void scanText(LineUncommented *line, unsigned offset);
	void scanString(LineUncommented *line, unsigned offset);
	void scanCppComment(LineUncommented *line, unsigned offset);
	void scanCComment(LineUncommented *line, unsigned offset);
	
	low_parser_call ll_parser;
};
