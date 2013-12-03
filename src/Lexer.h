/*
	Lexer
*/

#ifndef LEXER_H
#define LEXER_H

#include <List.h>

typedef struct Token Token;

typedef enum { 	Integer,
				Plus, Minus, Times, Divides, 
				LParen, RParen
} TokenType;

struct Token {
	TokenType type;
	void* value;
};


List* run(const char* input);

#endif