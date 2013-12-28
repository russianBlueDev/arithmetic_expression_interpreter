/*
	Lexer
*/

#ifndef LEXER_H
#define LEXER_H

#include "List.h"

typedef struct Token Token;

typedef enum { 	Integer,
				Plus, Minus, Times, Divides, 
				LParen, RParen
} TokenType;

struct Token {
	TokenType type;
	void* value;
};

// Return NULL in case of error with a msg
List/*Token*/* Lexer_run(const char* const input, char** const msg);


Token* Token_new(TokenType type, void* value);

void Token_delete(Token* token);

#endif
