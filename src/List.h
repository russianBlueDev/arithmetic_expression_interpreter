/*
	Simple Linked List for generic data
*/

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct _List List;
typedef struct _ListIterator ListIterator;

// List methods
List* List_new(void);

void List_delete(List** self);

int List_add(List* self, void* data);

size_t List_size(List* self);

void* List_head(List* self);

int List_removeHead(List* self);

ListIterator* iterator(List* self);

// ListIterator method
bool ListIterator_safeHasNext(ListIterator* self, bool* hasNext);

bool ListIterator_safeNext(ListIterator* self, void** data);

bool ListIterator_hasNext(ListIterator* self);

void* ListIterator_next(ListIterator* self);

#endif