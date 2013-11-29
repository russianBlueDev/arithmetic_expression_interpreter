/*
	Test suite for List
*/

#include <stdlib.h>
#include <assert.h>
#include <List.h>


void headOfEmptyList() {
	List* l = malloc(sizeof(List));
	assert(List_head(l) == NULL);
	free(l);
}

int main(void) {
	headOfEmptyList();
	return 0;
}