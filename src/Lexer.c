/*
	Lexer implementation
*/

#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include "Lexer.h"
#include "utils.h"


bool isNum(const char c);
int chartoInt(const char c);
void errorMessage(const char* const input, const size_t indexError,
                  const char* const error, char** const msg);

List/*Token*/* Lexer_run(const char* const input, char** const msg)
{
    assert(input); assert(msg);
    List* listOfTokens = List_new();

    size_t index = 0;
    
    while(input[index] != '\0') {

        if(input[index] == ' ') {
            index++;
            continue;
        }

        TokenType tokenType = 0;
        void* tokenValue = NULL;

        // Integer constant
        if(isNum(input[index])) {
            int num = chartoInt(input[index]);
            index++;
            while(isNum(input[index])) {
                if(INT_MAX/10 <= num) { // overflow
                    //strcpy(*msg, "Lexer Error: Number is too large");
                    //errorMessage(input, index, "Lexer error: Number is too large.", msg);
                    while(List_size(listOfTokens) > 0) {
                        Token_delete(List_head(listOfTokens));
                        List_removeHead(listOfTokens);
                    }
                    List_delete(listOfTokens);
                    return NULL;
                }
                num = num*10 + chartoInt(input[index]);
                index++;

            }

            tokenType = Integer;
            tokenValue = xmalloc(sizeof(int));
        } 

        // Punctuation
        else if(input[index] == '+') {
            tokenType = Plus;
            index++;
        } else if(input[index] == '-') {
            tokenType = Minus;
            index++;
        } else if(input[index] == '*') {
            tokenType = Times;
            index++;
        } else if(input[index] == '/') {
            tokenType = Divides;
            index++;
        } else if(input[index] == '(') {
            tokenType = LParen;
            index++;
        } else if(input[index] == ')') {
            tokenType = RParen;
            index++;
        }

        // Unknown character
        else {
            //strcpy(*msg, "Lexer Error: Unknown character");
            while(List_size(listOfTokens) > 0) {
                Token_delete(List_head(listOfTokens));
                List_removeHead(listOfTokens);
            }
            List_delete(listOfTokens);
            return NULL;
        }

        List_add(listOfTokens, Token_new(tokenType, tokenValue));
    }

    return listOfTokens;
}

Token* Token_new(TokenType type, void* value) {
    Token *token = xmalloc(sizeof(Token));
    token->type = type;
    token->value = value;
    return token; 
}

void Token_delete(Token* token) {
    if(token->value != NULL) {
        free(token->value);
    }
    free(token);
}

bool isNum(const char c) {
    return c > 47 && c < 58;
}

int chartoInt(const char c) {
    return (int) (c - 48);
}

void errorMessage(const char* const input, const size_t indexError,
                  const char* const error, char** const msg) {
    // error\ninput\ninput\0
    *msg = xcalloc(strlen(error) + 2*(strlen(input)) + 3, sizeof(char));
    // TODO handle msg == NULL
    int index = 0;
    strcpy(*msg, error);
    index += strlen(error);
    (*msg)[index] = '\n';
    index += 1;
    strcpy((*msg + index), input);
    index += strlen(input);
    (*msg)[index] = '\n';
    index += 1;
    for(size_t i = 0; i < indexError; i++) {
        (*msg)[index] = '~';
        index++;
    }
    (*msg)[index] = '^';
    index++;
    for(size_t i = indexError+1; i < strlen(input); i++) {
        (*msg)[index] = '~';
        index++;
    }
}

