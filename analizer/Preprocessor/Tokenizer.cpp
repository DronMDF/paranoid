
#include "Line.h"
#include "Tokenizer.h"
#include "TokenNewline.h"
#include "TokenWord.h"

using namespace std;

Tokenizer::Tokenizer(add_token_t add_token)
	: add_token(add_token)
{
}
	
void Tokenizer::parse(const shared_ptr<const Line> &line)
{
	add_token(shared_ptr<Token>(new TokenWord(line, 0, line->getText().size())));
	add_token(shared_ptr<Token>(new TokenNewline(line)));
}
