/*
    Test suite for Lexer
*/

#include <assert.h>
#include "List.h"
#include "Lexer.h"


void badInputTest(char* msg) {
    assert(Lexer_run("#", &msg) == NULL);
}

void emptyInputTest(char* msg) {
    List* l = Lexer_run("", &msg);
    assert(l);
    assert(List_size(l) == 0);
    List_delete(&l);
}

void largeNumberTest(char* msg) {
    assert(Lexer_run("999999999999999999", &msg) == NULL);
}


int main(void) {
    char* msg = NULL;
    emptyInputTest(msg);
    //badInputTest(msg);
    //largeNumberTest(msg);
    return 0;
}