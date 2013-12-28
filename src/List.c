/*
    Implementation file, See header for documentation
*/

#include <stdlib.h>
#include <assert.h>
#include "List.h"
#include "utils.h"

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
    List* l = xmalloc(sizeof(List));
    l->head = NULL;
    l->last = NULL;
    l->size = 0;
    l->modCount = 0;
    return l;
}

void List_delete(List* const self) {
    assert(self);
    while(self->size > 0)  {
        List_removeHead(self);
    }
    free(self);
}

void List_deleteFull(List* self, void (*deleteFunction)(void*)) {
    assert(self); assert(deleteFunction);
    while(self->size > 0) {
        deleteFunction(List_head(self));
        List_removeHead(self);
    }
    free(self);
}

void List_print(List* self, void (*print)(void*)) {
    assert(self); assert(print);
    ListIterator* it = iterator(self);
    while(ListIterator_hasNext(it)) {
        print(ListIterator_next(it));
    }
}

void List_add(List* const self, void* const data) {
    assert(self); assert(data);

    struct ListNode* newLast = NULL;

    // If the list is not empty (i.e. there is a last element)
    if(self->last) {
        self->last->next = xmalloc(sizeof(struct ListNode));
        self->last = self->last->next;
        newLast = self->last;
    }

    // else create new head/last element
    else {
        self->head = xmalloc(sizeof(struct ListNode));
        self->last = self->head;
        newLast = self->head;
    }

    // set its data
    newLast->data = data;
    newLast->next = NULL;
    self->size++;
    self->modCount++;
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
    ListIterator* iter = xmalloc(sizeof(ListIterator));
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
