#include <stdlib.h>
#include "utils.h"


void* xmalloc(size_t size)
{
    void* ptr = malloc(size);
    if(ptr == NULL && size != 0) {
        fprintf(stderr, "Out of Memory for allocation of size %lu", size);
        fprintf(stderr, "Exiting...");
        exit(EXIT_FAILURE);
    }
    
    return ptr;
}

void* xcalloc(size_t count, size_t size)
{
    void* ptr = calloc(count, size);
    if(ptr == NULL && count != 0 && size != 0) {
        fprintf(stderr, "Out of Memory for allocation of %lu blocks of size %lu", count, size);
        fprintf(stderr, "Exiting...");
        exit(EXIT_FAILURE);
    }
    return ptr;
}
