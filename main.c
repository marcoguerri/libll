#include "list.h"


int
print_integer_payload(void *ptr, char *str)
{
    return sprintf(str,"%d ", *((uint8_t*)ptr));
}

int 
main() {
    int a = 20;
    int b = 30;
    char *list_repr;
    ads_list_t* list_int = NULL;
    list_int = ads_list_init(&a, sizeof(int));
    list_int = ads_list_insert(list_int, &b, ads_list_len(list_int));
    list_repr = ads_list_print(list_int, print_integer_payload);
    printf("List representation: %s\n", list_repr);
    ads_list_destroy((void*)list_int);
}


