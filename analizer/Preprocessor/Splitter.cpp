
#include <string>
#include "Line.h"
#include "Splitter.h"
#include "Token.h"
#include "TokenWord.h"
#include "TokenSpace.h"

using namespace std;

Splitter::Splitter(std::function<void (const std::shared_ptr<const Token> &)> add_token)
	: add_token(add_token)
{
}
	
void Splitter::parse(const std::shared_ptr<const Line> &line)
{
	string text = line->getText();
	
	for (size_t eword = 0;;) {
		size_t sword = text.find_first_not_of(" \t", eword);
		if (sword == string::npos) {
			break;
		}
		
		if (sword > eword) {
			add_token(shared_ptr<const Token>(new TokenSpace));
		}
		
		eword = text.find_first_of(" \t", sword);
		if (eword == string::npos) {
			if (text.size() > sword) {
				add_token(shared_ptr<const Token>(new TokenWord(line, sword, text.size())));
			}
			break;
		}
			
		add_token(shared_ptr<const Token>(new TokenWord(line, sword, eword)));
	}
}
