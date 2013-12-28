/*
    Test suite for List
*/

#include <stdlib.h>
#include <assert.h>
#include "List.h"

// TestArray is an pointer to function taking a list and returning void
typedef void (*TestArray)(List*);

void headOfEmptyList(List* l) {
    assert(List_head(l) == NULL);
}

void sizeOfEmptyList(List* l) {
    assert(List_size(l) == 0);
}

void addOnEmptyList(List* l) {
    int* x = malloc(sizeof(int));
    *x = 5;
    List_add(l, x);
    assert(List_head(l) == x);
    assert( *((int*)List_head(l)) == 5);
    free(x);
}

void removeOnEmptyList(List* l) {
    List_removeHead(l);
    List_removeHead(l);
    assert(List_size(l) == 0);
}

void addAndRemove(List* l) {
    int* x = malloc(sizeof(int));
    *x = 5;
    int* y = malloc(sizeof(int));
    *y = 2;
    int* z = malloc(sizeof(int));
    *z = 3;

    List_add(l, x);
    assert(List_head(l) == x);
    assert(List_size(l) == 1);
    List_add(l, y);
    assert(List_head(l) == x);
    assert(List_size(l) == 2);
    List_add(l, z);
    assert(List_head(l) == x);
    assert(List_size(l) == 3);
    List_removeHead(l);
    assert(List_head(l) == y);
    assert(List_size(l) == 2);
    List_removeHead(l);
    assert(List_head(l) == z);
    assert(List_size(l) == 1);
    List_removeHead(l);
    assert(List_head(l) == NULL);
    assert(List_size(l) == 0);
    List_add(l, x);
    assert(List_head(l) == x);
    assert(List_size(l) == 1);
    List_add(l, y);
    assert(List_head(l) == x);
    assert(List_size(l) == 2);
    List_removeHead(l);
    assert(List_head(l) == y);
    assert(List_size(l) == 1);
    List_removeHead(l);
    assert(List_head(l) == NULL);
    assert(List_size(l) == 0);

    free(x);
    free(y);
    free(z);
}

void listIterator(List* l) {
    int* x = malloc(sizeof(int));
    *x = 1;
    int* y = malloc(sizeof(int));
    *y = 2;
    int* z = malloc(sizeof(int));
    *z = 3;

    List_add(l, x);
    List_add(l, y);
    List_add(l, z);

    ListIterator* iter = iterator(l);
    int i = 1;
    void* data = NULL;
    while(ListIterator_hasNext(iter)) {
        data = ListIterator_next(iter);
        assert( *((int*)(data)) == i);
        i++;
    }

    free(iter);
    iter = NULL;

    List_removeHead(l);
    List_removeHead(l);
    List_removeHead(l);

    free(x);
    free(y);
    free(z);
}

void listIteratorFailWhileModify(List* l) {
    int* x = malloc(sizeof(int));
    *x = 1;
    List_add(l, x);
    ListIterator* iter = iterator(l);
    bool hasNext = false;
    void* data = NULL;
    while(ListIterator_safeHasNext(iter, &hasNext), hasNext) {
        List_removeHead(l);
        assert(!ListIterator_safeNext(iter, &data)); // should fail here
        break;
    }
    free(iter);
    iter = NULL;
    List_removeHead(l);
    free(x);
}

void listIteratorFailWhileModify2(List* l) {
    int* x = malloc(sizeof(int));
    *x = 1;
    List_add(l, x);
    List_add(l, x);
    ListIterator* iter = iterator(l);
    bool hasNext = false;
    void* data = NULL;
    int i = 1;
    while(ListIterator_safeHasNext(iter, &hasNext), hasNext) { // should fail here on second iteration
        if(i == 2) { 
            List_add(l, x); 
            assert(!ListIterator_safeNext(iter, &data));
            break;
        }
        assert(ListIterator_safeNext(iter, &data));
        i++;
    }
    free(iter);
    iter = NULL;
    List_removeHead(l);
    free(x);
}

void listIteratorFailWhileModify3(List* l) {
    int* x = malloc(sizeof(int));
    *x = 1;
    List_add(l, x);
    ListIterator* iter = iterator(l);
    bool hasNext = false;
    void* data = NULL;
    while(ListIterator_safeHasNext(iter, &hasNext), hasNext) { // should fail here on second iteration
        ListIterator_safeNext(iter, &data);
        List_removeHead(l);
        assert(!ListIterator_safeHasNext(iter, &hasNext));
        break;
    }
    free(iter);
    iter = NULL;
    List_removeHead(l);
    free(x);
}

void newListTest(List* l) {
    assert(l);
    assert(List_head(l) == NULL);
    assert(List_size(l) == 0);
}

int main(void) {

    const size_t TEST_COUNT = 10;

    TestArray* tests = calloc(TEST_COUNT, sizeof(TestArray));
    tests[0] = headOfEmptyList;
    tests[1] = sizeOfEmptyList;
    tests[2] = addOnEmptyList;
    tests[3] = removeOnEmptyList;
    tests[4] = addAndRemove;
    tests[5] = listIterator;
    tests[6] = listIteratorFailWhileModify;
    tests[7] = listIteratorFailWhileModify2;
    tests[8] = listIteratorFailWhileModify3;
    tests[9] = newListTest;

    for(size_t i = 0; i < TEST_COUNT; i++) {
        // Setup the test
        List* l = List_new();
        // Launch the test
        tests[i](l);
        // tear down the test
        List_delete(l);
        l = NULL;
    }

    free(tests);
    return 0;
}
