/*
	Simple Linked List for generic data
*/

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct List List;

struct List {
	struct ListNode* head;
	struct ListNode* last;
	size_t size;
};

List* List_new();

void List_delete(List** self);

int List_add(List* self, void* data);

size_t List_size(List* self);

void* List_head(List* self);

int List_removeHead(List* self);

#endif