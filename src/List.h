/*
    \file List.h
    \brief Simple Linked List for generic data

    A simple linked list interface for generic data
*/

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdbool.h>


typedef struct _List List;

typedef struct _ListIterator ListIterator;


/**
*   \brief Creates a new List
*   \return a new empty List
*/
List* List_new(void);

/**
*   \brief Delete a new List and set pointer to NULL
*   \param self List to delete (pass by reference to set it to NULL)
*/
void List_delete(List* const self);

void List_deleteFull(List* self, void (*deleteFunction)(void*));

void List_print(List* self, void (*print)(void*));

/**
    \brief Adds a new element at the end of the list
    \param self the list
    \param data the element to add
    \return LIST_ADD_SUCCESS if element was added, LIST_ADD_FAILURE in
    case of memory allocation error
*/
void List_add(List* const self, void* const data);

/**
    \brief Returns the number of elements in the list
    \param self the list
    \return the size of the list (size >= 0)
*/
size_t List_size(const List* const self);

/**
    \brief Return the first element of the list
    \param self the list
    \return the first element
*/
void* List_head(const List* const self);

/**
*   \brief Remove the first element of the non-empty list
*   \param self the list
*
*   If the list is empty, it does nothing
*/
void List_removeHead(List* const self);

/**
    \brief Get an fail-fast iterator on this list
    \param self the list
    \return an robust iterator on this list
*/
ListIterator* iterator(const List* const self);

/**
    \brief know if the iterator has other elements
    \param self the iterator
    \param hasNext output parameter that tell if there is other elements
    \return if the list was modified since the creation of this iterator
*/
bool ListIterator_safeHasNext(const ListIterator* const self, bool* const hasNext);

/**
    \brief get the next element from iterator
    \param self the iterator
    \param data output paramater for the data to get
    \return if the list was modified since the creation of this iterator
*/
bool ListIterator_safeNext(ListIterator* const self, void** const data);

/**
    \brief know if the iterator has other elements
    \param self the iterator whose list must not have been modified
    \return if the iterator has other elements
*/
bool ListIterator_hasNext(const ListIterator* const self);

/**
    \brief get the next element from iterator
    \param self the iterator whose list must not have been modified
    \return the next element
*/
void* ListIterator_next(ListIterator* const self);

#endif
