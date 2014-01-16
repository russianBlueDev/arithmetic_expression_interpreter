/*
    Test suite for Lexer
*/

#include <assert.h>
#include "List.h"
#include "Lexer.h"


void badInputTest(char* msg) {
    assert(Lexer_run("#", &msg) == NULL);
    assert(Lexer_run("+#", &msg) == NULL);
    assert(Lexer_run("122+#2132", &msg) == NULL);
    assert(Lexer_run("+#+++", &msg) == NULL);
    assert(Lexer_run("+----------------------------------------------------#", &msg) == NULL);
}

void emptyInputTest(char* msg) {
    List* l = Lexer_run("", &msg);
    assert(l);
    assert(size(l) == 0);
    delete(l);
}

void largeNumberTest(char* msg) {
    assert(Lexer_run("999999999999999999", &msg) == NULL);
}

void goodInputTest(char* msg) {
    List* l = NULL;
    l = Lexer_run("12+34*382-2681129/26178", &msg);
    assert(l != NULL);
    delete(l);
    l = Lexer_run("(12+34) * 26781", &msg);
    assert(l != NULL);
    delete(l); 
    
}


int main(void) {
    char* msg = NULL;
    //emptyInputTest(msg);
    //badInputTest(msg);
    //largeNumberTest(msg);
    //goodInputTest(msg);
    return 0;
}
