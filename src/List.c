#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

List* cons(void* data, List* list) {
    List* new = malloc(sizeof(List));
    new->tail = list;
    new->head = data;
    return new;
}

void* head(const List* list) {
    return list->head;
}

List* tail(const List* list) {
    return list->tail;
}

size_t size(const List* list) {
    size_t size = 0;
    while(list != NULL) {
        size++;
        list = list->tail;
    }
    return size;
}

void print(const List* list, void (*printFn)(const void*)) {
    printf("{");
    for(const List* l = list; l != NULL; l = l->tail) {
        printFn(l->head);
        printf(", ");
    }
    printf("}\n");
}

List* reverse(List* list) {
    if(list == NULL || list->tail == NULL)
        return list;
    List* next = list->tail;
    List* reversedTail = reverse(list->tail);
    next->tail = list;
    list->tail = NULL;
    return reversedTail;
}

void delete(List* list) {
    if(list == NULL) return;
    delete(list->tail);
    free(list);
}

void deleteFull(List* list, void (*deleteFn)(void*)) {
    if(list == NULL) return;
    deleteFull(list->tail, deleteFn);
    deleteFn(list->head);
    free(list);
}
