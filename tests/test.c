#include <stdio.h>
#include <assert.h>

int main(void) {
    assert(1 && "Test failed because universe is false");
    return 0;
}
