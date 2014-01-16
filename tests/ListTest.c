/*
    Test suite for List
*/

#include <List.h>
#include <assert.h>
#include <stdio.h>

void printInt(const void* n) {
    //printf("%d", *((int*)n));
}

int main(void) {
    int* zero = malloc(sizeof(int));
    *zero = 0;
    int* one = malloc(sizeof(int));
    *one = 1;
    int* two = malloc(sizeof(int));
    *two = 2;
    int* three = malloc(sizeof(int));
    *three = 3;

    List* k = cons(zero, cons(one, cons(two, cons(three, NULL))));
    print(k, printInt);
    List* l = k->tail;
    print(l, printInt);
    assert(size(l) == 3);
    assert(l->head == one);
    assert(l->tail->head == two);
    assert(l->tail->tail->head == three);
    assert(l->tail->tail->tail == NULL);
    l = reverse(l);
    print(l, printInt);
    deleteFull(l, free);
    free(k->head);
    free(k);
    return 0;
}