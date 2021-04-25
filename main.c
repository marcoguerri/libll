#include "ll.h"


int
print(void *ptr, char *str)
{
    return sprintf(str,"%d ", *((uint8_t*)ptr));
}

int
main() {
    int v[] = {20, 30};
    ll_t* list_int = NULL;
    list_int = ll_init(&v[0], sizeof(int));
    list_int = ll_insert(list_int, &v[1], ll_len(list_int));
    printf("%s\n", ll_print(list_int, print));
}

