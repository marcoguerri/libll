#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "list.h"
#include "test.h"

int 
print_integer_payload(void *ptr, char *str)
{
    return sprintf(str,"%d ", *((int*)ptr));
}

void 
test_list_init_creates_list_with_one_node()
{
    int el = 100;
    node_t *ptr_root =  list_init(&el, sizeof(int));
    _assert(ptr_root != NULL && 
            *((int*)ptr_root->data->payload) == 100 &&
            ptr_root->next == NULL &&
            ptr_root->prev == NULL);
    list_destroy(ptr_root);
}

void 
test_list_insert_at_end_appends()
{
    int el = 0;
    size_t i;
    char *test_result = "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 ";

    node_t *ptr_root =  list_init(&el, sizeof(int));
    for(i = 1; i < 20; ++i)
        ptr_root = list_insert(ptr_root, &i, sizeof(int), i);
    
    char *list_printed = list_print(ptr_root, print_integer_payload);
    _assert(strcmp(list_printed, test_result) == 0);

    free(list_printed);
    list_destroy(ptr_root);
}


void
test_list_len_returns_correct_length()
{
    int el = 100;
    uint8_t num_err = 0, i = 0;
    
    if(list_len(NULL) != 0)
        ++num_err;
    
    node_t *ptr_root =  list_init(&el, sizeof(int));
    if(list_len(ptr_root) != 1)
        goto fail;

    for(i = 1; i < 100; ++i)
    {
        /* Inserting at the beginning */
        ptr_root = list_insert(ptr_root, &el, sizeof(int), 0);
        if(list_len(ptr_root) != i + 1)
            goto fail;
    }
    
    list_destroy(ptr_root);
    _assert(1);
    return;

fail:
   list_destroy(ptr_root);
    _assert(0);
}


void test_list_get_returns_correct_value()
{
    int el = 0;
    uint64_t i = 0;
    
    node_t *ptr_root =  list_init(&el, sizeof(int));

    for(i = 1; i < 100; ++i)
        ptr_root = list_insert(ptr_root, &i, sizeof(int), i);

    for(i = 0; i < 100; ++i)
    {
        int *test = list_get(ptr_root, i);
        if(*test != i)
            goto fail;
    }
    list_destroy(ptr_root);
    _assert(1);
    return;

fail:
    list_destroy(ptr_root);
    _assert(0);
    return;
}

void 
test_list_del_deletes_root()
{
    int el = 100;
    node_t *ptr_root =  list_init(&el, sizeof(int));
    ptr_root = list_del(ptr_root, &el, sizeof(int));
    _assert(ptr_root == NULL && list_len(ptr_root) == 0);
}


void 
test_list_del_deletes_at_the_end()
{

    int el1 = 100, el2 = 102, el3 = 102;
    node_t *ptr_root =  list_init(&el1, sizeof(int));
    ptr_root = list_insert(ptr_root, &el2, sizeof(int), list_len(ptr_root));
    ptr_root = list_insert(ptr_root, &el3, sizeof(int), list_len(ptr_root));
    
    ptr_root = list_del(ptr_root, &el3, sizeof(int));
    _assert(list_len(ptr_root) == 2 && 
            list_search(ptr_root, &el2, sizeof(int)) &&
            list_search(ptr_root, &el1, sizeof(int)));

    list_destroy(ptr_root);
}


void 
test_list_del_deletes_in_the_middle()
{

    int el1 = 100, el2 = 102, el3 = 102;
    node_t *ptr_root =  list_init(&el1, sizeof(int));
    ptr_root = list_insert(ptr_root, &el2, sizeof(int), list_len(ptr_root));
    ptr_root = list_insert(ptr_root, &el3, sizeof(int), list_len(ptr_root));
    
    ptr_root = list_del(ptr_root, &el2, sizeof(int));
    _assert(list_len(ptr_root) == 2 && 
            list_search(ptr_root, &el1, sizeof(int)) &&
            list_search(ptr_root, &el3, sizeof(int)));

    list_destroy(ptr_root);
}

int 
main(int argc, char *argv[])
{
    test_list_init_creates_list_with_one_node();
    test_list_insert_at_end_appends();
    test_list_len_returns_correct_length();
    test_list_get_returns_correct_value();
    test_list_del_deletes_root();
    test_list_del_deletes_at_the_end();
    test_list_del_deletes_in_the_middle();
    return 0;
}
