/*
	Test suite for List
*/

#include <stdlib.h>
#include <assert.h>
#include <List.h>

// TestArray is an pointer to function taking a list and returning void
typedef void (*TestArray)(List*);

void headOfEmptyList(List* l) {
	assert(List_head(l) == NULL);
}

void sizeOfEmptyList(List* l) {
	assert(List_size(l) == 0);
}

void addOnEmptyList(List* l) {
	int* x = malloc(sizeof(int));
	*x = 5;
	List_add(l, x);
	assert(List_head(l) == x);
	assert( *((int*)List_head(l)) == 5);
	free(x);
}

void removeOnEmptyList(List* l) {
	List_removeHead(l);
	List_removeHead(l);
	assert(List_size(l) == 0);
}

void addAndRemove(List* l) {
	int* x = malloc(sizeof(int));
	*x = 5;
	int* y = malloc(sizeof(int));
	*y = 2;

	List_add(l, x);
	assert(List_head(l) == x);
	assert(List_size(l) == 1);
	List_add(l, y);
	assert(List_head(l) == x);
	assert(List_size(l) == 2);
	List_removeHead(l);
	assert(List_head(l) == y);
	assert(List_size(l) == 1);
	List_removeHead(l);
	assert(List_head(l) == NULL);
	assert(List_size(l) == 0);

	free(x);
	free(y);
}

int main(void) {

	const size_t TEST_COUNT = 5;

	TestArray* tests = calloc(TEST_COUNT, sizeof(TestArray));
	tests[0] = headOfEmptyList;
	tests[1] = sizeOfEmptyList;
	tests[2] = addOnEmptyList;
	tests[3] = removeOnEmptyList;
	tests[4] = addAndRemove;

	for(int i = 0; i < TEST_COUNT; i++) {
		// Setup the test
		List* l = List_new();
		// Launch the test
		tests[i](l);
		// tear down the test
		List_delete(&l);
	}

	free(tests);
	return 0;
}