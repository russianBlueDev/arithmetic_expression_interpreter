/*
	Implementation file, See header for documentation
*/

#include <stdlib.h>
#include <List.h>

//typedef struct ListNode ListNode;

struct ListNode {
	struct ListNode* next;
	void* data;
};

List* List_new() {
	List* l = malloc(sizeof(List));
	l->head = NULL;
	l->last = NULL;
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

	struct ListNode* newLast = NULL;

	// If the list is not empty (i.e. there is a last element)
	if(self->last) {
		self->last->next = malloc(sizeof(struct ListNode));
		self->last = self->last->next;
		newLast = self->last;
	}

	// else create new head/last element
	else {
		self->head = malloc(sizeof(struct ListNode));
		self->last = self->head;
		newLast = self->head;
	}

	// set its data
	newLast->data = data;
	newLast->next = NULL;
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

		if(List_size(self) == 0) {
			self->last = NULL;
		}
	}
	return 0;
}