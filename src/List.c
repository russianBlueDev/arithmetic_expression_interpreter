/*
	Implementation file, See header for documentation
*/

#include <stdlib.h>
#include "List.h"

//typedef struct ListNode ListNode;

struct ListNode {
	struct ListNode* next;
	void* data;
};

List* List_new() {
	List* l = malloc(sizeof(List));
	l->head = NULL;
	l->size = 0;
	return l;
}

void List_delete(List** self) {
	while((*self)->size > 0)  {
		List_removeHead(*self);
	}
	free(*self);
	*self = NULL;
}

int List_add(List* self, void* data) {

	struct ListNode* last = NULL;

	// If list is empty
	if(self->head == NULL) {
		self->head = malloc(sizeof(struct ListNode)); 
		last = self->head;
	}

	// else create new ListNode as last element
	else {
		// get the last ListNode
		last = self->head;
		while(last->next != NULL) {
			last = last->next;
		}
		// Create the new element
		last->next = malloc(sizeof(struct ListNode));
		last = last->next;
	}

	// set its data
	last->data = data;
	last->next = NULL;
	self->size++;

	return 0;
}

size_t List_size(List* self) {
	return self->size;
}

void* List_head(List* self) {
	if(self->head)
		return self->head->data;
	else
		return NULL;
}

int List_removeHead(List* self) {
	if(self->head) {
		struct ListNode* toFree = self->head;
		self->head = toFree->next;
		self->size--;
		free(toFree);
	}
	return 0;
}