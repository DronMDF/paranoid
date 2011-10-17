
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
class LineWrapper;

class PreprocessorUncommenter {
public:
	typedef boost::function<void(const Line *, unsigned, unsigned)> low_parser_call;
	
	PreprocessorUncommenter(const low_parser_call &parser);
	void parse(const Line *line);
	
private:
	typedef std::map<std::string, boost::function<void(LineWrapper *, unsigned)>> action_type;
	
	void selectFirst(LineWrapper *line, unsigned offset, const action_type &actions);
	
	void scanText(LineWrapper *line, unsigned offset);
	void scanString(LineWrapper *line, unsigned offset);
	void scanCppComment(LineWrapper *line, unsigned offset);
	void scanCComment(LineWrapper *line, unsigned offset);
	
	low_parser_call ll_parser;
};
