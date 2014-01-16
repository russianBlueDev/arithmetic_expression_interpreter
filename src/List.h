/*
    A simple single-linked List
    ===========================

    Example of use:
    ---------------

    // x,y,z are int pointers
    NULL                        // {} empty List
    List* l = cons(z, NULL);    // l = {z}
    l = cons(1, cons(2, l));    // l = {x,y,z}
    size(l);                    // 3
    l = reverse(l)              // l = {z,y,x}
    head(l)                     // x
    tail(l)                     // {y,z}
    delete(l)                   // x,y,z are still allocated

    NB. You should handle carefully deallocation of the List nodes
    by either using free for a single node or 
    delete/deleteFull for a full list.
*/

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct List {
    void* head;
    struct List* tail;
} List;

/*
    Append data in front of list and returns this new list
    Use NULL as empty list
*/
List* cons(void* data, List* list);

/*
    Returns the first element of list
*/
void* head(const List* list);

/*
    Returns the same list without his first element
    Do not forget to free this first element
*/
List* tail(const List* list);

/*
    Compute the number of elements of list
*/
size_t size(const List* list);

/*
    Print the list, applying printFn to print each element
*/
void print(const List* list, void (*print)(const void*));

/*
    Returns list reversed
    It doesn't copy list but modifies it directly so your list
    pointer will now be the end of the List. Therefore you should
    always do as follows:
        list = reverse(list);
*/
List* reverse(List* list);

/*
    Deallocate all nodes of list (but not their data)
*/
void delete(List* list);

/*
    Deallocate all nodes of list and their data using deleteFn
*/
void deleteFull(List* list, void (*deleteFn)(void*));

#endif
