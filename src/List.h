/*
	Simple Linked List for generic data
*/

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct List List;
typedef struct ListIterator ListIterator;

struct List {
	struct ListNode* head;
	struct ListNode* last;
	size_t size;
	size_t modCount;
};

struct ListIterator {
	struct List* list;
	struct ListNode* next;
	size_t modCount;
};


// List methods
List* List_new(void);

void List_delete(List** self);

int List_add(List* self, void* data);

size_t List_size(List* self);

void* List_head(List* self);

int List_removeHead(List* self);

ListIterator* iterator(List* self);

// ListIterator method
bool ListIterator_hasNext(ListIterator* self, bool* hasNext);

bool ListIterator_next(ListIterator* self, void** data);

#endif