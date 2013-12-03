/*
    Implementation file, See header for documentation
*/

#include <stdlib.h>
#include <assert.h>
#include "List.h"

struct ListNode {
    struct ListNode* next;
    void* data;        
};

struct _List {
    struct ListNode* head;
    struct ListNode* last;
    size_t size;
    size_t modCount;
};

struct _ListIterator {
    const List* list;
    struct ListNode* next;
    size_t modCount;
};


List* List_new(void) {
    List* l = malloc(sizeof(List));
    if(l) {
        l->head = NULL;
        l->last = NULL;
        l->size = 0;
        l->modCount = 0;
    }
    return l;
}

void List_delete(List** const self) {
    assert(self); assert(*self);
    while((*self)->size > 0)  {
        List_removeHead(*self);
    }
    free(*self);
    *self = NULL;
}

ListErrorCode List_add(List* const self, void* const data) {
    assert(self); assert(data);

    struct ListNode* newLast = NULL;

    // If the list is not empty (i.e. there is a last element)
    if(self->last) {
        self->last->next = malloc(sizeof(struct ListNode));
        if(self->last->next == NULL) {
            return LIST_ADD_FAILURE;
        }
        self->last = self->last->next;
        newLast = self->last;
    }

    // else create new head/last element
    else {
        self->head = malloc(sizeof(struct ListNode));
        if(self->head == NULL) {
            return LIST_ADD_FAILURE;
        }
        self->last = self->head;
        newLast = self->head;
    }

    // set its data
    newLast->data = data;
    newLast->next = NULL;
    self->size++;
    self->modCount++;

    return LIST_ADD_SUCCESS;
}

size_t List_size(const List* const self) {
    assert(self);
    return self->size;
}

void* List_head(const List* const self) {
    assert(self);
    if(self->head)
        return self->head->data;
    else
        return NULL;
}

void List_removeHead(List* const self) {
    assert(self);
    if(self->head) {
        struct ListNode* toFree = self->head;
        self->head = toFree->next;
        self->size--;
        self->modCount--;
        free(toFree);

        if(List_size(self) == 0) {
            self->last = NULL;
        }
    }
}

ListIterator* iterator(const List* const self) {
    assert(self);
    ListIterator* iter = malloc(sizeof(ListIterator));
    iter->list = self;
    iter->next = self->head;
    iter->modCount = self->modCount;
    return iter;
}

bool ListIterator_safeHasNext(const ListIterator* const self, bool* const hasNext) {
    assert(self);
    assert(hasNext);
    if(self->modCount != self->list->modCount) {
        return false;
    } else {
        *hasNext = self->next != NULL;
        return true;
    }
}

bool ListIterator_safeNext(ListIterator* const self, void** const data) {
    assert(self);
    assert(data);
    bool hasNext = false;
    bool modified = !ListIterator_safeHasNext(self, &hasNext);
    if(modified) {
        return false;
    } else {
        assert(hasNext);
        *data = self->next->data;
        self->next = self->next->next;
        return true;
    }
}

bool ListIterator_hasNext(const ListIterator* const self) {
    bool hasNext = false;
    assert(ListIterator_safeHasNext(self, &hasNext));
    return hasNext;
}

void* ListIterator_next(ListIterator* const self) {
    void* data = NULL;
    assert(ListIterator_hasNext(self));
    assert(ListIterator_safeNext(self, &data));
    return data;
}
