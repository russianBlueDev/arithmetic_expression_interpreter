/*
	Lexer implementation
*/

#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include "Lexer.h"

bool isNum(const char c);
int chartoInt(const char c);
void errorMessage(const char* const input, const size_t indexError,
                  const char* const error, char** const msg);

List/*Token*/* Lexer_run(const char* const input, char** const msg)
{
    assert(input); assert(msg);
    List* listOfTokens = List_new();

    size_t index = 0;
    Token* token = NULL;
    while(input[index] != '\0') {

        token = malloc(sizeof(Token));
        List_add(listOfTokens, token);

        if(!token) {
            // Allocate new string for msg
            //strcpy(*msg, "Lexer Error: Allocation of token failed");
            // Use iterator to first free the tokens and then delete the list
            List_delete(&listOfTokens);
            return NULL;
        }
        token->value = NULL;


        // Integer constant
        if(isNum(input[index])) {
            int num = chartoInt(input[index]);
            index++;
            while(isNum(input[index])) {
                if(INT_MAX/10 <= num) { // overflow
                    //strcpy(*msg, "Lexer Error: Number is too large");
                    errorMessage(input, index, "Lexer error: Number is too large.", msg);
                    List_delete(&listOfTokens);
                    return NULL;
                }
                num = num*10 + chartoInt(input[index]);
                index++;

            }

            token->type = Integer;
            token->value = malloc(sizeof(int));
            *((int*)(token->value)) = num;
        } 

        // Punctuation
        else if(input[index] == '+') {
            token->type = Plus;
        } else if(input[index] == '-') {
            token->type = Minus;
        } else if(input[index] == '*') {
            token->type = Times;
        } else if(input[index] == '/') {
            token->type = Divides;
        } else if(input[index] == '(') {
            token->type = LParen;
        } else if(input[index] == ')') {
            token->type = RParen;
        }

        // Unknown character
        else {
            //strcpy(*msg, "Lexer Error: Unknown character");
            List_delete(&listOfTokens);
            return NULL;
        }
    }

    return listOfTokens;
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
    *msg = calloc(strlen(error) + 2*(strlen(input)) + 3, sizeof(char));
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

