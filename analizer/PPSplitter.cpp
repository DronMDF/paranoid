
#include <string>
#include "Line.h"
#include "PPSplitter.h"
#include "Token.h"

using namespace std;

PPSplitter::PPSplitter(std::function<void (Token)> add_token)
	: add_token(add_token)
{
}
	
void PPSplitter::parse(const Line *line)
{
	string text = line->getText();
	
	for (size_t eword = 0;;) {
		size_t sword = text.find_first_not_of(" \t", eword);
		if (sword == string::npos) {
			break;
		}
		
		if (sword > eword) {
			add_token(Token());
		}
		
		eword = text.find_first_of(" \t", sword);
		if (eword == string::npos) {
			if (text.size() > sword) {
				add_token(Token(line->getPointer(), sword, text.size() - sword));
			}
			break;
		}
			
		add_token(Token(line->getPointer(), sword, eword - sword));
	}
}
