#include <stdio.h>
#include <glib.h>

int main(void) {
    printf("Hello world!\n");
    GList* list = NULL;
    list = g_list_append(list, "Hello second one");
    printf("%s\n", g_list_first(list)->data);
    return 0;
}
